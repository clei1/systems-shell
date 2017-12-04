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
