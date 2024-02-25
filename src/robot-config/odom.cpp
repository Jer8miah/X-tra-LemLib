#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "robot.h"
#include "pros/error.h"

lemlib::OdomSensors* Robot::odomSensors = nullptr;
lemlib::Chassis* Robot::chassis = nullptr;

void Robot::initializeOdometry(){
    lemlib::Drivetrain drivetrain {
        &Robot::Motors::leftSide,       &Robot::Motors::rightSide,
        Robot::Dimensions::trackWidth,  Robot::Dimensions::driveWheelDiameter,
        Robot::Dimensions::driveWheelRpm, Robot::Tuneables::chasePower};

        lemlib::TrackingWheel* leftVert =
            Robot::Sensors::vertTracker.get_angle() != PROS_ERR
                ? new lemlib::TrackingWheel(&Robot::Sensors::vertTracker,
                                            Robot::Dimensions::vertEncDiameter,
                                            Robot::Dimensions::vertEncDistance,
                                            Robot::Dimensions::vertEncGearRatio)
                : nullptr;

        lemlib::TrackingWheel* rightVert = nullptr;
        lemlib::TrackingWheel* horiz = nullptr;


        Robot::odomSensors = 
            new lemlib::OdomSensors {leftVert, rightVert /* nullptr */, horiz /* nullptr*/, nullptr, &Robot::Sensors::imu};
       
       Robot::chassis = 
        new lemlib::Chassis {drivetrain, Robot::Tuneables::lateralController, Robot::Tuneables::angularController, *odomSensors};
};