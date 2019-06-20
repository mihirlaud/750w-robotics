#include "vex.h"

class Robot {

  private:
    int x, y;
  
  public:
    Robot(int x_pos, int y_pos);

    int getX();
    void setX(int newX);

};