#include "main.h"

//jumpers
ADIDigitalIn autonClose('B');
ADIDigitalIn autonFar('C');
ADIDigitalIn mirror('A');
ADIDigitalIn skill('D');

void skills()
{
  shoot();
}

void back()
{
  shoot();
}
//program red first then tweak blue if it doesnt work. look at micha's repo for the vartion of each side
void front()
{
  shoot();
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
