#include "diskSim.h"

using namespace std;

int main(int argc, char** argv) {
  parseCommandLine(argc, argv);
  readSequenceFile(sequenceFile);
  print();
  return 0;
}

void parseCommandLine(int argc, char* argv[]) {
  switch(argc){
    case 2:
      initialPosition = strtol(argv[1], NULL, STRTOL_BASE);
      sequenceFile = generateSequenceFile();
      break;

    case 3:
      initialPosition = strtol(argv[1], NULL, STRTOL_BASE);
      sequenceFile = argv[2];
      break;

    default:
      cout << "Invalid input." << endl;
      exit(EXIT_FAILURE);
  }
}

string generateSequenceFile() {
  
}

void readSequenceFile() {

}

void print() {
  printf("FCFS %d\nSSTF %d\nSCAN %d\nC-SCAN %d\nLOOK %d\nC-LOOK %d\n",
   numFCFS, numSSTF, numSCAN, numCSCAN, numLOOK, numCLOOK);
}
