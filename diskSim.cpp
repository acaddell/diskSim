#include "diskSim.h"

using namespace std;

int main(int argc, char** argv) {
  parseCommandLine(argc, argv);
  runFCFS();
  runSSTF();
  runSCAN();
  runCSCAN();
  runLOOK();
  runCLOOK();
  print();
  return 0;
}

void parseCommandLine(int argc, char* argv[]) {
  switch(argc){
    case 2:
      initialPosition = strtol(argv[1], NULL, STRTOL_BASE);
      populateCylinders();
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

void populateCylinders() {
  for(int i = 0; i < DEFAULT_SEQUENCE_LENGTH; i++) {
    cylinders.push_back(new Cylinder(rand() % DISK_SIZE));
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
  printf("FCFS %d\nSSTF %d\nSCAN %d\nC-SCAN %d\nLOOK %d\nC-LOOK %d\n",
   numFCFS, numSSTF, numSCAN, numCSCAN, numLOOK, numCLOOK);
}

void runFCFS() {
  unsigned int distance = 0;
  int curr_location = initialPosition;
  for (unsigned int i = 0; i < cylinders.size(); i++) {
    distance += abs(curr_location - cylinders[i]->location);
    curr_location = cylinders[i]->location;
  }
  numFCFS = distance;
}

int scanInDirection(vector<Cylinder*> temp_cylinders, int direction, int position) {
  int distance = 0;

  while (position >= 0 && position < DISK_SIZE && temp_cylinders.size() > 0) {
    position += direction;
    distance++;
    for (unsigned int i = 0; i < temp_cylinders.size(); i++) {
      if (temp_cylinders[i]->location == position) {
        temp_cylinders.erase(temp_cylinders.begin() + i);
        i--;
      }
    }
  }
  return distance;
}

vector<Cylinder*> copyCylinders() {
  vector<Cylinder*> temp_cylinders;
  for (unsigned int i = 0; i < cylinders.size(); i++) {
    temp_cylinders.push_back(cylinders[i]);
  }
  return temp_cylinders;
}

int getMin(vector<Cylinder*> temp_cylinders) {
  int min = DISK_SIZE;
  for (unsigned int i = 0; i < temp_cylinders.size(); i++) {
    if (temp_cylinders[i]->location < min) {
      min = temp_cylinders[i]->location;
    }
  }
  return min;
}

int getMax(vector<Cylinder*> temp_cylinders) {
  int max = 0;
  for (unsigned int i = 0; i < temp_cylinders.size(); i++) {
    if (temp_cylinders[i]->location > max) {
      max = temp_cylinders[i]->location;
    }
  }
  return max;
}

int lookInDirection(vector<Cylinder*> temp_cylinders, int direction, int position) {
  int distance = 0;
  int max = getMax(temp_cylinders);
  int min = getMin(temp_cylinders);

  while (position >= min && position < max && temp_cylinders.size() > 0) {
    position += direction;
    distance++;
    for (unsigned int i = 0; i < temp_cylinders.size(); i++) {
      if (temp_cylinders[i]->location == position) {
        temp_cylinders.erase(temp_cylinders.begin() + i);
        i--;
      }
    }
  }
  return distance;
}

void runSCAN() {
  int distance = 0;
  vector<Cylinder*> temp_cylinders = copyCylinders();

  if (initialPosition > 0) {
    distance += scanInDirection(temp_cylinders, 1, initialPosition);
    distance += scanInDirection(temp_cylinders, -1, DISK_SIZE-2);
  } else {
    distance += scanInDirection(temp_cylinders, -1, initialPosition);
    distance += scanInDirection(temp_cylinders, 1, 1);
  }
  numSCAN = distance;
}

void runCSCAN() {
  int distance = 0;
  vector<Cylinder*> temp_cylinders = copyCylinders();

  if (initialPosition > 0) {
    distance += scanInDirection(temp_cylinders, 1, initialPosition);
    distance += scanInDirection(temp_cylinders, 1, 0);
  } else {
    distance += scanInDirection(temp_cylinders, -1, initialPosition);
    distance += scanInDirection(temp_cylinders, -1, DISK_SIZE-1);
  }
  numSCAN = distance;
}

void runLOOK() {
  int distance = 0;
  vector<Cylinder*> temp_cylinders = copyCylinders();

  if (initialPosition > 0) {
    distance += lookInDirection(temp_cylinders, 1, initialPosition);
    distance += lookInDirection(temp_cylinders, -1, DISK_SIZE-2);
  } else {
    distance += lookInDirection(temp_cylinders, -1, initialPosition);
    distance += lookInDirection(temp_cylinders, 1, 1);
  }
  numLOOK = distance;
}

void runCLOOK() {

}

/* Need to remove elements that have already been visited from the vector */
void runSSTF() {
  int currentLocation = initialPosition;
  int nextLocationIndex = 0;
  int minDistance = abs(initialPosition - cylinders[0]->location);

  for(unsigned int i = 0; i < cylinders.size(); i++) {
    for(unsigned int j = 0; j < cylinders.size(); j++) {
      if((currentLocation - cylinders[j]->location) && minDistance > abs(currentLocation - cylinders[j]->location)) {
        minDistance = abs(currentLocation - cylinders[j]->location);
        nextLocationIndex = j;
      }
    }
    currentLocation = cylinders[nextLocationIndex]->location;
    numSSTF += minDistance;
    minDistance = DISK_SIZE;
  }
}
