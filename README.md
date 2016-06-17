# Arduino COM Template

Basic Arduino project with event-driven COM port command interface. This is a starting point for projects that require a terminal UI.
- Command list is easily expandable.
- Event driven command interface allows processing to continue while waiting for user commands.

## Todo

- Add functionality where typing "help <cmd>" provides specific help on command.

## Command interface

Uses serialEvent() to build up user command from individual key strokes. When the complete command is issued by the user (upon hitting the Enter key), the appropriate function is called.

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
