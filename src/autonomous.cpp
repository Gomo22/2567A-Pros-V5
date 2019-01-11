#include "main.h"

//jumpers
ADIDigitalIn autonClose('B');
ADIDigitalIn autonFar('C');
ADIDigitalIn mirror('A');
ADIDigitalIn skill('D');

void skills()
{
  suck(600);
  shoot();
}

void back()
{
  suck(-600);
  shoot();
}
//program red first then tweak blue if it doesnt work. look at micha's repo for the vartion of each side
void front()
{
  turnPID(90);
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
  else if(skill.get_value())
  {
    skills();
  }
  else
  {
    right(0);
    left(0);
  }
}
