/*
Author: Nicholas McDonald

Joycon C++ API Example Program!
*/

//Include the Header File
#include "../../joycon-core/joycon-core.cpp"
#include "movemouse.h"

int main(int argc, char *argv[]) {

  //Create a Joycon Manager Object and Initialize
  JoyconManager manager;
  if(!manager.setup()){
    std::cout<<"Failed to Launch the Joycon-Manager!"<<std::endl;
    return 0;
  }

  /* List all Available Bluetooth Connected Joycons (and managed)! */
  manager.list();

  /* Bind a Specific Joycon! */
  if(!manager.bind("58:2f:40:6b:1a:43")) return false;  //Change this to whatever your joycon MAC is

  /* ^^^ It is worth it to look what those two functions do! */

  /* Example Event Loop ! */
  bool run = true;
  while(run){

    /* Iterate over all Connected Joycons */
    for(auto& joycon: manager.joycons){

      //Get the Event from the Joycon
      event* e = joycon->getEvent();
      if(e == nullptr) continue;

      //Execute Code based on Joycon Inputs

      //Quit the Event Loop by Pressing Home / Screenshot
      if(e->input == BUTTON_SPECIAL) run = false;

      //Move the Mouse with the Joystick
      if(e->input == JOYSTICK){
        int speed = 25.0;
        pos shift(speed * joycon->input.xJoy, - speed * joycon -> input.yJoy);
        moveMousePosX(shift);
      }

      //Z-Trigger Down / Up Correspond to Left-Click Down / Up!
      if(e->input == TRIGGER_Z && e->type == BUTTON_DOWN) mouseClickX(LEFT, true);
      else if(e->input == TRIGGER_Z && e->type == BUTTON_UP) mouseClickX(LEFT, false);
    }
  }

  /* Release the Joycon (Not Strictly Necessary, good practice) */
  manager.release("58:2f:40:6b:1a:43");

  //Shutdown the Joycon API!
  manager.cleanup();
  return 0;
}
