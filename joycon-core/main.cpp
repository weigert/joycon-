/*
Author: Nicholas McDonald

Joycon C++ API Example Program!

Joycon Core allows for communicating with the Joycons

*/

//Include the Header File
#include "src/joycon-core.cpp"

int main(int argc, char *argv[]) {

  //Create a Joycon Manager Object!
  JoyconManager manager;

  //Initialize the Joycon API!
  if(!manager.setup()){
    std::cout<<"Failed to Launch the Joycon-Manager!"<<std::endl;
    return 0;
  }

  manager.bind("58:2f:40:6b:1a:43");


  bool test = true;
  while(test){
    //Test for Button up a!
    event* e = manager.joycons[0]->getEvent();
    if(e != nullptr){
      if(e->type == BUTTON_UP && e->input == BUTTON_SPECIAL ){
          test = false;
          std::cout<<"Hit Button SPECIAL!"<<std::endl;
      }
      else if(e->type == BUTTON_UP && e->input == BUTTON_X ){
          std::cout<<"Hit Button X!"<<std::endl;
      }
    }
  }

  manager.release("58:2f:40:6b:1a:43");


  //Shutdown the Joycon API!
  manager.cleanup();
  return 0;
}
