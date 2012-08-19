from sourcemod import *

PYCHARM_DEBUG_PORT = 1292


class WetCommands(object):
    def install(self):
        pass


def concmd_wet(cmd):
    return Plugin_Handled


def toggle_pycharm_debug(cvar, newvalue, oldvalue):
    if bool(newvalue):
        from pydev import pydevd
        pydevd.settrace('localhost', port=PYCHARM_DEBUG_PORT, suspend=False)

def pycharm_debug_port_change(cvar, newvalue, oldvalue):
    global PYCHARM_DEBUG_PORT
    try:
        PYCHARM_DEBUG_PORT = int(newvalue)
    except ValueError:
        print >> server_err, 'Port must be a valid integer'
        cvar.value = oldvalue

def register_convars():
    """Registers the core convars"""
    cvar_debug = console.create_convar('wet_pycharm_debug', '0',
                                       'Enables/disables PyCharm remote '
                                       'debugging.')
    cvar_debug.hook_change(toggle_pycharm_debug)

    cvar_debug_port = console.create_convar('wet_pycharm_debug_port',
                                            str(PYCHARM_DEBUG_PORT),
                                            'The port the remote PyCharm '
                                            'debugger will bind to', 0,
                                            1024, 65535)
    cvar_debug_port.hook_change(pycharm_debug_port_change)

def register_concommands():
    """Registers the core concommands"""
    console.reg_srvcmd('wet', concmd_wet, 'The SMRepo Package Manager')

def register_console():
    """Registers all the core convars and concommands"""
    register_convars()
    register_concommands()


if __name__ == '__main__':
    register_console()
