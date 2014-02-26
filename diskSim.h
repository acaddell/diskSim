#ifndef DISKSIM_H
#define DISKSIM_H

#include <iostream>

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
string sequenceFile; // name of access sequence file (optional)
int numFCFS;
int numSSTF;
int numSCAN;
int numCSCAN;
int numLOOK;
int numCLOOK;

#endif