#include "main.h"
#include "pros/misc.h"
#include "robot.h"
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
const bool tuneModeEnabled = true;

void opcontrol() {
	bool status_lift = false;
	bool status_wings = false;
	bool status_back_wings = false;
	//bool mid_wings = false;

	while (true) {
		
		//Chassis movement
		
		//chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		Robot::chassis->tank(
      Robot::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 
      Robot::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    
		/*
		//Cata movement
		if (Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			Robot::Motors::cata.move_velocity(100);
		}
		else {
			cata.brake();
		}
    */

		// Intake movement
		if (Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			Robot::Motors::intake.move_velocity(600);
		} else if (Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			Robot::Motors::intake.move_velocity(-600);
		}
		else {
			Robot::Motors::intake.brake();
		}

		//Lift movement
		if (Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			Robot::Motors::lift.move_velocity(100);
		} else if (Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			Robot::Motors::lift.move_velocity(-100);
		}
		else {
			Robot::Motors::lift.brake();
		}

		//Wings movement
		if(Robot::master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) ){
			status_wings = !status_wings;
		}
		Robot::Pistons::wings.set_value(status_wings);

		//Weak wings movement
		if(Robot::master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && status_wings == false){
			status_back_wings = !status_back_wings;
		}
		Robot::Pistons::backWings.set_value(status_back_wings);

    /*
		//Mid wings movement
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			mid_wings = !mid_wings;
		}
		midWing.set_value(mid_wings);
    */
		//
		//} else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		//	lift.set_value(LOW);

		//pros::lcd::print(0,"Hue value: %lf", eyes.get_hue());
		//lift.set_value(false);
		

		//if (eyes.get_hue() == )

    if (tuneModeEnabled &&
        Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) &&
        Robot::master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) 
      tuningCLI();


		pros::delay(10);
	}
}
