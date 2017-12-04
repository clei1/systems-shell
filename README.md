# Project 1: Shell-ing out commands
## Connie Lei

### Features:

	Can separate multiple commands on a line with `;`
	Single redirection  `>` and `<` functionality (will cause files to be overwritten like normally)
	Single pipe `|` functionality
	Can use `cd` to change directories, but becomes buggy, refer to bugs for more info
	Can use `exit`
	Bad commands will let user know they failed
	Prompt displayed
	Random/extra spaces are taken care of

### Attempted:

	The following did not end up working, but have been left in the code, commented out.
	Worked on multiple redirection in the mess that is foo.c
	Tried making mutliple pipes work, but then started to go down rabbit holes and never getting out, kept breaking
	
### Bugs:

	After using `cd` to go up a directory level, some commands begin to break for some unknown reason. Using `cd ..` and then `ls` will sometimes break it. It seems to happen randomly and I've to debug this, but my head isn't working right now. Moving down a directory will give an error `/usr/bin/cd: line 4: cd: systems-shell: No such file or directory` but it will still sometimes move you down to the directory.
	The prompt will break depending on what machine you are using. I tested it while sshing into the school computers and also while on the the school computers and it comes out funny like. My laptop gives me `alohomora:systems-shell connielei$ ` so that is the one I based the prompt off of. It will probably break if you have fancy path customizations or something.
	
### Files & Function Headers:

I actually had one large file and aesthetics, but I broke most of it up for the sake of cutting it up.

aesthetics
	
	Handles the command prompt
	/*======== void prompt() ==========
	Inputs:  void
	Returns: void

	prints out the command prompt,
	is called before each user input
	====================*/

parse.c
	
	/*======== void printarr() ==========
	Inputs:  char* args[]
	Returns: void

	prints out the commands to be executed in array format,
	used for debugging
	====================*/

	/*======== char ** parse_args ==========
	Inputs:  char *line 
	Returns: Pointer to the beginning of line

	Removes leading and trailing whitespace on the string line.
	Terminating '\0' is placed at a new location if necessary.
	====================*/

command.c

	/*======== void special_exec ==========
	Inputs: char ** line
	Returns: void

	used for `exit` and `cd`
	as name suggests, for special commands
	only executable by the parent
	====================*/
	
	/*======== void execute_args ==========
	Inputs:  char ** line
	Returns: void

	forks() and executes the commands
	====================*/

	/*======== void exec  ==========
	Inputs:  char * command
	Returns: void

	runs commands with `;`
	wrapper function for other executes
	====================*/

spoon.c
	
	/*======== void piping ==========
	Inputs:  char * s
	Returns: void

	single piping functionality
	only function that takes in the entire command
	because it is parsed differently and used for popen()
	====================*/

redirect.c

	/*======== void redirecting  ==========
	Inputs:  int std, char ** line 
	Returns: void

	std tells whether `>` or `<`
	cleans up command to be execvp
	opens/creates a file, fd
	calls helper function redirect
	====================*/

	/*======== void redirect  ==========
	Inputs:  int std, int fd, char ** line 
	Returns: void

	uses dup, dup2, and executes commands
	====================*/
