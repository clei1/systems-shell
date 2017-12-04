#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "aesthetics"
#include "shell.h"

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
  char ** args = (char **) malloc(10 * sizeof(char*));
  int index = 0;
  while (line) {
    char *s = strsep(&line, " ");
    if(strlen(s) != 0){ //removes extra white space
      args[index] = s;
      index += 1;
    }
  }
  printarr(args);
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

void piping(char * s){
  //"ls -l | wc"
  char *first_cmd = strsep(&s, "|");
  char ** second_cmd = parse_args(s);
  
  FILE *pipe_fp;
  pipe_fp = popen(first_cmd, "r");
  int fd = fileno(pipe_fp);

  redirect(0, fd, second_cmd);
   
  pclose(pipe_fp);


  /*
  strncpy(pipe_file, ".tempfile", sizeof(pipe_file) );
  out_fd = redirect(STDOUT_FILENO, &out_copy, pipe_file);
  exec_command(temp); //execute the command

  //revert stdout
  out_fd = redirect_back(STDOUT_FILENO, out_copy, out_fd);

  //redirect stdin to temp
  in_fd = redirect(STDIN_FILENO, &in_copy, pipe_file);
  exec_command(command);

  remove(".tempfile");
  */
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
  int sstd = dup(std);
  dup2(fd, std);

  execute_args(line);

  close(fd);
  dup2(sstd, std);
  close(sstd);
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

  //need O_RDWR else it breaks
  int fd = open(filename, O_CREAT | O_RDWR, 0644);
  redirect(std, fd, line);
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


