#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

struct Auth {
  char name[32];
  int auth;
};

struct Auth *instance;
char *service;

int main(int argc, char **argv)
{
  char line[128];

  while(1) {
    printf("[ auth = %p, service = %p ]\n", instance, service);

    if(fgets(line, sizeof(line), stdin) == NULL) break;
    
    if(strncmp(line, "auth ", 5) == 0) {
      instance = malloc(sizeof(*instance));
      memset(instance, 0, sizeof(*instance));
      if(strlen(line + 5) < 31) {
        strcpy(instance->name, line + 5);
      }
    }
    if(strncmp(line, "reset", 5) == 0) {
      free(instance);
    }
    if(strncmp(line, "service", 6) == 0) {
      service = strdup(line + 7);
    }
    if(strncmp(line, "login", 5) == 0) {
      if(instance->auth) {
        printf("you have logged in already!\n");
      } else {
        printf("please enter your password\n");
      }
    }
  }
}