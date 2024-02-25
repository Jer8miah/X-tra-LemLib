#include "robot.h"
#include "main.h"
#include <string>
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

std::vector<std::string> split(const std::string& _input,
                               const std::string& delimiter) {
  std::vector<std::string> tokens;
  std::string source = _input;
  size_t pos = 0;
  while ((pos = source.find(delimiter)) != std::string::npos) {
    tokens.push_back(source.substr(0, pos));
    source.erase(0, pos + delimiter.length());
  }
  tokens.push_back(source);
  return tokens;
}

void makeLowerCase(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  ;
}

void print() { printf("y: %fdeg\n", Robot::chassis->getPose().y); }

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

