# Operating Systems and System Programming Projects
A repository for an operating systems -courses' projects. 

## Build applications

Clone the repository and build

```
$ git clone https://github.com/JanniT/operatingSystems_projects.git
$ cd operatingSystems_projects
$ make all
```

Make will build many small applications, which are listed below:

## Project 1 - Reverse

This project reads a text file and then reverses the order of the lines in it. 
The program should be invoked two command-line arguments specifying input and 
output files. For example: 

```
$ ./reverse
```
and then input all the text you want to be reversed. Then press `Ctrl + D` to
execute the reversion.

## Project 2 - Unix utilities

### my-cat

This app function the same way as unix `cat` command, where it can print the
contents of a file, or if not given any file path parameter, it will print out
stdin.

### my-grep

This utility is a variant of the unix `grep` command, where it looks through a
file line by line and tries to find user-specified search term in the line. If
it finds a line with the word in it, the line is printed out.

If a search term is provided but a file isn't, my-grep reads and searches the
term from the standard input. This is done until user presses `Ctrl + D`

Run the program:  

```
$ ./my-grep term file.txt
```

or:

```
$ ./my-grep term
```
and then giving text as standard input until pressing `Ctrl + D`

### my-zip

This utility is a simple file compression tool that uses run-length encoding
(RLE). It compressess file(s) via replacing consecutive sequences of the same
character with a single character followed by the count of that character.

If user gives multiple files to be compressed, they're separated with a
separator, which helps the my-unzip app to check and separate the file contents.

Run the program: 

```
$ ./my-zip file1 [file2 ...] > compressed_output.z
```

### my-unzip

The my-unzip app simply does the reverse of the previous my-zip app, taking in
a compressed file(s) and writing (to standard output) the uncompressed results.
The my-unzip supports decompressing of multiple zip files.

Run the program: 

```
$ ./my-unzip file1 [file2 ...]
```

## Project 3 - Unix shell

This project involves building a simple Unix shell, a command-line interpreter
central to the Unix/C programming environment.

### Basic Shell: wish
The shell, named wish (short for Wisconsin Shell), parses and executes command.
It can be run in an interactive or a batch mode.

In interactive mode there is a prompt printed, which shows the current working
directory followed with a dollar sign. The prompt waits for user input, and
after pressing Return, will parse and execute written command, after which
the promp is ready for next command. Interactive mode will run until user
presses `^C` or uses a internal exit command.

Batch mode works the same way, except will not print prompt and will read
commands from a provided file instead of from stdin.

```
$ ./wish
-> Will run interactive mode

$ ./wish batch.txt
-> Will run batch mode
```

### Command execution

All commands, except internal ones, are executed as a child process. Internal
commands are listed below, and external programs are searched from a 'path'
variable that the shell keeps track of. Value of 'path' can be changed with
a command, and the variable has a default value of `/bin`

#### Build-in Commands

```
exit <?exit-code>
pwd
cd <?path>
path <?paths>...
```

`exit` will exit shell with provided exit-code argument. If none given, will
default to 0

`pwd` prints current working directory

`cd` changes directory to given path. If none provided, will default to `HOME`

`path` will add arguments to 'path' where the shell searches for programs.
If no args are provided, will print current 'path'

#### Features

Arguments are parsed with whitespace as a delimiter with the exception of
text in quotes. Quotes can include whitespace characters, and the contents
will get parsed as a single token.

```
$    echo      this is "a    test !"
-> Would be tokenized to: [echo] [this] [is] [a    test !]
```

The shell supports a output redirection with `>` symbol. Which redirects
stdout and stderr to provided file.

```
$ echo "foo" > file.txt
$ cat file.txt
foo
```

Commands can be set to run in parallel with `&` symbol. It will print the pid
of the background child process.

```
$ sleep 10 & echo "this prints immidiately"
-> <pid>
this prints immidiately
```

## Authors

These projects are done together by:
- Janni Timoskainen
- Leevi Laitala
