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

void tuningCLI() {
  auto& pid = Robot::chassis->lateralPID;
  auto& settings = Robot::chassis->lateralSettings;
  while (1) {
    try {
      std::cout << "pid tuner> ";
      std::string input;
      getline(std::cin, input);
      makeLowerCase(input);
      auto params = split(input, " ");
      std::string command = params.at(0);

      if (command == "s" || command == "set") {
        if (params.size() < 3) {
          std::cout << "invalid number of arguments" << std::endl;
          continue;
        }
        std::string gainType = params.at(1);
        std::string gainValueStr = params.at(2);
        float gainValue = std::stof(gainValueStr);

        if (gainType.find("p") != std::string::npos) {
          pid.kP = gainValue;
        } else if (gainType.find("d") != std::string::npos) {
          pid.kD = gainValue;
        } else if (gainType.find("i") != std::string::npos) {
          pid.kI = gainValue;
        } else if (gainType.find("s") != std::string::npos) {
          settings.slew = gainValue;
        } else {
          std::cout << "invalid gain type" << std::endl;
        }
      } else if (command == "g" || command == "get") {
        if (params.size() < 2) {
          std::cout << "invalid number of arguments" << std::endl;
          continue;
        }
        std::string gainType = params.at(1);
        if (gainType.find("p") != std::string::npos) {
          std::cout << "kP: " << pid.kP << std::endl;
        } else if (gainType.find("d") != std::string::npos) {
          std::cout << "kD: " << pid.kD << std::endl;
        } else if (gainType.find("i") != std::string::npos) {
          std::cout << "kI: " << pid.kI << std::endl;
        } else if (gainType.find("s") != std::string::npos) {
          std::cout << "slew: " << settings.slew << std::endl;
        } else {
          std::cout << "invalid gain type" << std::endl;
        }
      } else if (command == "run" || command == "x" || command == "rr") {
        Robot::chassis->cancelMotion();
        Robot::chassis->setPose(0, 0, 0);
        float x = 0;
        float y = (command == "rr" ? -1 : 1) * 24;
        float timeout = 2000;
        bool wait = true;
        if (params.size() > 1) {
          auto noWaitIt = find(params.begin(), params.end(), "-n");
          if (noWaitIt != params.end()) {
            timeout = 1000000;
            wait = false;
          }

          auto timeoutIt = find(params.begin(), params.end(), "-t");
          if (timeoutIt != params.end() && ++timeoutIt != params.end()) {
            timeout = std::stof(*timeoutIt);
          }
        }
        Robot::chassis->moveToPoint(x, y, timeout, {.forwards = y > 0});
        if (wait) {
          Robot::chassis->waitUntilDone();
          print();
        }
      } else if (command == "print" || command == "p") {
        print();
      } else if (command == "stop" || command == "s") {
        Robot::chassis->cancelMotion();
      } else if (command == "exit") {
        break;
      } else {
        std::cout << "invalid command" << std::endl;
      }
    } catch (std::exception e) {
      std::cout << "error: " << e.what() << std::endl;
    }

    pros::delay(10);
  }
}
void opcontrol() {
	bool status_lift = false;
	bool status_wings = false;
	//bool status_weak_wings = false;
	bool mid_wings = false;

	while (true) {
		
		//Chassis movement
		
		//chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
		
		//Cata movement
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
			cata.move_velocity(100);
		}
		else {
			cata.brake();
		}

		// Intake movement
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			intake.move_velocity(600);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake.move_velocity(-600);
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
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) ){
			status_wings = !status_wings;
		}
		wings.set_value(status_wings);

		//Weak wings movement
		/*if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) && status_wings == false){
			status_weak_wings = !status_weak_wings;
		}
		weakWings.set_value(status_weak_wings);*/

		//Mid wings movement
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			mid_wings = !mid_wings;
		}
		midWing.set_value(mid_wings);

		//
		//} else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		//	lift.set_value(LOW);

		//pros::lcd::print(0,"Hue value: %lf", eyes.get_hue());
		//lift.set_value(false);
		

		//if (eyes.get_hue() == )


		pros::delay(10);
	}
}
