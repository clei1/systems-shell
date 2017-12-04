#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
  char cwd[1024] = "alohomora and life";
  char lol[128] = "/life;ife";
  if(strrchr(lol, '/')){
    strcat(cwd,(strrchr(lol, '/') + 1));
  }
  printf("%s", cwd);
}
