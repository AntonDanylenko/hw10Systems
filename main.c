#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int getRandom(){
  int fd = open("/dev/random", O_RDONLY);
  int answer;
  read(fd, &answer, sizeof(int));
  if (errno) {
    printf("errno %d: %s\n", errno, strerror(errno));
  }
  close(fd);
  //printf("answer: %d\n", answer);
  return answer;
}

int main(){
  printf("Generating random numbers:\n");
  int randsInitial[10];
  for (int x=0; x<10; x++){
    randsInitial[x] = getRandom();
    printf("  random %d: %d\n", x, randsInitial[x]);
  }

  printf("Writing numbers to file...\n\n");
  int fd0 = open("temp.txt", O_RDWR | O_CREAT, 0666);
  write(fd0, randsInitial, sizeof(randsInitial));
  if (errno) {
    printf("errno %d: %s\n", errno, strerror(errno));
  }
  close(fd0);

  printf("Reading numbers from file...\n\n");
  int fd1 = open("temp.txt", O_RDONLY);
  int randsFinal[10];
  read(fd1, randsFinal, sizeof(randsFinal));
  if (errno) {
    printf("errno %d: %s\n", errno, strerror(errno));
  }
  close(fd1);

  printf("Verification that written values were the same:\n");
  for (int x=0; x<10; x++){
    printf("  random %d: %d\n", x, randsFinal[x]);
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
