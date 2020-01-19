/*
  Map Bluetooth Communication so you can store the buttons and positions
  Can we also somehow store the IR camera information?

  You then need a proper device driver style interface.

  This means you launch the code that can handle the inputs...

  You should be able to hook up to the joycon normally using bluetooth.

  Then you should be able to pair two joycons using a command too.

  Each joycon has a MAC number and an ID (0, 1, 2, etc.)

  you can pair two joycons

  Disconnect a joycon by its ID

  Maybe do this with named pipes?

  You write the button state to files...

  Or you send a command to get the button state.

  If we store all the devices inside some folder structure then we can display them e.g. using polybar

  having an icon depending on the color, disconnect, etc.

  Finally:

  You need to have a good interface to do a number of things:

  -> Execute arbitrary code by hooking into the device driver.

  i.e. have some program managing the joycon connections and Communication...



1. Connect the Device via bluetooth
At this point, if the device could automatically find it's driver, or the driver automatically detects it and starts
streaming the data, that would make sense. Then it interprets it and writes it to appropriate files

Other programs can then stream the data to utilize it.

Alternatively, you build an API system.

but you really need to have a server running the joycons off first.

Then you can build a small program that reads the data directly from the files,
for instance for polybar.
And that way you can have a disconnect button,
a pairing function which remaps the inputs to some new structure


How about:
You launch a joycon manager server...
This keeps track of joycon objects.

You can query it with a number of commands...

List all (checks your bluetooth connections for the devices)
Get the batter status
Set the home button status

Pair joycons together, which changes their button mapping accordingly
And additionally sets their lights

Reads their current button states.

How does this become an API tho?

You should have a library that is a header.
This header allows you to do a number of calls.

You can setup a joycon and connect to the bluetooth socket once connected.
Then by a number of calls you can get the current button data.

To do this, we need to be streaming the data into some data structure.

Uses libhid so that you can stream the data appropriately..
stores it in some kind of joycon object.

*/
