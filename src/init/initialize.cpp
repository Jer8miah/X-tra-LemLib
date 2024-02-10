#include "main.h"
/*
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 
void initialize(){
    //selectorInit();
    pros::lcd::initialize();
    

    pros::Task chassisCalibrateTask{[=] {
         chassis.calibrate();
    }};
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
    debugInit();
}