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
