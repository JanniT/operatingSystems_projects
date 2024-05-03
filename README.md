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

## Authors

These projects are done together by:
- Janni Timoskainen
- Leevi Laitala
