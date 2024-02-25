#include "autonGlobals/autonSelector.hpp"
#include "lemlib/asset.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "robot.h"
ASSET(j_txt);
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// Init debug screen for auton
    //debugInit();
	//Robot::chassis->setPose({0, 0, 0});
	//Robot::chassis->moveToPoint(0, 7, 2000);
	//Robot::chassis->moveToPoint(0, 0, 2000, false);
	Robot::chassis->turnTo(1000,0,1000);

	//Robot::chassis->follow(j_txt,6, 2000);
    switch (autonSelection) {
		// Solo autons
		case RED_1: // Main auton - Auton Near Side , 



			break;
		case RED_2: // Outside auton starting line
			//Drop down mid wing
			//chassis.moveToPose(, float y, float theta, int timeout)
			//chassis.moveTo();
			break;
		case RED_3:


			break;
		case RED_4:


			break;

		case RED_5:
			//chassis.moveTo(20, 20, 2000);
			break;

		// Duo
		case BLUE_1:
			break;
		case BLUE_2:
			break;
		case BLUE_3:
			break;
		case BLUE_4:
			break;
		case BLUE_5:
			break;
			
		case SKILLS:


		case TEST:
			//test();

			//chassis.setPose(
			break;
	}
}