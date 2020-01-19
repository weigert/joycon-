/*

Named Pipe Class.

This allows for communicating between different programs.

*/
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>

class Pipe{
public:
  //Pipe File Location
  std::string location;
  int fifo;
  char buf[100];
  bool isOpen = false;

  //
  bool create(std::string _location);
  bool openPipe(std::string _location);
  void closePipe();
  void readPipe();
  void writePipe(std::string message);
};

bool Pipe::create(std::string _location){
  //Check if pipe exists.
  struct stat fifopipe;
  stat (_location.c_str(), &fifopipe);

  // If both the pipes already exist there is nothing to do
  if (S_ISFIFO(fifopipe.st_mode)) {
  	std::cout << "Pipe exists already. Exiting." << std::endl;
   	return true;
  }
  std::cout << "Pipe doesn't exist. Creating pipe." << std::endl;

	/* Create the server pipe */
	fifo = mkfifo(_location.c_str(), 0666);

	if ( fifo < 0 ) {
		std::cout << "Unable to create a fifo server file." << std::endl;
		std::cout << fifo << std::endl;
		return false;
	}

  std::cout << "FIFO pipe "<<_location.c_str()<<" created successfully." << std::endl;
  return true;
}

bool Pipe::openPipe(std::string _location){

  //Make sure pipe exists first!
  if(!create(_location)){
    std::cout<<"Failed to create FIFO pipe. Check permissions."<<std::endl;
    return false;
  }

  //Check if the pipe file exists and create it if it doesn't!!
  std::cout<<"Opening FIFO pipe on "<<_location<<std::endl;
  location = _location;

  //Open the pipe at the correct location...
  fifo = open(_location.c_str(),O_RDWR);
  if ( fifo < 1 ) {
  	std::cout << "Error opening pipe. Aborting." << std::endl;
   	return false;
  }

  std::cout << "Pipe opened successfully." << std::endl;
  isOpen = true;
  return true;
}

void Pipe::closePipe(){

  if(!isOpen){
    std::cout<<"Pipe is not open. Aborting."<<std::endl;
    return;
  }

  std::cout<<"Closing FIFO pipe."<<std::endl;
  close(fifo);
}

void Pipe::writePipe(std::string message){

  if(!isOpen){
    std::cout<<"Pipe is not open. Aborting."<<std::endl;
    return;
  }

  //Write to the pipe!
  write(fifo, message.c_str(), sizeof(message.c_str()));
}

void Pipe::readPipe(){

  if(!isOpen){
    std::cout<<"Pipe is not open. Aborting."<<std::endl;
    return;
  }

  read(fifo, buf, 100*sizeof(char));
  std::cout << buf << " received from the client." << std::endl;
}
