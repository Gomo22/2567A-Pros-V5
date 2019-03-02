#include "main.h"
//jumpers
ADIDigitalIn autonClose('B');
ADIDigitalIn autonFar('C');
ADIDigitalIn mirror('A');
ADIDigitalIn skill('D');
ADIDigitalIn test('E');

void tests()
{
  shoot();
  //drivePID(20);
  //shootC();
  //suck(1000);
}
void skills()
{
  setSpeed(100);
  drivePID(44);
  suck(-400);
  drivePID(7);
  delay(200);
  suck(1000);
  delay(400);
  setSpeed(200);
  drivePID(-53);
  drivePID(4);
  turnPID(87);
  drivePID(60);
  shoot();
  adjust(true);
  suck(1000);
  delay(900);
  shoot();
  drivePID(-9);
  turnPID(-90);
  drivePID(-8);
  setSpeed(100);
  drivePID(44);
  suck(-400);
  drivePID(10);
  delay(200);
  suck(1000);
  delay(400);
  setSpeed(200);
  drivePID(-55);
  drivePID(3);
  turnPID(90);
  suck(800);
  drivePID(48);
  drivePID(-26);
  turnPID(-93);
  drivePID(-7);
  suck(-1350);
  drivePID(45);
  setSpeed(200);
  turnPID(60);
  adjust(false);
  shoot();
  turnPID(25);
  drivePID(30);
}
void back()
{

}
//program red first then tweak blue if it doesnt look. look at micha's repo for the vartion of each side
void front()
{
  //loadPuncher();
  suck(2300);
  drivePID(53);
  delay(200);
  drivePID(-55);
  drivePID(4);
  if(mirror.get_value())
  {
    turnPID(88);
  }
  else
  {
  turnPID(88);
  }
  drivePID(8);
  shoot();
  adjust(true);
  suck(900);
  delay(800);
  shoot();
  if(mirror.get_value())
  {
    turnPID(10);
  }
  else
  {
    turnPID(10);
  }
  suck(2500);
  drivePID(47);
  suck(1400);
  drivePID(-27);
  turnPID(-93);
  setSpeed(150);
  suck(-1150);
  drivePID(35);
  setSpeed(200);
  turnPID(70);
  drivePID(30);
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
