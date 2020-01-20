/*
ToDo:
  Simple Interface for IR Camera Information
  Write to SPI Flash for settings device colors

  Joycon Pairing
    -> Give each joycon a pointer to its paired joycon
    -> Pairing joycons lets you map their inputs different?
    -> There is really no benefit I think

  Give Joycons an ID for the Manager, for easier manipulation.

  Store the Joycon Color

  Query command for managed joycon objects
    --list, etc.

  Commands to bind and unbind joycon objects

  Command to output the joycon data!
    --data <color / battery>

  Command to set the player number status
    Maybe it by default sets them all to whatever index they are?
    Pairing sets their lights accordingly

  Finally, you have access to the direct button states by setting up the API

  Joycons need a proper event managing system.
  Joycons store their absolute state but also just events.

  The server will load binding config files to specific joycons
  it will iterate over all joycons and poll for joycon events

  It will then execute the code that is loaded for each joycon event!

  Certain event handlers can be pre-programmed!

  
*/
