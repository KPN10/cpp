#ifndef MISC_H
#define MISC_H

#include <unistd.h>

int msleep(unsigned int xArg) { return usleep(xArg * 1000); }

#endif

