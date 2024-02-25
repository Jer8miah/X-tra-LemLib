#include "pros/imu.hpp"
#include "robot.h"
#include "pros/rotation.hpp"

pros::Imu Robot::Sensors::imu {16};
pros::Rotation Robot::Sensors::vertTracker{3, false};