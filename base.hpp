#ifndef _BASE_H_
#define _BASE_H_

void resetDrive();
void driveOP();
void drivePID(int inches);
void turnPID(int deg);
void right(int vel);
void left(int vel);
void setCurrent(int current);
void variableSpeedDrive(int inches , int speed);
int getDistance();
int getBatteryLevel();
int getLeftEfficiency();
int getRightEfficiency();

#endif
