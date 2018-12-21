#ifndef _BASE_H_
#define _BASE_H_

void driveOP();
void drive(int inches);
void driveMax(int inches);
void turn(int degrees);
void resetDrive();
void right(int vel);
void left(int vel);
int getDistance();
int getBatteryLevel();

#endif
