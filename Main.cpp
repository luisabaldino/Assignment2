#include <iostream>
using namespace std;
#include "Cell.h"
#include "Grid.h"
#include "UserInterface.h"
#include "Simulation.h"

int main(){
  Simulation sim = Simulation();
  sim.runSimulation();
}
