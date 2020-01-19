/*

Options parsing helper.

This will identify a series of options...

Then it will have a defined callback function once it has identified the correct command.

Different Joycon States:

  -> Not Connected (not connected via bluetooth)
  -> Connected Via Bluetooth
  -> Bound to the joycon server! (i.e. we are tracking their data)

Options:

  Bluetooth Options:
    --find (find joycons via bluetooth)
    --connect [ID] (connect a joycon that isn't bluetooth bound yet)
    --disconnect [ID] (disconnect a joycon that is bluetooth bound)

    --list (list all joycons that are connected or bound
    --info (list a specific joycons data, color, ID, L / R, etc.)

  Those steps can be skipped directly through the bluetooth thing

  --bind (bind a joycon that is connected)
  --unbind (unbind a joycon to the joycon manager)

  --pair (pair two joycons manually)
  --unpair (unpair a joycon and its partner)
  --autopair (will wait for you to press the shoulder buttons)

  --player (set the player number for a joycon or joycon pair)
  --profile (bind the joycons button inputs to a specific profile from a config file)

  Cosmetic Stuff:
  --rumble (send a rumble to a specific joycon to test it)
  --blink (send a quick homebutton blink to the joycon)

  Settings:
  --setcolor (set the joycons color)
*/

/*
  Parse the Inputs for Valid Inputs

  Open the pipe and send the data to the server...

  Wait for the servers response

  Display the information
*/

/*
Pipe pipe;
pipe.openPipe("/home/nick/test_pipe");

if(argc < 2) return 0;
pipe.writePipe(argv[1]);
*/

/*
Open the Named Pipe!

1. Parse the Inputs, make sure they are valid!!
2. Communicate the Inputs to the Named Pipe
3. Get the Response from the Server
4. Display the Information
*/

#include <vector>
#include <string>
#include <iostream>


/* All possible Option Flags!! */
enum OptionFlag{
  NONE,
  UNKNOWN,
  FIND,
  CONNECT,
  DISCONNECT,

  RUMBLE,
  BLINK
};

/* Define the Option Callbacks (templated by their subcomand enum)! */
template<OptionFlag F>
bool optionCallback(std::vector<std::string> params){
  std::cout<<"Specified OptionFlag does not exist."<<std::endl;
  return true;
};

template<>
bool optionCallback<NONE>(std::vector<std::string> params){
  std::cout<<"Please specify an option."<<std::endl;
  return true;
};

template<>
bool optionCallback<UNKNOWN>(std::vector<std::string> params){
  std::cout<<"Please specify an option."<<std::endl;
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
  /* List all the bluetooth devices we can find! */
  bluetooth::findJoycons();
  return true;
}

template<>
bool optionCallback<CONNECT>(std::vector<std::string> params){
  /* List all the bluetooth devices we can find! */
  return bluetooth::connect(params[0]);
}

template<>
bool optionCallback<DISCONNECT>(std::vector<std::string> params){
  /* List all the bluetooth devices we can find! */
  return bluetooth::disconnect(params[0]);
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
  }

  //Get the string from the first char...
  std::string s(args[1]);

  //Otherwise, we check what the option is!
  if(s == "--blink") ID = BLINK;
  else if(s == "--rumble") ID = RUMBLE;
  else if(s == "--find") ID = FIND;
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
    case BLINK:
      return optionCallback<BLINK>(params);
    case RUMBLE:
      return optionCallback<RUMBLE>(params);
    case FIND:
      return optionCallback<FIND>(params);
    case CONNECT:
      return optionCallback<CONNECT>(params);
    case DISCONNECT:
      return optionCallback<DISCONNECT>(params);
    default:
      return false;
  }
};
