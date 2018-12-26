#include "main.h"

//jumpers
ADIDigitalIn autonClose('B');
ADIDigitalIn autonFar('C');
ADIDigitalIn mirror('A');

void skills()
{
  //drives to cap and flips it
  suck(800); //run suck before drive to have it run while drive
  drive(40);
  //reverse and turn to next cap
  drive(-24);
  turn(45);
  //drives to cap and flips it
  suck(800);
  drive(24);
}

void back()
{
  shoot();
}
//program red first then tweak blue if it doesnt look. look at micha's repo for the vartion of each side
void front()
{
  shoot();
  suck(2000);
  drivePID(56);
  suck(400);
  drivePID(-12);
  turnPID(-90);
  suck(1000);
  drivePID(24);
}

void autonomous()
{
  if(autonClose.get_value())
  {
    front();
  }
  else if(autonFar.get_value())
  {
    back();
  }
  else
  {
    skills();
  }
}
