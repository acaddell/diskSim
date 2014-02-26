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
  cylinders.push_back(new Address());
  for(int i = 0; i < DEFAULT_SEQUENCE_LENGTH; i++) {
    cylinders[i].location = rand() % DISK_SIZE;
    cylinders.push_back(new Address());
  }
}

void readSequenceFile(string file) {

}

void print() {
  printf("FCFS %d\nSSTF %d\nSCAN %d\nC-SCAN %d\nLOOK %d\nC-LOOK %d\n",
   numFCFS, numSSTF, numSCAN, numCSCAN, numLOOK, numCLOOK);
}
