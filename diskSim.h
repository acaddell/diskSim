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
std::string sequenceFile; // name of access sequence file (optional)
// distance traveled for each algorithm
int numFCFS;
int numSSTF;
int numSCAN;
int numCSCAN;
int numLOOK;
int numCLOOK;

extern void parseCommandLine(int argc, char* argv[]);
extern std::string generateSequenceFile();
extern void readSequenceFile(std::string file);
extern void runFCFS();
extern void runSSTF();
extern void runSCAN();
extern void runCSCAN();
extern void runLOOK();
extern void runCLOOK();
extern void print();

#endif
