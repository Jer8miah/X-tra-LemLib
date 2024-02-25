#include "lemlib/chassis/chassis.hpp"
#include "robot.h"

lemlib::ControllerSettings Robot::Tuneables::lateralController {
                        10, // proportional gain (kP)
                        0, // integral gain (kI)   
                        3, // derivative gain (kD)
               3, // anti windup
                1, // small error range, in inches
         100, // small error range timeout, in milliseconds
                3, // large error range, in inches
         500, // large error range timeout, in milliseconds
                      20 // maximum acceleration (slew)    
};

lemlib::ControllerSettings Robot::Tuneables::angularController{
                                             2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
};

const float Robot::Tuneables::chasePower = 4;