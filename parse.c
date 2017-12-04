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
  char ** args = (char **) calloc(10, sizeof(char*));
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
