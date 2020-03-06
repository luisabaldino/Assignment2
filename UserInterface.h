#include <iostream>
using namespace std;
#include <fstream>
#include <unistd.h>

class UserInterface {

  public:

      ifstream inFile;
      ofstream outFile;
      string line;

      // User input variables
      string outputOption;
      string mode;
      bool randomGrid;
      float seed;
      int rows;
      int columns;
      string initialGridFile;
      string outputFileName;

      char *initValuesArr;

      //Getters
      string getoutputOption(){
        return outputOption;
      }
      string getMode(){
        return mode;
      }
      int getRows(){
        return rows;
      }
      int getColumns(){
        return columns;
      }
      char* getInitValuesArr(){
        //cout << "in getInitValuesArr - " << initValuesArr << endl;
        return initValuesArr;
      }

  // Get user input
  void getUserInput() {
     cout << "Welcome to the game of life! \n\n";
     cout << "How would you like to output the grids? Pause/Enter/File? \n";
     cin >> outputOption;
     if (outputOption == "File"){
     cout << "What is the name of the file you would like to output the grids to (no extension)?" << endl;
     cin >> outputFileName;
     }

     cout << "What boundary conditions would you like to use? Classic/Donut/Mirror?  \n";
     cin >> mode;

     cout << "Would you like to use a random grid? Y/N? \n";
     string yesOrNo;
     cin >> yesOrNo;
     if (yesOrNo == "Y") randomGrid = true;
     else randomGrid = false;

     if (randomGrid) {
       cout << "Pick the (integer) dimmensions for the grids. Rows: \n";
       cin >> rows;

       cout << "Columns: \n";
       cin >> columns;

       cout << "Pick an initial population density. Decimal between 0-1. \n";
       cin >> seed;

       //cout << "in getUserInput() - rows = " << rows << " - columns = " << columns << endl;

       // Create and populate 2dim array with random - and X
       this->initValuesArr = new char[rows*columns];

       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < columns; j++){
             initValuesArr[i*columns+j] = '-';
             }
           }
        // For each position in the array, get a rand between 0 and 1 and use it to match the seed
         for (int i = 0; i < rows; i++) {
             for (int j = 0; j < columns; j++){
               double rndval = (double)rand()/RAND_MAX;
               if (rndval >= seed) {
                 initValuesArr[i*columns+j] = '-';
               } else {
                 initValuesArr[i*columns+j] = 'X';
               }
               //cout << "initValuesArr Randomly created - " << initValuesArr[i*columns+j] << endl;
             }
          }
     } else {
       // Not a random grid: create and populate 2dim array with given values
       cout << "Whats the name of the .txt file with your initial grid (no extension)\n";
       cin >> initialGridFile;
       inFile.open(initialGridFile + ".txt");
       getline (inFile, line);
       rows = stoi(line);
       getline (inFile, line);
       columns = stoi(line);
       cout << rows << "  " << columns << endl;
       if (rows > 0 && columns > 0) {
         this->initValuesArr = new char[rows*columns];
         for (int i = 0; i < rows; i++) {
             getline (inFile, line);
             for (int j = 0; j < columns; j++){
               initValuesArr[i*columns+j] = line[j];
             }
         }
       }
       inFile.close();
     }
   }

   void output(Grid *grid, int genNumber){
     cin.clear();
     if (outputOption == "File") {
       //Output to file - appending
       outFile.open(outputFileName + ".txt", std::ios_base::app);
       outFile << genNumber;
       for (int i = 0; i < rows; i++) {
         outFile << "\n";
         for (int j = 0; j < columns; j++){
           if (grid->checkCellAlive(i*columns+j)){
             outFile << "X";
           } else {
             outFile << "-";
           }
         }
       }
       outFile << "\n";
       outFile.close();
     } else {
       //Output to screen
       cout << genNumber;
       for (int i = 0; i < rows; i++) {
         cout << "\n";
         for (int j = 0; j < columns; j++){
           if (grid->checkCellAlive(i*columns+j)){
             cout << "X";
           } else {
             cout << "-";
           }
         }
       }
       cout << endl;
       // Check if they press enter
       if (outputOption == "Enter") {
         cin.clear();
         cin.ignore();
         cout << "Please press enter to continue.";
         cin.clear();
         cin.ignore();
       // Wait 3 seconds
       } else {
         usleep(3000000);
       }
     }
   }
};
