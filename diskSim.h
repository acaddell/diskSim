#ifndef DISKSIM_H
#define DISKSIM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cmath>

#define STRTOL_BASE 10
#define DEFAULT_SEQUENCE_LENGTH 500
#define DISK_SIZE 5000
#define GOING_UP 1
#define GOING_DOWN -1

class Cylinder {
  public:
    Cylinder(int new_loc) {
      location = new_loc;
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
extern void populateCylinders(); // fills vector with 100 random positions
extern void readSequenceFile(std::string file); // parses file and creates cylinders
extern void runFCFS();
extern void runSSTF();
extern void runSCAN();
extern void runCSCAN();
extern void runLOOK();
extern void runCLOOK();
extern std::vector<Cylinder*> copyCylinders(); // creates a new copy of the cylinders vector
// runs the scan algorithm and returns the distance traveled from position
extern int scanInDirection(std::vector<Cylinder*> temp_cylinders, int direction, int position);
// runs the look algorithm and returns the distance traveled from position
extern int lookInDirection(std::vector<Cylinder*> temp_cylinders, int direction, int position);
// gets the maximum position from a given vector for look algorithm
extern int getMax(std::vector<Cylinder*> temp_cylinders);
// gets the minimum position from a given vector for look algorithm
extern int getMin(std::vector<Cylinder*> temp_cylinders);
extern void print(); // print results

#endif
