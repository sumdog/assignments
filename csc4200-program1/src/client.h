#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>

#define BUFFER 256
#define CONFIG ".4200p1rc"

typedef struct cmd {
  char* service;
  char* command;
  char* host;
  unsigned short port;
} cmd_t;

typedef struct nameserver {
  char* nshost;
  unsigned short nsport;
} ns_t;

void freeCommand(cmd_t *t);

cmd_t* promptUser();

ns_t* getNameserver(char *file);

short serviceLookup(cmd_t *cmd, ns_t *ns);

void runCommand(cmd_t *cmd, char *output, long bufsize);


void runClient(char *config);


#endif /** CLIENT_H */
