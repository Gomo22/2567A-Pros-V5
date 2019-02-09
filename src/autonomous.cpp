#include "main.h"
//jumpers
ADIDigitalIn autonClose('B');
ADIDigitalIn autonFar('C');
ADIDigitalIn mirror('A');
ADIDigitalIn skill('D');
ADIDigitalIn test('E');

void tests()
{

//  drivePID(20);
  //shootC();
  suck(1000);

}
void skills()
{
  loadPuncher();
  suck(1500);
  drivePID(53);
  drivePID(-53);
  drivePID(2);
  turnPID(88);
  suck(300);
  drivePID(-6);
  shoot();
  suck(700);
  drivePID(24);
  suck(400);
  delay(600);
  shoot();
  turnPID(10);
  suck(1300);
  drivePID(24);
  drivePID(-24);
  turnPID(-90);
  suck(-1500);
  drivePID(33);
  turnPID(-100);
  drivePID(34);
  delay(750);
  drivePID(20);
  turnPID(90);
  drivePID(29);
}

void back()
{
shoot();
if(mirror.get_value())
{
  turnPID(-60);
}
else
{
turnPID(-65);
}
suck(1500);
drivePID(50);
drivePID(-25);
suck(700);
if(mirror.get_value())
{
  turnPID(-35);
}
else
{
  turnPID(-45);
}
drivePID(23);
suck(-800);
drivePID(12);
drivePID(-18);
turnPID(135);
drivePID(22);
}
//program red first then tweak blue if it doesnt look. look at micha's repo for the vartion of each side
void front()
{
  loadPuncher();
  suck(1700);
  drivePID(52);
  delay(200);
  drivePID(-53);
  drivePID(2);
  if(mirror.get_value())
  {
    turnPID(85);
  }
  else
  {
  turnPID(88);
  }
  suck(300);
  drivePID(-2);
  shoot();
  if(mirror.get_value())
  {
    turnPID(7);
  }
  suck(700);
  drivePID(28);
  suck(400);
  delay(600);
  shoot();
  if(mirror.get_value())
  {
    turnPID(15);
  }
  else
  {
  turnPID(10);
  }
  suck(1300);
  drivePID(24);
  drivePID(-27);
  turnPID(-93);
  suck(-1500);
  drivePID(33);
  if(mirror.get_value())
  {
    turnPID(60);
  }
  else
  {
  turnPID(70);
  }
  drivePID(10);
  shoot();
  if(mirror.get_value())
  {
    turnPID(25);
  }
  drivePID(20);
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
  else if(test.get_value())
  {
    tests();
  }
  else
  {
    right(0);
    left(0);
  }
}
