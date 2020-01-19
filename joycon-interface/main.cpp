/*

Joycon Command-Line Interface

This program will communicate via named pipes with the joycon server.

It parses your inputs and passes them to the server, returns data and displays it
in a meaningful way.

You can use this to do all kinds of stuff.

*/

#include "src/parse.h"
#include "src/pipe.h"

int main(int argc, char *argv[]) {

  /* All we do here is identify the subcommand with its arguments,
     and execute the specified callback for the subcommand. */

  Option option(argc, argv);
  return option.execute();
}
