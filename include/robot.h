#pragma once
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

class Robot {
    public:
        class Motors{
            public:
                static pros::Motor_Group leftSide;
                static pros::Motor_Group rightSide;

                static pros::Motor intake;
        };

        class Sensors{
            public:
                static pros::Imu imu;
                static pros::Rotation vertTracker;
        };

        class Pistons{
            public:
                static pros::ADIDigitalOut wings;
                static pros::ADIDigitalOut backWings;
        };

        class Dimensions{
            public:
                static const float trackWidth;
                static const float driveWheelDiameter;
                static const float driveWheelRpm;
                static const float driveEncRatio;

                static const float vertEncDiameter;
                static const float vertEncDistance;
                static const float vertEncGearRatio;
        };

        class Tuneables{
            public:
                static lemlib::ControllerSettings lateralController;
                static lemlib::ControllerSettings angularController;
                static const float chasePower;

        };

        static void initializeOdometry();
        static lemlib::OdomSensors* odomSensors;
        static pros::Controller master;
        static lemlib::Chassis* chassis;

    
};