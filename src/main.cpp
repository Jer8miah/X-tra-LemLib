#include "main.h"
#include "declaration.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}







/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {


	while (true) {

		chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		//pros::lcd::print(0,"Hue value: %lf", eyes.get_hue());
		
		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			cata.move_velocity(-100);
		}
		else {
			cata.brake();
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			Intake.move_velocity(100);
		} else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
			Intake.move_velocity(-100);
		}
		else {
			Intake.brake();
		}

		//if (eyes.get_hue() == )


		pros::delay(10);
	}
}
