#include <iostream>
#include <fstream>
#include <ctime>

#include "GLFW_window_set.h"
#include "Log.h"

std::stringstream* Logger::lg = nullptr;

int main(int argc, char **argv) {

	window_setup();
}
// Can get the full code from https://github.com/V-KMilev/Ray-tracer.git