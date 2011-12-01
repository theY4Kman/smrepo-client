#pragma semicolon 1

#include <sourcemod>
#include <rootmenu>

public Plugin:myinfo =
{
    name = "SMRepo",
    author = "theY4Kman",
    description = "Yak's SMRepo client -- SourceMod Plug-in Repository tool",
    version = "0.0.0.1-unreleased",
    url = "http://smrepo.net"
};

ROOTMENU_COMMAND(test,"test","Let's test this shit!","What can I say, man? This is a\nTest\nandSHIT!")
{
    PrintToServer("Test!");
}

BEGIN_ROOTMENU(menu,"menu","This is a description for this here menu")
    COMMAND(test)
END_ROOTMENU()

public OnPluginStart()
{
    INIT_ROOTMENU(menu);
}