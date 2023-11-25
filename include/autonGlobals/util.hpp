#pragma once

#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "api.h"

void print_to_screen(std::string text, int line = 0);

namespace as{
extern AutonSelector auton_selector;

void page_up();

void page_down();

void initialize();  
}
