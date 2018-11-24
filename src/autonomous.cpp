#include "main.h"

void autonomous()
{
//drives to cap and flips it
driveAsync(40);
suck(800);
//reverse and turn to next cap
drive(-24);
turn(45);
//drives to cap and flips it
driveAsync(24);
suck(800);
}
