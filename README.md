# Arduino COM Template

Basic Arduino project with event-driven COM port command interface.
- Command list is easily expandable; this is a starting point for projects
- Event driven command interface allows processing (loop function) to continue while waiting for user commands.

## Todo

- Add functionality where typing "help <cmd>" provides specific help on command

## Command interface

Uses serialEvent() to build up user command. When the complete  command is issued by the user (upon hitting the Enter key), the appropriate function is called.

### Files
- cmds.cpp
- cmds.h

### Adding new commands

To add new commands:

- Add command functions to .ino file of form:

    int cmd_<command name>(char *args[]))
    {
      /*do stuff*/
    }

- Update the commandTable with command string and command function pointer

- Declare command function in the main.h
