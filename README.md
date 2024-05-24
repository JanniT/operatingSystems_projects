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
and then input all the text you want to be reversed. Then press ```Ctrl + D``` to execute the reversion.

## Project 2 - Unix utilities

### my-cat

This app function the same way as unix `cat` command, where it can print the 
contents of a file, or if not given any file path parameter, it will print out 
stdin.

### my-grep

This utility is a variant of the unix `grep` command, where it looks through a file line by line and tries to find user-specified search term in the line. If it finds a line with the word in it, the line is printed out. 

If a search term is provided but a file isn't, my-grep reads and searches the term from the standard input. This is done until user presses ```Ctrl + D```

Run the program:  

```
$ ./my-grep term file.txt
```

or:

```
$ ./my-grep term
```
and then giving text as standard input until pressing ```Ctrl + D```

### my-zip

This utility is a simple file compression tool that uses run-length encoding (RLE). It compressess file(s) via replacing consecutive sequences of the same character with a single character followed by the count of that character. 

If user gives multiple files to be compressed, they're separated with a separator, which helps the my-unzip app to check and separate the file contents.

Run the program: 

```
$ ./my-zip file1 [file2 ...] > compressed_output.z
```

### my-unzip

The my-unzip app simply does the reverse of the previous my-zip app, taking in a compressed file(s) and writing (to standard output) the uncompressed results. The my-unzip supports decompressing of multiple zip files.

Run the program: 

```
$ ./my-unzip file1 [file2 ...]
```

## Project 3 - Unix shell

This project involves building a simple Unix shell, a command-line interpreter central to the Unix/C programming environment.

### Basic Shell: wish
The shell, named wish (short for Wisconsin Shell), operates in an interactive loop:

- Prints a prompt wish>
- Parses user input
- Executes the specified command
- Repeats until the user types exit

Run the program: 
Interactive mode:

```
$ ./wish
```
Batch mode

```
$ ./wish batch.txt
```

### Command execution

Executes commands by creating a new process for each command, except for built-in commands. Uses the path variable to find executables.

#### Build-in Commands

```
wish> exit
```

```
wish> cd /desired/path
```

```
wish> path /bin /usr/bin
```

Output redirection using '>'

```
wish> ls -la /tmp > output.txt
```

Supports multiple commands in parallel using 'g'

```
wish> cmd1 & cmd2 args1 args2 & cmd3 args1
```


## Authors

These projects are done together by:
- Janni Timoskainen
- Leevi Laitala
