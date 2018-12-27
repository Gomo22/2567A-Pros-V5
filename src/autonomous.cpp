#include "main.h"

//jumpers
ADIDigitalIn autonClose('B');
ADIDigitalIn autonFar('C');
ADIDigitalIn mirror('A');

void skills()
{
shoot();
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
{ /*
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
  } */

  drivePID(56);
  drivePID(-56);
}
