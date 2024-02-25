#include "robot.h"

bool backWingState = false;
bool frontWingState = false;

void setWings(bool state) {
    frontWingState = state;
    Robot::Pistons::wings.set_value(state);
}

void setBackWings(bool state) {
    backWingState = state;
    Robot::Pistons::backWings.set_value(state);
}

void Robot::Actions::expandWings() {
    setWings(true);
}

void Robot::Actions::retractWings() {
    setWings(false);
}

void Robot::Actions::expandBackWings() {
    setBackWings(true);
}

void Robot::Actions::retractBackWings() {
    setBackWings(false);
}