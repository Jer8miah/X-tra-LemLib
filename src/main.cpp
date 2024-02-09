#include "main.h"
#include "declaration.hpp"
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
	bool status_lift = false;
	bool status_wings = false;
	bool status_weak_wings = false;

	while (true) {
		
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			chassis.tank(pros::E_CONTROLLER_ANALOG_LEFT_Y, pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		}else {
			chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		}
		//pros::lcd::print(0,"Hue value: %lf", eyes.get_hue());
		//lift.set_value(false);
		
		//Cata movement
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			cata.move_velocity(-60);
		}
		else {
			cata.brake();
		}

		// Intake movement
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			intake.move_velocity(100);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake.move_velocity(-100);
		}
		else {
			intake.brake();
		}

		//Lift movement
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
			status_lift = !status_lift;
		}
		lift.set_value(status_lift);

		//Wings movement
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) && status_weak_wings == false){
			status_wings = !status_wings;
		}
		wings.set_value(status_wings);

		//Weak wings movement
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && status_wings == false){
			status_weak_wings = !status_weak_wings;
		}
		weakWings.set_value(status_weak_wings);

		//
		//} else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		//	lift.set_value(LOW);

		

		//if (eyes.get_hue() == )


		pros::delay(10);
	}
}
