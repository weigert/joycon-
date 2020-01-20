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
#include <cmath>
#include <vector>
#include <array>
#include <type_traits>
#include <hidapi/hidapi.h>

#define JOYCON_VENDOR 0x057e

#include "include/event.h"
#include "include/types.h"
#include "include/rumble.cpp"
#include "include/buffer.cpp"
#include "include/homelight.cpp"
#include "include/joycon.cpp"

/*
Author: Nicholas McDonald

  Joycon API Master Class!

*/

class JoyconManager{
  public:
    //Initialize and Shutdown
    bool setup();
    void cleanup();

    //List Managed Joycons and Available Bluetooth Devices
    void list();

    //Bind and Release Joycons from Management
    bool bind(std::string serial_number);
    bool release(std::string serial_number);

    //Vector of Joycon Objects!
    std::vector<Joycon*> joycons;
};
