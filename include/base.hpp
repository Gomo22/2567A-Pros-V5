#ifndef _BASE_H_
#define _BASE_H_

void driveMax(int inches);
void turn(int degrees);
void resetDrive();
void drive(int inches);
void driveOP();
void drivePID(int inches);
void turnPID(int deg);
void right(int vel);
void left(int vel);
int getDistance();
int getBatteryLevel();
#endif
