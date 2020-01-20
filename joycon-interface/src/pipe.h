/*
Author: Nicholas McDonald


Named Pipe Class.

This allows for communicating between different programs via named pipes.
It's super simple and very useful.

*/

#include <string>
#include <iostream>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/poll.h>

class Pipe{
public:
  //Pipe File Location
  std::string location;
  int fifo;
  char buf[100];
  bool isOpen = false;

  Pipe(std::string _location);

  bool peek();
  bool create(std::string _location);
  bool openPipe(std::string _location);
  void closePipe();
  void readPipe();
  void writePipe(std::string message);
};

Pipe::Pipe(std::string _location){
  //Simply open the pipe at the location.
  openPipe(_location);
}

//Simple check to see if the pipe can be read from!
bool Pipe::peek(){
  struct pollfd fds;
  fds.fd = fifo;
  fds.events = POLLIN;
  if(isOpen && poll(&fds, 1, 0)) return true;
  return false;
}

bool Pipe::create(std::string _location){
  //Check if pipe exists.
  struct stat fifopipe;
  stat (_location.c_str(), &fifopipe);

  // If both the pipes already exist there is nothing to do
  if (S_ISFIFO(fifopipe.st_mode)) return true;

  //Pipe does not exist yet...

	/* Create the server pipe */
	fifo = mkfifo(_location.c_str(), 0666);
	if ( fifo >= 0 ) return true; //Success!!

  //Failed to create the pipe...
  std::cout << "Unable to create a fifo server file." << std::endl;
  return false;
}

bool Pipe::openPipe(std::string _location){

  //Make sure pipe exists first (and if not, create it)!
  if(!create(_location)){
    std::cout<<"Failed to create FIFO pipe. Check permissions."<<std::endl;
    return false;
  }

  //Check if the pipe file exists and create it if it doesn't!!
  location = _location;

  //Open the pipe at the correct location...
  fifo = open(_location.c_str(),O_RDWR);
  if ( fifo < 1 ) {
  	std::cout << "Error opening pipe. Aborting." << std::endl;
   	return false;
  }

  //Success!
  isOpen = true;
  return true;
}

void Pipe::closePipe(){
  if(!isOpen) return;
  close(fifo);
}

void Pipe::writePipe(std::string message){
  if(!isOpen) return;
  write(fifo, message.c_str(), sizeof(message.c_str()));
}

void Pipe::readPipe(){
  if(!isOpen) return;
  read(fifo, buf, 100*sizeof(char));
}
