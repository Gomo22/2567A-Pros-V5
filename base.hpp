
#ifndef _BASE_H_
#define _BASE_H_

void resetDrive();
void resetAll();
void setSlant(int s);
void setSpeed(int speed);
void setCurrent(int current);
void driveOP();
void right(int vel);
void left(int vel);
void drivePID(int inches);
void turnPID(int deg);
int getDistance();
int getBatteryLevel();
int getLeftEfficiency();
int getRightEfficiency();
#endif
