#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

ssize_t getRandom(){
  int fd = open("/dev/random", O_RDONLY);
  ssize_t answer;
  read(fd, &answer, sizeof(ssize_t));
  if (errno) {
    printf("errno %d: %s\n", errno, strerror(errno));
  }
  close(fd);
  printf("answer: %lu\n", answer);
  return answer;
}

int main(){
  printf("Generating random numbers:\n");
  ssize_t randsInitial[10];
  for (int x=0; x<10; x++){
    randsInitial[x] = getRandom();
    printf("  random %d: %lu\n", x, randsInitial[x]);
  }

  /*printf("write wassup\n");
  write(fd, "wassup\n", 7);

  close(fd);
  printf("closed fd\n");

  printf("opened fd, can read\n");
  fd = open("file.txt", O_RDONLY);

  printf("reading\n");
  read(fd, b, 7);
  b[7] = "\0";

  printf("closed fd\n");
  close(fd);

  printf("should print wassup: %s\n", b);*/
}
