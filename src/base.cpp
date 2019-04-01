#include "main.h"
static int maxBaseVelocity = 200;
static int brakeBaseVelocity = -10;
static int setdistance;
static int slant = 0;
static int maxspeed = 127;
static int distance = 0;
//DEFINING MOTORS
Motor leftDrive(1, MOTOR_GEARSET_18, 0,  MOTOR_ENCODER_DEGREES);
Motor leftDrive1(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor rightDrive(10, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);
Motor rightDrive1(9, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);


/************************************LCD STUFF***********************************************/
int getDistance()
{
  return leftDrive.get_position();
}

int getBatteryLevel()
{
  return battery::get_capacity();
}

int getRightEfficiency()
{
  return rightDrive.get_efficiency();
  return rightDrive1.get_efficiency();
}

int getLeftEfficiency()
{
  return leftDrive.get_efficiency();
  return leftDrive1.get_efficiency();
}
/************************************Driver Control***********************************************/
int count = 1;
void driveOP()
{
  if(controller.get_digital(DIGITAL_UP) == 1)
  {
 count = 2;
  }

  if(controller.get_digital(DIGITAL_DOWN) == 1)
  {
 count = 1;
  }

  if(count == 1)
  {
    setCurrent(2500);
    leftDrive.set_brake_mode(MOTOR_BRAKE_COAST);
    leftDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
    rightDrive.set_brake_mode(MOTOR_BRAKE_COAST);
    rightDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
    leftDrive.move(controller.get_analog(ANALOG_LEFT_Y));
    leftDrive1.move(controller.get_analog(ANALOG_LEFT_Y));
    rightDrive.move(controller.get_analog(ANALOG_RIGHT_Y));
    rightDrive1.move(controller.get_analog(ANALOG_RIGHT_Y));
  }

  if(count == 2)
  {

    setCurrent(2500);
    leftDrive.set_brake_mode(MOTOR_BRAKE_COAST);
    leftDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
    rightDrive.set_brake_mode(MOTOR_BRAKE_COAST);
    rightDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
    leftDrive.move(-controller.get_analog(ANALOG_RIGHT_Y));
    leftDrive1.move(-controller.get_analog(ANALOG_RIGHT_Y));
    rightDrive.move(-controller.get_analog(ANALOG_LEFT_Y));
    rightDrive1.move(-controller.get_analog(ANALOG_LEFT_Y));
  }
}
/************************************Autonoumus STUFF***********************************************/
void left(int vel){
  leftDrive.move(vel);
  leftDrive1.move(vel);
}

void right(int vel){
  rightDrive.move(vel);
  rightDrive1.move(vel);
}

void resetDrive()
{
  leftDrive.tare_position();
  leftDrive1.tare_position();
  rightDrive.tare_position();
  rightDrive1.tare_position();
}

void resetAll()
{
  resetDrive();
  maxspeed = 127;
  slant = 0;
}

 void setCurrent(int current)
 {
     leftDrive.set_current_limit(current);
     leftDrive1.set_current_limit(current);
     rightDrive.set_current_limit(current);
     rightDrive1.set_current_limit(current);
 }

void setSlant(int s)
{
  if(mirror.get_value())
  {
    s = -s;
  }
   slant = s;
}

void setSpeed(int speed)
{
  maxspeed = speed;
}

void leftSlew(int slewSpeed)
{
  int step;
  static int speed = 0;
  if(abs(speed) < abs(slewSpeed))
  {
    step = 5;
  }
  else
  {
    step = 256; // no slew
  }


  if(speed < slewSpeed - step)
  {
    speed += step;
  }
  else if(speed > slewSpeed + step)
  {
    speed -= step;
  }
  else
  {
    speed = slewSpeed;
  }

   left(speed);
}

void rightSlew(int slewSpeed)
{
  int step;
  static int speed = 0;
  if(abs(speed) < abs(slewSpeed))
  {
    step = 5;
  }
  else
  {
    step = 256; // no slew
  }


  if(speed < slewSpeed - step)
  {
    speed += step;
  }
  else if(speed > slewSpeed + step)
  {
    speed -= step;
  }
  else
  {
    speed = slewSpeed;
  }

   right(speed);
}

bool isDriving()
{
  static int count = 0;
  static int last = 0;
  static int lastTarget = 0;

  int leftPos = leftDrive.get_position();
  int rightPos = rightDrive.get_position();

  int curr = (abs(leftPos) + abs(rightPos))/2;
  int thresh = 4;
  int target = distance;

  if(abs(last-curr) < thresh)
    count++;
  else
    count = 0;

  if(target != lastTarget)
    count = 0;

  lastTarget = target;
  last = curr;

  //not driving if we haven't moved
  if(count > 9)
    return false;
  else
    return true;
}


void drivePID(int inches)
{
  resetDrive();
  double kd = 0.7; //2x kp
  double kp = 0.4;
  distance = inches*(360/14.125);
  leftDrive.set_brake_mode(MOTOR_BRAKE_COAST);
  leftDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
  rightDrive.set_brake_mode(MOTOR_BRAKE_COAST);
  rightDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
  while(isDriving())//leftDrive.get_position() < distance - 12 || leftDrive.get_position() > distance + 12)
    {
      setCurrent(2500);
      int error = distance - leftDrive.get_position();
      int prevError = error;
      int derivative = prevError - error;
      int speed = error*kp + derivative*kd;
      //sets max speed of motors
      if(speed > maxspeed)
     speed = maxspeed;
     if(speed < -maxspeed)
     speed = -maxspeed;
     if(speed > 0 && speed < 20)
     speed = 20;
     if(speed < 0 && speed >-20)
     speed = -20;

      //iniates drive motors
      leftSlew(speed - slant);
      rightSlew(speed + slant);

      delay(20);
    }
    leftSlew(0);
    rightSlew(0);
}

void turnPID(int deg)
{
  leftDrive.set_brake_mode(MOTOR_BRAKE_COAST);
  leftDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
  rightDrive.set_brake_mode(MOTOR_BRAKE_COAST);
  rightDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
  resetDrive();
 if(mirror.get_value())
 {
   deg = -deg;
 }
 int speed;
 // both should be higher
 double kd = 3.7; //4x kp
 double kp = 0.8;
 int error;
 int derivative;
 int prevError;
 int target = deg*3.29;
 do{
   setCurrent(400);
   error = target - ((rightDrive.get_position() - leftDrive.get_position())/2);
   derivative = prevError - error;
   prevError = error;
   speed = error*kp + derivative*kd;
   left(-speed);
   right(speed);
   printf("%d\n", error);
   delay(20);
 }while(isDriving());
 left(0);
 right(0);
}

void turnFastPID(int deg)
{
  leftDrive.set_brake_mode(MOTOR_BRAKE_COAST);
  leftDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
  rightDrive.set_brake_mode(MOTOR_BRAKE_COAST);
  rightDrive1.set_brake_mode(MOTOR_BRAKE_COAST);
  resetDrive();
 if(mirror.get_value())
 {
   deg = -deg;
 }
 int speed;
 // both should be higher
 double kd = 2.0;//3.7; //4x kp
 double kp = 0.5;//0.8;
 int error;
 int derivative;
 int prevError;
 int target = deg*3.29;
 do{
   //setCurrent(400);
   error = target - ((rightDrive.get_position() - leftDrive.get_position())/2);
   derivative = prevError - error;
   prevError = error;
   speed = error*kp + derivative*kd;
   left(-speed);
   right(speed);
   printf("%d\n", error);
   delay(20);
 }while(isDriving());
 left(0);
 right(0);
}

void driveHard(int inches)
{
  leftDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
  leftDrive1.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightDrive.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightDrive1.set_brake_mode(MOTOR_BRAKE_HOLD);
  resetDrive();
  int distance = inches*(360/14.125);
  if(distance > 0)
  {
    leftDrive.move_velocity(maxBaseVelocity);
    leftDrive1.move_velocity(maxBaseVelocity);
    rightDrive.move_velocity(maxBaseVelocity);
    rightDrive1.move_velocity(maxBaseVelocity);

    while(leftDrive.get_position() < distance)
    {
      delay(2);
    }

    leftDrive.move_velocity(brakeBaseVelocity);
    leftDrive1.move_velocity(brakeBaseVelocity);
    rightDrive.move_velocity(brakeBaseVelocity);
    rightDrive1.move_velocity(brakeBaseVelocity);

    delay(10);

    leftDrive.move_velocity(0);
    leftDrive1.move_velocity(0);
    rightDrive.move_velocity(0);
    rightDrive1.move_velocity(0);
  }
  if(distance < 0)
  {
    leftDrive.move_velocity(-maxBaseVelocity);
    leftDrive1.move_velocity(-maxBaseVelocity);
    rightDrive.move_velocity(-maxBaseVelocity);
    rightDrive1.move_velocity(-maxBaseVelocity);

    while(leftDrive.get_position() > distance)
    {
      delay(2);
    }

    leftDrive.move_velocity(-brakeBaseVelocity);
    leftDrive1.move_velocity(-brakeBaseVelocity);
    rightDrive.move_velocity(-brakeBaseVelocity);
    rightDrive1.move_velocity(-brakeBaseVelocity);

    delay(10);

    leftDrive.move_velocity(0);
    leftDrive1.move_velocity(0);
    rightDrive.move_velocity(0);
    rightDrive1.move_velocity(0);
  }
}
