#include "robot.h"
#include "lemlib/chassis/trackingWheel.hpp"

const float Robot::Dimensions::trackWidth = 12.5;
const float Robot::Dimensions::driveWheelDiameter = lemlib::Omniwheel::NEW_275;
const float Robot::Dimensions::driveWheelRpm = 450;
const float Robot::Dimensions::driveEncRatio = 1;

const float Robot::Dimensions::vertEncDiameter = lemlib::Omniwheel::NEW_275;
const float Robot::Dimensions::vertEncDistance = 0;
const float Robot::Dimensions::vertEncGearRatio = 1;