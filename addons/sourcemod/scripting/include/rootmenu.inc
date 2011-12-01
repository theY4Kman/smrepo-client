/**
 * # Root Menu
 * Implements an `sm`-like root menu system.
 * 
 * Usage is simple. Anywhere in the global scope (i.e. outside functions),
 * place this::
 *
 *     MENU_COMMAND(name_of_my_command,"name_of_my_command",\
 *                  "Short description displayed in command listing",\
 *                  "A help text longer than the short description,\n\
 *                   Preferrably it also explains arguments:\n\
 *                   Usage: {command} <required> [optional] ...")
 *     {
 *         ReplyToCommand(client, "Menu: %s, Command: %s, Arguments: %s", menu, cmd, args);
 *     }
 *
 * Also in the global scope, you'll place the menu declaration. This declaration
 * describes which commands are enabled and what order they're in::
 * 
 *     BEGIN_ROOTMENU(menu_command,"menu_command","Console command description")
 *         COMMAND(name_of_my_command)
 *     END_ROOTMENU()
 *
 * Finally, we enable and initialize the menu inside OnPluginStart
 * with this line::
 *
 *     public OnPluginStart()
 *     {
 *         INIT_ROOTMENU(menu_command);
 *     }
 */

// Just in case!
#include <sourcemod>

//      ROOTMENU_COMMAND(cmd, description, helptext)
#define ROOTMENU_COMMAND(%1,%2,%3,%4) \
Action:___menu_command___%1___description(const String:cmd[], String:description[], maxlength) \
{ \
    if (strcmp(cmd, %2) == 0) { \
        strcopy(description, maxlength, %3); \
        return Plugin_Stop; \
    } \
    return Plugin_Continue; \
} \
Action:___menu_command___%1___helptext(const String:cmd[], String:description[], maxlength) \
{ \
    if (strcmp(cmd, %2) == 0) { \
        strcopy(description, maxlength, %4); \
        return Plugin_Stop; \
    } \
    return Plugin_Continue; \
} \
Action:___menu_command___%1___command(client, const String:menu[], const String:cmd[], const String:args[]) \
{ \
    if (strcmp(cmd, %2) == 0) { \
        ___menu_command___%1___command_run(client, menu, cmd, args); \
        return Plugin_Stop; \
    } \
    return Plugin_Continue; \
} \
___menu_command___%1___command_run(client, const String:menu[], const String:cmd[], const String:args[])


#define BEGIN_ROOTMENU(%1,%2,%3) \
new Handle:___root_menu___%1___forward_description = INVALID_HANDLE; \
new Handle:___root_menu___%1___forward_helptext = INVALID_HANDLE; \
new Handle:___root_menu___%1___forward_command = INVALID_HANDLE; \
public Action:___root_menu___%1___command(args) \
{ \
    return Plugin_Handled; \
} \
___root_menu___%1___initialize() \
{ \
    RegServerCmd(%2, ___root_menu___%1___command, %3); \
    ___root_menu___%1___forward_description = CreateForward(ET_Hook, Param_String, Param_String, Param_Cell); \
    ___root_menu___%1___forward_helptext = CreateForward(ET_Hook, Param_String, Param_String, Param_Cell); \
    ___root_menu___%1___forward_command = CreateForward(ET_Hook, Param_Cell, Param_String, Param_String, Param_String); \
    new Handle:forward_description = ___root_menu___%1___forward_description; \
    new Handle:forward_helptext = ___root_menu___%1___forward_helptext; \
    new Handle:forward_command = ___root_menu___%1___forward_command;

#define COMMAND(%1) \
    AddToForward(forward_description, INVALID_HANDLE, ___menu_command___%1___description); \
    AddToForward(forward_helptext, INVALID_HANDLE, ___menu_command___%1___helptext); \
    AddToForward(forward_command, INVALID_HANDLE, ___menu_command___%1___command);

#define END_ROOTMENU() \
}

#define INIT_ROOTMENU(%1) \
    ___root_menu___%1___initialize()
