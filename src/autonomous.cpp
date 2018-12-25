#include "main.h"

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

void blueFront()
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
turnPID(90);
shoot();
}
