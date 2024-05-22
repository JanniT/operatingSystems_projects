#include "argparse.h"
#include "cmd.h"

int parse_and_execute(parsed_command *cmd, char *cmdline) {
    enum Type {
        REGULAR = 0, QUOTE, WHITESPACE, REDIRECT, PARALLEL, COMMENT, NEWLINE
    };

    int cmdline_offset = 0;

    int token_length = 0;
    bool token_ready = false;
    bool next_token_is_redirect_filename = false;
    bool command_ready = false;

    char current_token_buf[MAX_ARG_LEN] = { 0 };

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

        if (type == COMMENT) {
            // Return from function immidiately if COMMENT is the first char
            // of token, since all the following tokens will also be inside
            // the comment
            if (token_length == 0 && cmd->argc == 0) { return 0; }
            token_ready = command_ready = true;
        }

        if (type == REGULAR) {
            current_token_buf[token_length++] = cur;
        }

        if (type == QUOTE) {
            cmd->quote = (int)(cmd->quote == 0);
        }

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

        // TODO: Bug fix 
        // Cmdline 'command > output' will be parsed as:
        // -> 'command' = token
        // -> 'output' = redirect fname
        //
        // But 'command>output' will be parsed the other way around:
        // -> 'command' = redirect fname
        // -> 'output' = token
        if (type == REDIRECT) {
            token_ready = next_token_is_redirect_filename = true;
        }

        if (type == PARALLEL) {
            next_token_is_redirect_filename = false;
            command_ready = token_ready = true;
            cmd->background = true;
        }

        if (type == NEWLINE) {
            if (cmdline_offset == 1) { continue; }
            command_ready = token_ready = true;
        }

        if (token_ready) {
            current_token_buf[token_length + 1] = '\0';

            if (token_length != 0) {
                if (next_token_is_redirect_filename) {
                    next_token_is_redirect_filename = false;
                    strcpy(cmd->output_redirect_filename, current_token_buf);
                } else {
                    strcpy(cmd->argv[cmd->argc++], current_token_buf);
                }
            }

            if (command_ready) {
                if (cmd->quote) {
                    printf("ERR: Unclosed quote\n");
                    return 1;
                }

                execute_command(cmd);

                command_ready = false;
                reset_cmd(cmd);
            }

            memset(current_token_buf, 0, token_length + 1);
            token_length = 0;
            token_ready = false;
        }
    }

    return 0;
}

void reset_cmd(parsed_command *cmd) {
    if (cmd->output_redirect != NULL && cmd->output_redirect != stdout) {
        fclose(cmd->output_redirect);
    }

    memset(cmd, 0, sizeof(parsed_command));
    cmd->output_redirect = stdout;
}

