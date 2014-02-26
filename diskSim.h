#ifndef DISKSIM_H
#define DISKSIM_H

#include <iostream>
#include <cstring>
#include <stdlib.h>

#define STRTOL_BASE 10

class Cylinder {
  public:
    Cylinder(int location) {
      location = 0;
    }
    ~Cylinder() { }

    int location;
};

int initialPosition; // initial position of disk arm
int numFCFS;
int numSSTF;
int numSCAN;
int numCSCAN;
int numLOOK;
int numCLOOK;
std::string sequenceFile; // name of access sequence file (optional)

extern void parseCommandLine(int argc, char* argv[]);
extern std::string generateSequenceFile();

#endif
