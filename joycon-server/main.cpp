/*

Joycon C++ API Example Program!

Joycon Core

*/
#include "src/pipe.h"

int main(int argc, char *argv[]) {

  Pipe pipe;
  pipe.openPipe("/home/nick/test_pipe");

  while(true){
    pipe.readPipe();
  }

  /*
  Launch a main loop and wait for commands.

  If joycons exist, then stream their information.

  This program will be the most complex.

  But we need to wait for inputs on the named pipe.

  Then we can respond to inputs on the named pipe.

  This also needs to load profiles from files and bind them via callbacks.
  */

  return 0;
}
