#include "main.h"

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
    debugInit();

    switch (autonSelection) {
		// Solo autons
		case RED_1: // Main auton - 2 rollers, 
			test();
			break;
		case RED_2: // Outside auton starting line

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
			break;

		case TEST:
			test();

			//chassis.setPose(
			break;
	}
}