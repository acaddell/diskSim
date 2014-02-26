#ifndef DISKSIM_H
#define DISKSIM_H

#include <iostream>
#include <cstring>
#include <stdlib.h>

#define STRTOL_BASE 10

int initialPosition; // initial position of disk arm
std::string sequenceFile; // name of access sequence file (optional)

extern void parseCommandLine(int argc, char* argv[]);
extern std::string generateSequenceFile();

#endif
