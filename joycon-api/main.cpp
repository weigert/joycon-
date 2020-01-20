/*
Author: Nicholas McDonald

Joycon C++ API Example Program!

Joycon Core allows for communicating with the Joycons

*/

//Include the Header File
#include "src/JoyconManager.cpp"
#include <unistd.h>

int main(int argc, char *argv[]) {

  //Create a Joycon Manager Object!
  JoyconManager manager;

  //Initialize the Joycon API!
  if(!manager.setup()){
    std::cout<<"Failed to Launch the Joycon-Manager!"<<std::endl;
    return 0;
  }

  std::cout<<"Executing Joycon Test!"<<std::endl;

  /* List all Available Joycon Devices! */
  manager.list();
  manager.bind("58:2f:40:6b:1a:43");
  //manager.bind("58:2f:40:6b:52:5e");
  usleep(1E+8);
  //manager.release("58:2f:40:6b:52:5e");
  manager.release("58:2f:40:6b:1a:43");

  /*

  Connect to the Joycon Devices!

  Start streaming their information!

  Define callbacks for input events!

  Use their data directly!

  */

  /*
  JoyconVec joycons;
  if (joycons.addDevices()   == -1) { hid_exit();  return 0; }
  if (joycons.startDevices() == -1) { hid_exit();  return 0; };

  //Send a rumble!
  std::cout<<"Sending Rumble"<<std::endl;
  Rumble rumble(200, 0.5);
  joycons.vec[0]->send_rumble(rumble);

  while (!shutdown_flag) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
*/

  //Shutdown the Joycon API!
  manager.cleanup();
  return 0;
}
