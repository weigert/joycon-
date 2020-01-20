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

#define JOYCON_VENDOR 0x057e


#include "include/types.h"
#include "include/rumble.cpp"
#include "include/buffer.cpp"
#include "include/homelight.cpp"
#include "include/joycon.cpp"

/*
Author: Nicholas McDonald

  Joycon API Master Class!

*/

static sig_atomic_t volatile shutdown_flag = 0;
static void SigCallback(int sig) {
	shutdown_flag = 1;
}

class JoyconManager{
  public:
    //Initialize and Shutdown
    bool setup();
    void cleanup();

    //Other Members!
    void list();

    //Bind and Release Joycons
    bool bind(std::string serial_number);
    bool release(std::string serial_number);

    //Joycon Management...
    void activate(Joycon *joycon);
    void deactivate(Joycon *joycon);

    //Vector of Joycon Objects!
    std::vector<Joycon*> joycons;
};
