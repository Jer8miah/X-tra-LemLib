#include "declaration.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "lemlib/api.hpp"


//drivetrain motors
pros::Motor frontLeft(12, pros::E_MOTOR_GEARSET_06, true);
pros::Motor backLeft(15, pros::E_MOTOR_GEARSET_06, true);
pros::Motor topBackLeft(19, pros::E_MOTOR_GEARSET_06, true);
pros::Motor frontRight(1, pros::E_MOTOR_GEARSET_06, false);
pros::Motor backRight(9, pros::E_MOTOR_GEARSET_06, false);
pros::Motor topBackRight(6, pros::E_MOTOR_GEARSET_06, false);

//drivetrain motor groups
pros::MotorGroup leftSide({backLeft,topBackLeft,frontLeft});
pros::MotorGroup rightSide({backRight,topBackRight,frontRight});

// Inertial
pros::Imu imu(16);

// Opitcal 
//pros::Optical eyes(15);

// Full Wings
pros::ADIDigitalOut wings('D');

// Weak Wings
pros::ADIDigitalOut weakWings('B');

// Lift
pros::ADIDigitalOut lift('F');

// Intake
pros::Motor intake(14, pros::E_MOTOR_GEARSET_06, true);

//Mid Wing
pros::ADIDigitalOut midWing('C');

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Catapult
pros::Motor cata(18, pros::E_MOTOR_GEARSET_36, false);

lemlib::Drivetrain drivetrain (
    &leftSide,  // left drivetrain motors
    &rightSide, // left drivetrain motors
    14,         // Update track width !!!
    lemlib::Omniwheel::NEW_275,      // wheel diameter
    450,        // wheel rpm 
    5           // Chase power
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// forward/backward PID
// forward/backward PID
//#include "lemlib/controller_settings.hpp"

lemlib::ControllerSettings linearController(25, // proportional gain (kP)
                                            1, // integral gain (kI)
                                            29, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            16 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(13, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             48, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors );