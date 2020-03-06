#include <iostream>
using namespace std;

class Cell
{
    // Access specifier
    public:

    // Data Members
    int alive;
    int xcoord;
    int ycoord;

    //Constructor
    Cell(int x, int y, bool status){
      xcoord = x;
      ycoord = y;
      alive = status;
    }

    // Give birth to cell
    void makeAlive()
    {
       alive = 1;
    }
    // Kill cell
    void makeDead()
    {
       alive = 0;
    }

    // Alive getter
    int getAlive(){
      return alive;
    }

    //Coordinate setters
    void setXCoord(int x)
    {
       xcoord = x;
    }
    void setYCoord(int y)
    {
       ycoord = y;
    }

    //Coordinate getters
    int getXCoord()
    {
       return xcoord;
    }
    int getYCoord()
    {
       return ycoord;
    }
};

/*
Cell Class:
  Attributes
    - alive
    - xcoord
    - ycoord
  Methods
    - Coord Getter
    - changeStatus(bool)
*/
