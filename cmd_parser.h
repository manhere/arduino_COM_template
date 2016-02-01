
#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#define GUI_CMD_BUFFER_SIZE     65    
#define MAX_ARGS                10    
#define NULL_COMMAND            "NULL"

bool verifyInput(char ch);
void processCommand(char *st);
void checkForCommand(); 

typedef struct
{
   char cmd[128];  
   char const *helpStr;  
   int  (*fp)(char *args[], unsigned int argCount);
}commandTable;

#endif
