#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "aesthetics"

void printarr(char* args[]) {
  int index = 0;
  int i = 0;
  printf("[");
  while(args[i]){
    printf("'%s' ", args[i]);
    i ++;
  }
  printf("]\n");
}

char ** parse_args(char* line) {
  char ** args = (char **) malloc(6 * sizeof(char*));
  int index = 0;
  while (line) {
    char *s = strsep(&line, " ");
    if(strlen(s) != 0){ //removes extra white space
      args[index] = s;
      index += 1;
    }
  }
  return args;
}

void special_exec(char ** line){
    if(! strcmp(line[0], "exit")){
      exit(0);
    }

    if(! strcmp(line[0], "cd")){
      //change directories

    }
}

void piping(char ** line){
  //"ls -l | wc"
  
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


int redirection(char ** line){
  printarr(line);

  int SIN = 1;
  int SOUT = 2;
  int direction = 0;
  
  char * filename = line[0];
  while(filename){
    if(strcmp(filename, "<") == 0){
      direction = SIN;
      break;
    }
    else if(strcmp(filename, ">") == 0){
      direction = SOUT;
      break;
    }
    filename ++;
  }

  if(direction){
    *filename = 0; //changes "<" or ">" to 0
    filename ++;
    if(direction == SIN){
      int in = open(filename, O_CREAT); //created file descriptor, to replace normal stdin during redirection
      int sstdin = dup(0); //creates alias sstdin to stdin, to be used after redirection complete
      dup2(in, 0); //changes normal stdin to the stdin we want to use

      execute_args(line); //executes stuff like normal, but with changed stdin

      //parent executes this
      dup2(sstdin, 0); //resets stdin back to 0 using alias sstdin to stdin created before
      close(sstdin); //closes no longer needed alias
    }
    else{
      int out = open(filename, O_CREAT);
    
      int sstdout = dup(1);
      dup2(out, 1);

      execute_args(line);
    
      dup2(sstdout, 1);
      close(sstdout);
    }
  }
  return direction;
}



void exec(char * command){
  while(command){

    char * curr = strsep(& command, ";");
    
    if(strchr(curr, '|')){
      piping(parse_args(curr));
    }
    else{
      if(strchr(curr, '>') == NULL && strchr(curr, '<') == NULL){
	special_exec(parse_args(curr));
	execute_args(parse_args(curr));
      }
      else
	redirection(parse_args(curr));
    }
    
  }
 
}

int main(){

  while(1){
    prompt();

    char s[200];
    fgets(s, sizeof(s), stdin);
    *strchr(s, '\n') = 0;

    exec(s);
  }
    
  return 0;
}


