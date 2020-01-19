#include <chrono>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <mutex>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <signal.h>
#include <cmath>
#include <vector>
#include <array>
#include <type_traits>

#include <hidapi/hidapi.h>

#include "include/types.h"
#include "include/rumble.cpp"
#include "include/buffer.cpp"
#include "include/homelight.cpp"
#include "include/joycon.cpp"

static sig_atomic_t volatile shutdown_flag = 0;
static void SigCallback(int sig) {
	shutdown_flag = 1;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	// Initialize the hidapi library
	if (hid_init()) {
		std::cerr << "HID initialization failed!" << std::endl;
		return -1;
	}

	signal(SIGINT , SigCallback);
	signal(SIGTERM, SigCallback);

	JoyconVec joycons;
	if (joycons.addDevices()   == -1) { hid_exit();  return 0; }
	if (joycons.startDevices() == -1) { hid_exit();  return 0; };

	//Send a rumble!
	std::cout<<"Sending Rumble"<<std::endl;
	Rumble rumble(200, 0.5);
  joycons.vec[0]->send_rumble(rumble);


	while (!shutdown_flag) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		//Send a rumble???
	}

	hid_exit();
	return 0;
}
