#include "CInsultServer.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>

CInsultServer::CInsultServer(unsigned short port, long backlog) : CServer(port,backlog) {

  strcpy(name,"insult");

  //insults
  insults = new (char*)[10];
  insults[0] = "You're a loser.\n";
  insults[1] = "You're a big loser.\n";
  insults[2] = "Your mother undresses you funny.\n";
  insults[3] = "You eat poo.\n";
  insults[4] = "You're really a nice guy. Just kidding. You're a jerk.\n";
  insults[5] = "You're really something (and I don't mean that in a good way).\n";
  insults[6] = "You're a nice guy, but I all ready have a boyfriend.\n";
  insults[7] = "You actually liked that movie?! What a loser.\n";
  insults[8] = "Did I mention you eat poo?\n";
  insults[9] = "Friends? You have friends?\n";

  //randrom seed
  srand(time(NULL));
  rand(); //ignore first random number
}

CInsultServer::~CInsultServer() {
  delete insults;
}


void CInsultServer::processRequest(command_t *t, char* retval) {
  //command
  char cmd[BUFFER_SIZE];
  strcpy(cmd,*(t->argv));

  //strip off newline
  cmd[strlen(&cmd[0])-1] = '\0';

  //check for the right command format
  if(t->type == CMD_IVK   &&   t->argc == 1   &&   strcmp("insult",&cmd[0]) == 0  ) {
    
    short r = (short) floor(10 * ((float)rand()/RAND_MAX));
    strcpy(retval,"A:");
    strcat(retval,insults[r]);

  }
  else {
    strcpy(retval,"E:You Must Be Really Stupid If You Can't Even Use An Insult Service\n");
  }
}
