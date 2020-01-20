# joycon++ API

C++ API for streaming joycon inputs into an event queue / data structure and sending commands to joycons.

## Structure

### Joycon Manager

The API (find in `joycon-core`) can be included by including `joycon-core.cpp`.

This allows you to create a JoyconManager object and initialize it.

This provides the interface to communicating with the joycons. It lets you bind and release them, as well as list all available joycons on bluetooth (as well as all managed joycons).

Binding occurs by passing the bluetooth-connected joycon MAC adress as a string (small letters) to the bind function. Same for release.

**Important:** Your joycons must already be connected to your computer via bluetooth. If you are unsure, you can install a bluetooth manager like `blueman` and make sure that the device is connected / paired (not strictly necessary) as an "HID" device. If you are unsure, then the joycon manager will tell you if they are available using the list function.

### Joycon Object

Inidividual joycon objects (`joycon-core/include/joycon.h`) store all the important joycon information. Once a joycon is bound by the manager, it opens a thread and streams the input data. It is then parsed and stored inside a machine / human readable form.

The joycon will additionally keep track of an event queue (with a definable maximum size) that you can get individual events out of and then use to execute arbitrary code upon joycon button inputs.

Since the streaming is on a separate thread, you can simply have your event loop as a while loop.

Or you can do something fancier if you like.

To see what kind of event types will be triggered by the joycon inputs, see `joycon-core/include/events.h`.

Joycon objects have a few helper members that you can use to set their properties, such as player lights or sending rumbles

### Other Stuff

Everything else are helper classes that you can feel free to peruse. These are useful for sending vibrations, settings home light blinking patterns, or the player light.
