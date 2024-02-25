#include "robot.h"
#include "main.h"
#include <string>
#include "driverFeedback.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
// Brain debug info screen
/*void debugInit() {
    pros::Task task{[=] {
        pros::lcd::initialize();

        while (true) {
            lemlib::Pose pose = Robot::chassis->getPose(); // get the current position of the robot
            pros::lcd::print(0, "x: %f", pose.x); // print the x position
            pros::lcd::print(1, "y: %f", pose.y); // print the y position
            pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
            pros::delay(10);
        }
    }};
}*/




DriverFeedback* Robot::Subsystems::feedback = nullptr;
ControllerScreen* Robot::Subsystems::master = nullptr;

pros::Task* Robot::Subsystems::task = nullptr;

void Robot::Subsystems::initialize() {

  // Robot::Subsystems::feedback = new DriverFeedback();
  Robot::Subsystems::master = new ControllerScreen(&Robot::master);

  Robot::Subsystems::task = new pros::Task([]() {
    while (true) {
      const int start = pros::millis();
      Robot::Subsystems::update();
      // const int a = pros::millis();
      // printf("update took %i ms\n", a - start);
      pros::delay(10);
      // pros::delay(MIN_MILLIS_BETWEEN_UPDATES - (a - start));
    }
  });
}

void Robot::Subsystems::update() {
  // printf("updating feedback: %i\n", Robot::Subsystems::feedback == nullptr);
  // Robot::Subsystems::feedback->update();
  // printf("updating catapult\n");

  // printf("updating lift\n");
  // we no longer have a motorized lift
  //Robot::Subsystems::lift->update();
  // printf("updating controller\n");
  // Robot::Subsystems::controller->update();
}