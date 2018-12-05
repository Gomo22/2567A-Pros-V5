#include "main.h"

void autonomous()
{
//drives to cap and flips it
suck(800); //run suck before drive to have it run while drive
drive(40);
//reverse and turn to next cap
drive(-24);
turn(45);
//drives to cap and flips it
drive(24);
suck(800);
}
