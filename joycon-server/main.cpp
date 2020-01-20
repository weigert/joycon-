/*

Joycon Server for Running an Instance of the Joycon C++ API,
with callbacks for certain features and wrapping everything in a user friendly console program.

*/

bool JOY_API_INIT(){
  return true;
}

void JOY_API_SHUTDOWN(){
}


#include <string>
#include <thread>
#include "src/pipe.h"

int main(int argc, char *argv[]) {

  /* Construct a Joycon Manager Object */
  if(!JOY_API_INIT()){
    std::cout<<"Joycon API Initialization Failed. Exiting."<<std::endl;
    return 0;
  }

  //Communication Pathway
  Pipe in_pipe("/home/nick/tos_pipe");
  Pipe out_pipe("/home/nick/toc_pipe");

  /* Main Server Loop */
  bool shutdown = false;
  while(!shutdown){

    /* Check for Command Inputs */
    if(in_pipe.peek()){

      //Get Pipe Data!
      in_pipe.readPipe();
      std::string s(in_pipe.buf);

      //Do something with Pipe Data...
      if(s == "--close") shutdown = true;
      if(s == "--ping") out_pipe.writePipe("PING");
    }

    //Sleep a bit...
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  //Close the Service!
  JOY_API_SHUTDOWN();
  return 0;
}
