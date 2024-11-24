#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setup(void) {
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
}

void admin_debug(char *command) { system(command); }

int main() {
  setup();
  char name[256];
  printf("Ah, a curious soul! Speak thy words, and they shall echo through the aether... twice, as is the way of ancient spells!\n");
  read(0, name, 255);
  printf(name);
  printf(name);
  return 0;
}
