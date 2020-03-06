#include <iostream>
using namespace std;
#include <fstream>

class Simulation
{
    public:

    int genCounter = 0;
    UserInterface user = UserInterface();
    Grid *grid;

    // Constructor
    Simulation() {
      //Get user input
      user.getUserInput();
      //Instantiate Grid object
      Grid *gr = new Grid(user.getRows(), user.getColumns(), user.getInitValuesArr());
      grid = gr;
    }

     /**
        Run the simulation
     **/
     void runSimulation(){
       while (!grid->isEmpty() && !grid->isStable()){
         user.output(grid,genCounter);         
         grid->calcNextGen(user.getMode());
         genCounter++;
       }
       cout << "End of simulation. Press enter to exit." << endl;
       cin.ignore();
     }
};

/*
Simulation Class:
  Attributes:
    - All user inputs (actually in userinterface)
    - 1 grid object
  Methods:
  - X Check if stop
  - X Instantiate grid (nLines, nColumns, initValues)
    - X Generations Loop
      - grid.calcNextGen(mode)
      - increment gen counter
      - userinterface.output
      - check stop conditions
*/
