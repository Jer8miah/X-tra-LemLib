#include "declaration.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "lemlib/api.hpp"
#include "pros/rotation.hpp"
#include <cstddef>


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

// Inertial
pros::Imu imu(16);

// Opitcal 
//pros::Optical eyes(15);

// Full Wings
pros::ADIDigitalOut wings('D');

// Weak Wings
pros::ADIDigitalOut backWings('B');

// Lift
pros::ADIDigitalOut lift('F');

pros::Rotation vertTracker(2,false);
lemlib::TrackingWheel vert_tracking_wheel(&vertTracker, lemlib::Omniwheel::NEW_275,-.5);

pros::Rotation horizTracker(3,false);
lemlib::TrackingWheel horiz_tracking_wheel(&horizTracker, lemlib::Omniwheel::OLD_275,0);

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
    12.2,         // Update track width !!!
    lemlib::Omniwheel::NEW_275,      // wheel diameter
    450,        // wheel rpm 
    4           // Chase power
);

lemlib::OdomSensors sensors(&vert_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// forward/backward PID
// forward/backward PID
//#include "lemlib/controller_settings.hpp"

lemlib::ControllerSettings linearController(19, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            16, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2.5, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             15, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors );