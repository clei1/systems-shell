#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
  int in, out;
  char *test[] = {"cat", "test", NULL};

  // open input and output files

  in = open("scores", O_RDONLY);
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT);

  dup2(in, 0);
  dup2(out, 1);
  close(in);
  close(out);
  execvp(test[0], test);
}


void redirection(char ** line){
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
  *filename = 0; //changes "<" or ">" to 0
  filename ++;
  
  if(direction == SIN){
    int in = open(filename, O_CREAT); //created file descriptor, to replace normal stdin during redirection
    int sstdin = dup(0); //creates alias sstdin to stdin, to be used after redirection complete
    dup2(in, 0); //changes normal stdin to the stdin we want to use
    close(in);
    execute_args(line); //executes stuff like normal, but with changed stdin

    //parent executes this
    dup2(sstdin, 0); //resets stdin back to 0 using alias sstdin to stdin created before
    close(sstdin); //closes no longer needed alias
  }
  else{
    int out = open(filename, O_CREAT);
    
    int sstdout = dup(1);
    dup2(out, 1);
    close(out);

    execute_args(line);
    
    dup2(sstdout, 1);
    close(sstdout);
  }
}
