#include "redirect.c"
#include "spoon.c"

void special_exec(char ** line){
    if(! strcmp(line[0], "exit")){
      exit(0);
    }
    if(! strcmp(line[0], "cd")){
      chdir(line[1]);
    }
}

void execute_args(char ** line){
  if(fork() == 0){
    //child process
    execvp(line[0], line);
    printf("Command not recognized.\n");
    exit(0);
  }
  else{
    //parent process
    int st;
    wait( &st );
  }
}

void exec(char * command){
  while(command){

    char s[200];
    char * line = strsep(& command, ";");
    strcpy(s, line);
    char ** cmd = parse_args(line);
    
    if(strchr(s, '|')){
      piping(s);
    }
    else if(strchr(s, '>')){
      redirecting(1, cmd);
    }
    else if(strchr(s, '<')){
      redirecting(0, cmd);
    }
    else{
      special_exec(cmd);
      execute_args(cmd);
    }

    free(cmd);
  }
 
}
