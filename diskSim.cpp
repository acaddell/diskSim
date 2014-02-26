#include "diskSim.h"

using namespace std;

int main(int argc, char** argv) {
  parseCommandLine(argc, argv);
  
  print();
  return 0;
}

void parseCommandLine(int argc, char* argv[]) {
  switch(argc){
    case 2:
      initialPosition = strtol(argv[1], NULL, STRTOL_BASE);
      generateSequenceFile();
      break;

    case 3:
      initialPosition = strtol(argv[1], NULL, STRTOL_BASE);
      sequenceFile = argv[2];
      readSequenceFile(sequenceFile);
      break;

    default:
      cout << "Invalid input." << endl;
      exit(EXIT_FAILURE);
  }
}

void generateSequenceFile() {
  for(int i = 0; i < DEFAULT_SEQUENCE_LENGTH; i++) {
    cylinders.push_back(new Cylinder(0));
    cylinders[i]->location = rand() % DISK_SIZE;
  }
}

void readSequenceFile(string file) {
  FILE *sequence;
  int location;

  if (((sequence = fopen(file.c_str(),"r")) == NULL)) {
    cout << "Invalid reference sequence file." << endl;
    exit(EXIT_FAILURE);
  }

  while (fscanf(sequence, "%d", &location) > 0 || !feof(sequence)) {
    cylinders.push_back(new Cylinder(location));
  }
  fclose(sequence);
}

void print() {
  printf("#for initial position of %d\n", initialPosition);
  printf("FCFS %d\nSSTF %d\nSCAN %d\nC-SCAN %d\nLOOK %d\nC-LOOK %d\n",
   numFCFS, numSSTF, numSCAN, numCSCAN, numLOOK, numCLOOK);
}

void runSSTF() {
  int currentLocation = initialPosition;
  int minDistance = initialPosition - cylinders[0].location;

  for(int i = 1; i < cylinders.size(); i++) {
    if(minDistance > abs(currentLocation - cylinders[i].location)) {
      minDistance = abs(currentLocation - cylinders[i].location);
    }
  }
}