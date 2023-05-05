#ifdef __SWITCH__
#include "nx.h"
#include <switch.h>

void initNxlink()
{
    socketInitializeDefault();
    nxlinkStdio();
}

void closeNxlink()
{
    socketExit();
}
#endif
