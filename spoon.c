/*
void pipe_r(int fd, char ** cmd){
  int sstdin = dup(0);
  dup2(fd, 0);
  int sstdout = dup(1);
  dup2(1, 0);

  execute_args(line);

  close(fd);
  dup2(sstdin, 0);
  close(sstdin);
  dup2(sstdout, 1);
  close(sstdout);
}

void pipe_(char ** cmd){
  int sstdout = dup(1);
  dup2(1, 0);

  execute_args(line);

  dup2(sstdout, 1);
  close(sstdout);
}


void test(char * s){
  char *first_cmd = strsep(&s, "|");
  char ** second_cmd = parse_args(strsep(&s, "|"));
  
  FILE *pipe_fp;
  pipe_fp = popen(first_cmd, "r");
  int fd = fileno(pipe_fp);

  pipe_r(fd, second_cmd);
  
  while(&s){
    pipe_(second_cmd);
    second_cmd = parse_args(strsep(&s, "|"));
  }
  pclose(pipe_fp);
}

*/

void piping(char * s){
  //"ls -l | wc"
  char *first_cmd = strsep(&s, "|");
  char ** second_cmd = parse_args(s);
  
  FILE *pipe_fp;
  pipe_fp = popen(first_cmd, "r");
  int fd = fileno(pipe_fp);

  redirect(0, fd, second_cmd);
   
  pclose(pipe_fp);
}
