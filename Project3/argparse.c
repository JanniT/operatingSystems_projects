#include "argparse.h"

extern int execute_command(parsed_command *cmd);

// Get user input via 'cmdline' and parse it into tokens, which are
// on top of other information stored into a 'parsed_command' structure.
//
// Commands are parsed with whitespace as a delimiter ('\n', '\t' and ' '),
// except for when text is inside quotes, then whitespace chars are included.
//
// Function iterates over 'cmdline' one char at a time, and makes decision
// based on the current character on what to do.
int parse_and_execute(parsed_command *cmd, char *cmdline) {
    enum Type {
        REGULAR = 0, QUOTE, WHITESPACE, REDIRECT, PARALLEL, COMMENT, NEWLINE
    };

    // Marks the index of current character in 'cmdline'
    int cmdline_offset = 0;

    // Local information about the current token
    int token_length = 0;
    bool token_ready = false;
    bool next_token_is_redirect_filename = false;
    bool command_ready = false;

    // Store current token here, and after the whole token is stored, copy
    // it's contents into the 'parsed_command->argv' list
    char current_token_buf[MAX_ARG_LEN] = { 0 };

    // Iterate over all characters in 'cmdline'
    while (cmdline[cmdline_offset++] != '\0') {
        char cur = cmdline[cmdline_offset - 1];

        enum Type type = REGULAR;
        switch (cur) {
            case ' ': case '\t':
                type = WHITESPACE;
                break;
            case '"':
                type = QUOTE;
                break;
            case '>':
                type = REDIRECT;
                break;
            case '&':
                type = PARALLEL;
                break;
            case '#':
                type = COMMENT;
                break;
            case '\n':
                type = NEWLINE;
                break;
        }

        // All tokens after a comment character are ignored
        if (type == COMMENT) {
            // Return from function immidiately if COMMENT is the first char
            // of token, since all the following tokens will also be inside
            // the comment
            if (token_length == 0 && cmd->argc == 0) { return 0; }
            token_ready = command_ready = true;
        }

        // All non-special characters are copied to the local token buffer
        if (type == REGULAR) {
            current_token_buf[token_length++] = cur;
        }

        // Quote variable has a value of 0 if there are no unclosed quotes
        if (type == QUOTE) {
            cmd->quote = (int)(cmd->quote == 0);
        }

        // Ignore whitespace unless command's quote value is non-zero
        if (type == WHITESPACE) {
            if (cmd->quote) {
                cmd->quote += (int)(cmd->quote != 0);

                // Include whitespace if in quotes
                current_token_buf[token_length++] = cur;
            } else {
                if (cmdline_offset == 1) { continue; }
                // If previously read REGULAR characters, token_length will
                // then have a non-zero value. In such case a token is ready
                // with whitespace being the delimiter
                token_ready = (token_length > 0);
            }
        }

        // When redirect character is found, the next token tells the output
        // redirection filename
        if (type == REDIRECT) {
            // TODO: Bug fix
            // Cmdline 'command > output' will be parsed as:
            // -> 'command' = token
            // -> 'output' = redirect fname
            //
            // But 'command>output' will be parsed the other way around:
            // -> 'command' = redirect fname
            // -> 'output' = token
            token_ready = next_token_is_redirect_filename = true;
        }

        // Parallel character completes the current token and current command.
        // The command should be executed right away
        if (type == PARALLEL) {
            next_token_is_redirect_filename = false;
            command_ready = token_ready = true;
            cmd->background = true;
        }

        // Newline characters represents the end of 'cmdline', and marks the
        // end of command. Command should be executed
        if (type == NEWLINE) {
            if (cmdline_offset == 1) { continue; }
            command_ready = token_ready = true;
        }

        // If token is ready, that is a whitespace character is reached with
        // quote variable having a value 0
        if (token_ready) {
            // Null terminate the token string
            current_token_buf[token_length + 1] = '\0';

            // Token can be ready and have a length of zero if there are
            // multiple whitespace characters. Then do nothing
            if (token_length != 0) {
                // If redirection char is parsed, store current token as the
                // filename for output
                if (next_token_is_redirect_filename) {
                    next_token_is_redirect_filename = false;
                    strcpy(cmd->output_redirect_filename, current_token_buf);
                } else {
                    // Regular token gets copied to parsed_command's argv and
                    // argc gets increased
                    strcpy(cmd->argv[cmd->argc++], current_token_buf);
                }
            }

            // Execute command if it's ready
            if (command_ready) {
                if (cmd->quote) {
                    printerr("%s: unclosed quote\n", PROGNAME);
                    return 1;
                }

                execute_command(cmd);

                command_ready = false;
                reset_cmd(cmd);
            }

            // Fully clear current token buffer
            memset(current_token_buf, 0, token_length + 1);
            token_length = 0;
            token_ready = false;
        }
    }

    // Wait for all background jobs to complete
    waitpid(-1, NULL, 0);

    return 0;
}

void reset_cmd(parsed_command *cmd) {
    memset(cmd, 0, sizeof(parsed_command));
}

