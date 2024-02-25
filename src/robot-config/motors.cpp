#include "pros/motors.h"
#include "pros/motors.hpp"
#include "robot.h"

//drivetrain motors
pros::Motor frontLeft(12, pros::E_MOTOR_GEARSET_06, false);
pros::Motor backLeft(15, pros::E_MOTOR_GEARSET_06, false);
pros::Motor midLeft(19, pros::E_MOTOR_GEARSET_06, false);
pros::Motor frontRight(1, pros::E_MOTOR_GEARSET_06, true);
pros::Motor backRight(9, pros::E_MOTOR_GEARSET_06, true);
pros::Motor midRight(6, pros::E_MOTOR_GEARSET_06, true);

//drivetrain motor groups
pros::MotorGroup leftSide({backLeft,midLeft,frontLeft});
pros::MotorGroup rightSide({backRight,midRight,frontRight});

//Lift
pros::Motor lift(3, pros::E_MOTOR_GEARSET_36, false);

//intake
pros::Motor intakeA(14, pros::E_MOTOR_GEAR_600, true);

// Robot Group
pros::Motor_Group Robot::Motors::leftSide {frontLeft, midLeft, backLeft};
pros::Motor_Group Robot::Motors::rightSide {frontRight, midRight, backRight};
pros::Motor Robot::Motors::intake {intakeA};