#pragma once

#include "main.h"
#include "pros/adi.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"

// Controller
extern pros::Controller master;

// Drivetrain
extern pros::Motor frontLeft;
extern pros::Motor backLeft;
extern pros::Motor topBackLeft;
extern pros::Motor frontRight;
extern pros::Motor backRight;
extern pros::Motor topBackRight;

extern pros::MotorGroup leftSide;
extern pros::MotorGroup rightSide;

extern lemlib::Chassis chassis;

// Inertial
extern pros::Imu imu;

// Cata
extern pros::Motor cata;

// Optical
extern pros::Optical eyes;

// Intake
extern pros::Motor Intake;

//Lift
extern pros::ADIDigitalOut lift;
