#include "declaration.hpp"
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
		case RED_1: // Main auton - Auton Near Side , 
			//test();
			chassis.setPose(-35,-63,180);
			chassis .moveTo(-60,-25, 225, 1000);
			chassis.waitUntilDist(2);
			chassis.moveTo(-60, -20, 225, 1000, true);
			intake.move_absolute(360, -100);

			chassis.turnTo(-30, -20, 1000);
			chassis.moveTo(-60, 44, 75, 1000);

			midWing.set_value(true);
			chassis.moveTo(-44, -65, 180,1000);
			pros::delay(500);
			midWing.set_value(false);

			chassis.moveTo(-2, -55, 180, 1000);
			wings.set_value(true);

			break;
		case RED_2: // Outside auton starting line
			//Drop down mid wing
			chassis.moveTo();
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
			//test();

			//chassis.setPose(
			break;
	}
}