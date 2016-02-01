#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "cmd_parser.h"
#include "WProgram.h" // needed to run Serial commands from non-.ino file

// Globals needed for interrupt/event driven command reader
bool cmdStringComplete = false;  // whether the string is complete
char cmdString[GUI_CMD_BUFFER_SIZE];

extern commandTable cmdTable[];

// Event driven serial command reader.
// Build a NULL terminated command string. Call processCommand if a newline is received.
void serialEvent() {
  static int index = 0;
  while (Serial.available()) {
    char ch = (char)Serial.read();
    if (verifyInput(ch))
      cmdString[index++] = ch;
    if (ch == '\r') {
      cmdString[index] = 0;     // NULL terminate
      index = 0;                // reset the index 
      cmdStringComplete = true; // flag that command recieved
    }
  }  
}

void checkForCommand()
{
  if (cmdStringComplete)
  {
    processCommand(cmdString);  // process the command
    cmdStringComplete = false;
  }
}

// Split command string into a command + args, check if this is a valid command, and call function with command + args
void processCommand(char *st)
{
  char *args[MAX_ARGS];
  unsigned int argCount;
  int cmdIndex = 0;
  int result;

  for (argCount = 0; argCount<5; argCount++)
    args[argCount] = NULL;
  
  // Get args
  argCount = 0;
  args[argCount] = strtok(st, " ");
  while((args[argCount] != NULL) && (argCount < MAX_ARGS))
  {
    argCount++;
    args[argCount] = strtok(NULL, " ");
  }
  
  strupr(args[0]);

  // find a valid command
  while(true)
  {
    if(strcmp(cmdTable[cmdIndex].cmd, NULL_COMMAND) == 0) // reached the end command list
    {
      Serial.println("Invalid command received. type 'help' for instructions\n");
      return;
    }
    if(strcmp(args[0], cmdTable[cmdIndex].cmd) == 0)
      break; // found a command match
    cmdIndex++;
  }
  
  // Call the appropriate function 
  result = cmdTable[cmdIndex].fp(args, argCount);
  if (result == 0)
    Serial.println("ACK");
  else
    Serial.println("NACK");
}

// Only allow alpha-numeric characters
bool verifyInput(char ch)
{
  if ((ch == ' '))
    return true;
  if ((ch >= '0') && (ch <= '9'))
    return true;      
  if ((ch >= 'A') && (ch <= 'Z'))
    return true;        
  if ((ch >= 'a') && (ch <= 'z'))
    return true;       
  return false;
}
