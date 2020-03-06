#include <iostream>
using namespace std;
#include <vector>

class Grid
{
    public:

    // Instance Variables
    int nRows;
    int nColumns;
    char *initValuesArr;

    bool gridStable = false;

    //Cell *cellArray;
    std::vector<Cell> cellArray;
    int *statusMap;

    //Constructor
    Grid(int rows, int columns, char *initVal){
      nRows = rows;
      nColumns = columns;
      initValuesArr = initVal;
      //cout << "in Grid() - nrows = " << nRows << " - ncolumns = " << nColumns << endl;
      initializeCellArray();
      populateGrid();
    }

    // Getters
    bool checkCellAlive(int ndx) {
      return cellArray[ndx].getAlive();
    }

    // Create empty cell array (grid)
    void initializeCellArray()
    {
      // cell array
      //Cell cx[3];
      //Cell cArr[nRows*nColumns];
      for (int i = 0; i < nRows; i++) {
          for (int j = 0; j < nColumns; j++){
            //cellArray[i*nColumns+j] = new Cell(i,j,false);
            cellArray.push_back(Cell(i,j,false));
          }
      }
      // status map
      statusMap = new int[nRows*nColumns];
      clearStatusMap();
    }

    // Empties status map array
    void clearStatusMap()
    {
      for (int i = 0; i < nRows; i++) {
          for (int j = 0; j < nColumns; j++){
            statusMap[i*nColumns+j] = 0;
          }
      }
    }
    //Populate grid
    void populateGrid()
    {
      for (int i = 0; i < nRows; i++) {
          for (int j = 0; j < nColumns; j++){
            //cout << " in populateGrid - initValuesArr - " << initValuesArr[i*nColumns+j] << endl;
            if (initValuesArr[i*nColumns+j] == 'X'){
              cellArray[i*nColumns+j].makeAlive();
              //cout << " in populateGrid - cellArray - " << cellArray[i*nColumns+j].getAlive() << endl;
            }
          }
      }
    }

    //Check stop conditions
    bool isEmpty(){
      bool rc = true;
      //cout << "in isEmpty() - nRows = " << nRows << " - nColumns = " << nColumns << endl;
      for (int i = 0; i < nRows; i++) {
          for (int j = 0; j < nColumns; j++){
            //cout << "in isEmpty - cellArray[" <<i << "," <<j <<"].getAlive() = " << cellArray[i*nColumns+j].getAlive() << endl;
            if (cellArray[i*nColumns+j].getAlive()) {
                rc = false;
                break;
            }
          }
      }
      return rc;
    }

    bool isStable(){
      return gridStable;
    }

    // Returns how many live neighbors a cell has depnding on mode
    int countLiveNeighbors(Cell cell, string mode){
      int r = cell.getXCoord();
      int c = cell.getYCoord();

      int leftc = c-1;
      int rightc = c+1;
      int upr = r-1;
      int downr = r+1;

      if ((leftc) < 0) {
        if (mode == "Classic") {
          // do nothing - cell will be counted as dead if x < 0
        } else if (mode == "Donut") {
          // calculate new leftc for donut
          leftc = nColumns - 1;
        } else {
          // calculate new leftc for mirror
          leftc = c;
        }
      }
      if ((rightc) >= nColumns) {
        if (mode == "Classic") {
          // do nothing, cell will be counted as dead if x > nColumns
        } else if (mode == "Donut") {
          // calculate new rightc for donut
          rightc = 0;
        } else {
          // calculate new rightc for mirror
          rightc = c;
        }
      }

      if ((upr) < 0) {
        if (mode == "Classic") {
          // do nothing
        }
        else if (mode == "Donut") {
          // calculate new upr for donut
          upr = nRows - 1;
        }
        else {
          // calculate new upr for mirror
          upr = r;
        }
      }

      if ((downr) >= nRows) {
        if (mode == "Classic") {
          // do nothing
        }
        else if (mode == "Donut") {
          // calculate new downr for donut
          downr = 0;
        }
        else {
          // calculate new downr for mirror
          downr = r;
        }
  }
      // Cells we need to check
        int tl = checkAlive(upr, leftc); // tl = (x-1, y-1)
        int tm = checkAlive(upr, c); //tm = (x, y-1)
        int tr = checkAlive(upr, rightc);  //tr = (x+1, y-1)
        int ml = checkAlive(r, leftc); //ml = (x-1, y)
        int mm = 0;
        if (mode == "Mirror") {
          int mm = checkAlive(r, c);
        }
        int mr = checkAlive(r, rightc); //mr = (x+1,y)
        int bl = checkAlive(downr, leftc); //bl = (x-1, y+1)
        int bm = checkAlive(downr, c); //bm = (x, y+1)
        int br = checkAlive(downr, rightc); //br = (x+1 y+1)

        return tl + tm + tr + ml + mr + bl + bm + br + mm;

    }

    // Check alive
    int checkAlive(int r, int c) {
      if (c >=0 && c < nColumns &&
          r >=0 && r < nRows) {
            //if it's in bounds
            return cellArray[r*nColumns+c].getAlive();
          } else {
            //if it's out of bounds - only happens when in Classic mode
            return 0;
          }
    }

    //Loops through cells in grid, calcSimStep for each cell
    void calcNextGen(string mode){
      clearStatusMap();
      for (int i = 0; i < nRows; i++) {
          for (int j = 0; j < nColumns; j++){
            calcSimStep(cellArray[i*nColumns+j], mode);
          }
       }
      // At this point, the statusMap contains the next generation, and needs to be "copied" to the grid
      gridStable = true;
      for (int i = 0; i < nRows; i++) {
          for (int j = 0; j < nColumns; j++){
            if (statusMap[i*nColumns+j] == 1) {
              if (!cellArray[i*nColumns+j].getAlive()) gridStable = false;
              cellArray[i*nColumns+j].makeAlive();
            } else {
              if (cellArray[i*nColumns+j].getAlive()) gridStable = false;
              cellArray[i*nColumns+j].makeDead();
            }
          }
      }
    }
    // Calculates whether cell should live or die in next gen, store in status map
    void calcSimStep(Cell cell, string mode){
      int liveN = countLiveNeighbors(cell, mode);
      int ndx = cell.getXCoord()*nColumns+cell.getYCoord();
      if (liveN <= 1){
        //Dies of lonliness
        statusMap[ndx] = 0;
      } else if (liveN == 2){
        //Stays the same
        statusMap[ndx] = cell.getAlive();
      } else if (liveN == 3){
        //Is born!
        statusMap[ndx] = 1;
      } else if (liveN >= 4) {
        //Dies of overcrowding
        statusMap[ndx] = 0;
      }
    }
};

/*
Grid Class:
  Attributes:
    - nLines
    - nColumns
    - initValuesArrs
  Methods:
    - X Check stop conditions
    - X Create (nLines X nColumns) cells and store in Array (each cell takes x, y, status)
    - X Create second (nLines X nColumns) array, call it statusmap
    - X Populate grid from initValuesArr
    - X calcNextGen (will go through the array of cells and call calcSimStep(cell, mode) for each cell)
    - X Output grid as per pause/enter/file
    - X countLiveNeighbors(cell, mode)
    - X calcSimStep(cell, mode)
      - Empty statusmap array
      - uses countLiveNeighbors(cell, mode) to populate the statusmap array
      - Loop over the map and update status of all grid cells
*/
