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

void redirect(int std, int fd, char **line){
  int sstdin = dup(std);
  dup2(fd, std);
  close(fd);

  execute_args(line);
  
  dup2(sstdin, std);
  close(sstdin);
}

void redirecting(int std, char ** line){
  int index = 0;
  while(line[index]){
    if(strcmp(line[index], "<") == 0 || strcmp(line[index], ">") == 0 )
      break;
    index ++;
  } 
  char * filename = line[index + 1];
  line[index] = 0;

  int fd = open(filename, O_CREAT, 0644);
  redirect(std, fd, line);
}


void exec(char * command){
  while(command){

    char s[200];
    char * line = strsep(& command, ";");
    strcpy(s, line);
    char ** cmd = parse_args(line);
    
    if(strchr(s, '|')){
      piping(cmd);
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


