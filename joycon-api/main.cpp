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

  //Set the Home Light?
  usleep(1E+7);
  //HOME_LIGHT light;
  //light.set_header(0xff, 0xff, 0xff, 0xff);
  //manager.joycons[0]->set_home_light(light);
  manager.joycons[0]->set_player_lights(P0_FLASH | P1_FLASH | P2_FLASH | P3_FLASH);

  //manager.bind("58:2f:40:6b:52:5e");
  //manager.release("58:2f:40:6b:52:5e");
  manager.release("58:2f:40:6b:1a:43");

  /* Now I need to define callbacks! */

  //Shutdown the Joycon API!
  manager.cleanup();
  return 0;
}
