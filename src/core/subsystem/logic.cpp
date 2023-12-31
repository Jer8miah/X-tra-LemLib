#include "declaration.hpp"
#include "main.h"

// Brain debug info screen
void debugInit() {
    pros::Task task{[=] {
        pros::lcd::initialize();

        while (true) {
            lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
            pros::lcd::print(0, "x: %f", pose.x); // print the x position
            pros::lcd::print(1, "y: %f", pose.y); // print the y position
            pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
            pros::delay(10);
        }
    }};
}