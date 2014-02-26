#ifndef DISKSIM_H
#define DISKSIM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>
#include <vector>

#define STRTOL_BASE 10
#define DEFAULT_SEQUENCE_LENGTH 500
#define DISK_SIZE 5000

class Cylinder {
  public:
    Cylinder(int location) {
      location = 0;
    }
    ~Cylinder() { }

    int location;
};

std::vector<Cylinder*> cylinders;
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
extern void generateSequenceFile();
extern void readSequenceFile(std::string file); // parses file and creates cylinders
extern void runFCFS();
extern void runSSTF();
extern void runSCAN();
extern void runCSCAN();
extern void runLOOK();
extern void runCLOOK();
extern void print();

#endif
