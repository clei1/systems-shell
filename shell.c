#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "aesthetics"
#include "headers.h"
#include "parse.c"
#include "command.c"

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


