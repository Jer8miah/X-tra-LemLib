#include "main.h"


//drivetrain motors
pros::Motor frontLeft(12, pros::E_MOTOR_GEARSET_06, true);
pros::Motor backLeft(15, pros::E_MOTOR_GEARSET_06, true);
pros::Motor topBackLeft(19, pros::E_MOTOR_GEARSET_06, false);
pros::Motor frontRight(1, pros::E_MOTOR_GEARSET_06, false);
pros::Motor backRight(9, pros::E_MOTOR_GEARSET_06, false);
pros::Motor topBackRight(6, pros::E_MOTOR_GEARSET_06, true);

//drivetrain motor groups
pros::MotorGroup leftSide({backLeft,topBackLeft,frontLeft});
pros::MotorGroup rightSide({backRight,topBackRight,frontRight});

// Inertial
pros::Imu imu(16);



pros::Controller master(pros::E_CONTROLLER_MASTER);

//
pros::Motor cata(18, pros::E_MOTOR_GEARSET_36, false);

lemlib::Drivetrain_t drivetrain {
    &leftSide,  // left drivetrain motors
    &rightSide, // left drivetrain motors
    15,         // Update track width !!!
    4.125,      // wheel diameter
    300,        // wheel rpm 
    5
};

lemlib::OdomSensors_t odomSensors {
    nullptr, // left encoder
    nullptr, // right encoder
    nullptr, // back encoder
    nullptr, // front encoder
    &imu // imu
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    9, // kP
    31, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, odomSensors);