
/*
  Author: Nicholas McDonald


  Options Parse and Executor!


*/

#include <vector>
#include <string>
#include <iostream>
#include "pipe.h"


/* All possible Option Flags!! */
enum OptionFlag{
  //These are dummies (but they work)!
  NONE,
  UNKNOWN,
  HELP,

  //Manage Bluetooth Connections
  FIND,
  CONNECT,
  DISCONNECT,

  //These all work!
  CLOSE,
  PING,

  //Manage Connected Joycons
  LIST,
  BIND,
  UNBIND,

  //
  RUMBLE,
  BLINK
};

/* Define the Option Callbacks (templated by their subcomand enum)! */
template<OptionFlag F>
bool optionCallback(std::vector<std::string> params){
  std::cout<<"Something has gone horribly wrong..."<<std::endl;
  return true;
};

template<>
bool optionCallback<NONE>(std::vector<std::string> params){
  std::cout<<"Please specify an option: joycon [flags]"<<std::endl;
  return true;
};

template<>
bool optionCallback<UNKNOWN>(std::vector<std::string> params){
  std::cout<<"Option is unknown. Please use the option --help for more information."<<std::endl;
  return false;
};

template<>
bool optionCallback<HELP>(std::vector<std::string> params){
  std::cout<<std::endl<<"Joycon++ Commandline Interface Help"<<std::endl;
  std::cout<<"Usage: joycon --subcommand [required] <optional>"<<std::endl;
  std::cout<<std::endl;
  std::cout<<"Server Communication"<<std::endl;
  std::cout<<"  --ping: Check if joycon-server is online."<<std::endl;
  std::cout<<"  --close: Shutdown the joycon-server safely."<<std::endl;
  std::cout<<std::endl;
  std::cout<<"Bluetooth Management"<<std::endl;
  std::cout<<"  --find: Find available bluetooth joycons"<<std::endl;
  std::cout<<"  --connect <ID>: Establish joycon bluetooth connection. If no ID specified, connects to all."<<std::endl;
  std::cout<<"  --disconnect <ID>: Remove joycon bluetooth connection. If no ID specified, disconnects from all."<<std::endl<<std::endl;
  return true;
};

template<>
bool optionCallback<BLINK>(std::vector<std::string> params){
  /* Do a Blink! */
  std::cout<<"Called the Blink Option!"<<std::endl;
  return true;
}

template<>
bool optionCallback<RUMBLE>(std::vector<std::string> params){
  /* Do a Blink! */
  std::cout<<"Called the RUMBLE option!"<<std::endl;
  return true;
}

template<>
bool optionCallback<FIND>(std::vector<std::string> params){
  /* Find any available Bluetooth Devices that are Joycons */
  return bluetooth::findJoycons();
}

template<>
bool optionCallback<CONNECT>(std::vector<std::string> params){
  /* Connect to Bluetooth Devices that are Joycons */
  return bluetooth::connect(params[0]);
}

template<>
bool optionCallback<DISCONNECT>(std::vector<std::string> params){
  /* Disconnect from Bluetooth Devices that are Joycons */
  return bluetooth::disconnect(params[0]);
}

template<>
bool optionCallback<CLOSE>(std::vector<std::string> params){
  /* Send a --close command to the pipe! */
  Pipe pipe("/home/nick/tos_pipe");
  pipe.writePipe("--close");
  return true;
}

template<>
bool optionCallback<PING>(std::vector<std::string> params){
  //Open the Pipe to Write Ping!
  Pipe pipe("/home/nick/tos_pipe");
  pipe.writePipe("--ping");

  //Open the Reading Pipe!
  pipe.closePipe();
  pipe.openPipe("/home/nick/toc_pipe");

  int tries = 15;
  while(tries > 0){
    //Check for a peek!
    if(pipe.peek()){
      pipe.readPipe();
      std::cout<<pipe.buf<<std::endl;
      return true;
    }

    //Wait and try again!
    usleep(10000);
    tries--;
  }

  //Dind't get what we wanted...
  std::cout<<"...timed out..."<<std::endl;
  return false;
}

/* An Option Struct */
struct Option{
  //Properties of the Subcommand Option
  OptionFlag ID;
  std::vector<std::string> params;

  //Constructor...
  Option(int argc, char* args[]);
  bool execute();
};

//Constructor Code (i.e. the parser)
Option::Option(int argc, char* args[]){
  //Check for existing arguments
  if(argc < 2){
    ID = NONE;
    return;
  }

  //Get the string from the first char...
  std::string s(args[1]);

  //Otherwise, we check what the option is!
  if(s == "--blink") ID = BLINK;
  else if(s == "--rumble") ID = RUMBLE;
  else if(s == "--find") ID = FIND;
  else if(s == "--close") ID = CLOSE;
  else if(s == "--ping") ID = PING;
  else if(s == "--help") ID = HELP;
  else if(s == "--list") ID = LIST;
  else if(s == "--connect"){
    ID = CONNECT;
    //Check if we have an argument here!
    if(argc == 3){
      std::string p(args[2]);
      params.push_back(p);
    }
    else{
      params.push_back("");
    }
  }
  else if(s == "--disconnect"){
    ID = DISCONNECT;
    //Check if we have an argument here!
    if(argc == 3){
      std::string p(args[2]);
      params.push_back(p);
    }
    else{
      params.push_back("");
    }
  }
  else ID = UNKNOWN;
};

bool Option::execute(){
  //Execute the Templated Callback Function!
  switch(ID){
    case NONE:
      return optionCallback<NONE>(params);
    case BLINK:
      return optionCallback<BLINK>(params);
    case HELP:
      return optionCallback<HELP>(params);
    case RUMBLE:
      return optionCallback<RUMBLE>(params);
    case FIND:
      return optionCallback<FIND>(params);
    case CONNECT:
      return optionCallback<CONNECT>(params);
    case CLOSE:
      return optionCallback<CLOSE>(params);
    case PING:
      return optionCallback<PING>(params);
    case DISCONNECT:
      return optionCallback<DISCONNECT>(params);
    case LIST:
      return optionCallback<LIST>(params);
    default:
      return optionCallback<UNKNOWN>(params);
  }
};
