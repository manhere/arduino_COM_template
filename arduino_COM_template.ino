
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include "cmd_parser.h"
#include <stdlib.h>

#define REVISION "ardunio_template 1.0.0"

void setup() 
{
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.setTimeout(0);
  Serial.flush();
  pinMode(LED_BUILTIN,OUTPUT); 
  digitalWrite(LED_BUILTIN,HIGH);  // LED on
}

void loop() {
  checkForCommand();
}

commandTable cmdTable[] =
{
  {"HELP","Display help", cmd_help},  
  {"PING","Send ping to processor, which should respond with ACK", cmd_ping},
  {"REV","Display version information", cmd_rev},
  {NULL_COMMAND,"", cmd_ping} // last command must be NULL
};

/* 
Functions for commands in the command table
*/

int cmd_ping(char *args[], unsigned int argCount)
{
  return 0;
}

int cmd_rev(char *args[], unsigned int argCount)
{
  Serial.println(REVISION);
  return 0;
}

int cmd_help(char *args[], unsigned int argCount)
{
  for(uint cmdIndex = 0; cmdIndex < sizeof(cmdTable)/sizeof(commandTable) - 1; cmdIndex++) // minus 1 to avoid printing NULL
  {
    Serial.print(cmdTable[cmdIndex].cmd);
    Serial.print(" ");
    Serial.println(cmdTable[cmdIndex].helpStr);
  }
  return 0;
}


