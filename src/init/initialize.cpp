#include "main.h"
#include "robot.h"
/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void screen(){
  // loop forever
  Robot::master.clear_line(0);
  Robot::master.clear_line(1);
  Robot::master.clear_line(2);
  float lastHeading = 0;
  while (true) {
    lemlib::Pose pose =
        Robot::chassis->getPose(); // get the current position of the robot

    pros::lcd::clear_line(1);
    pros::lcd::print(1, "x: %f in", pose.x); // print the x position
    pros::lcd::clear_line(2);
    pros::lcd::print(2, "y: %f in", pose.y); // print the y position
    pros::lcd::clear_line(3);
    pros::lcd::print(3, "heading: %f deg", pose.theta); // print the heading
    
    lastHeading = Robot::chassis->getPose().theta;
    pros::delay(20);
  }
}

pros::Task* screenTask;

void initialize(){
    //selectorInit();
    pros::lcd::initialize();
    Robot::initializeOdometry();
    
    Robot::chassis->calibrate(true); // calibrate the chassis

    pros::lcd::set_text(1, "Calibrating Chassis");
    Robot::Subsystems::initialize();
    pros::lcd::set_text(1, "Chassis Calibrated");

    new pros::Task {screen};
/*
    pros::Task chassisCalibrateTask{[=] {
         Robot::chassis->calibrate();
    }};
    */
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    //selectorInit();
    //debugInit();
}