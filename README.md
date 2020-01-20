# joycon++ - Joycon C++ API
Joycon API / Driver for C++ on Unix. Example program with Joycon Mouse.

There were already a few for windows, and no complete ones in C++, so I made this.

## Usage

Simply copy the `joycon-core` folder to your source and include `joycon-core.cpp`.

See the `README.md` file in `joycon-core` for more information on how it works.

Tested using g++ on Ubunutu 18.04 LTS.

## Dependencies

Dependency:

- libhidapi

Installation:

    sudo apt install libhidapi-dev

Linking:

    -lhidapi-hidraw

Check the makefile in the example for more info. This includes other linkage, e.g. pthread.

## Example

I have written a simple example that lets you have your joycon act as a mouse. This requires that your computer runs using X server.

### Dependencies

Extra Dependency:

- libxtst

Installation:

    sudo apt-get install libxtst-dev

Linking:

    -lX11 -lXtst

### Building / Running
Edit the MAC adress inside the code to your joycon, compile, run the program as super user and BOOM you got a joycon mouse.

Build using the make file:

    sudo make all

Press the Home (screenshot) button to exit the program, Z-Trigger to click, joystick to move.

## Other Remarks

If you can't get it to work feel free to drop me a question. I am happy to help you out.

This repo is based mostly off of the work of these fine people:

    https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering

    https://github.com/Armag3ddonDev/joycon

I simply finished the button / joystick mapping, implemented the event system,
and wrapped it so that joycons could be managed individually.

I have sliced out some experimental features for cleanness, but might add them back as I am more happy with the structure and stability of the API and know how to incorporate it cleanly.

If you would like to contribute or have suggestions on how this can be improved, please let me know.

## To-Do

Find a way to let this run as a daemon that we can communicate with, so I can query data and bind / release joycons at will through a separate commandline program. Then, make a nice polybar widget.

## License

MIT - Steal this code and sell it.

I AM ABSOLUTELY NOT RESPONSIBLE FOR ANY DAMAGE DONE TO YOUR JOYCONS OR OTHER DEVICES.

THE CODE HAS BEEN TESTED BUT I PROVIDE NO GUARANTEE OF ITS STABILITY, USEABILITY OR USEFULNESS.
