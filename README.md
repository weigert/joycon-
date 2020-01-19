# joycon++
Unix joycon driver in C++ with simple command-line interface for communication and binding of actions.

As there already exist joycon drivers for windows, this is only for unix.

I couldn't find a nicely interfaceable joycon driver for linux so I wrote this for average users.

## How it Works

### C++ API
A joycon driver in C++ can communicate with connected bluetooth devices by starting a joycon-server. 

This server can be started from code, after which you can define your own button-press callbacks and have access to the raw joycon streaming data. You can also use code to send information to the joycons and set properties of the joycons from code.

If you are interested in how the code works, I recommend looking at the raw joycon C++ API without all the other bells and whistles.

## Command-Line Tool
You can launch the joycon-server in wrapped form, after which it listens on a few named pipes for inputs.

A specially written command line tool can then interface with these named pipes to query the server and do a number of things with the joycons. This acts as your user-friendly interface for managing your joycons.

You can then define binding profiles for your joycons using config files, and bind them using the command-line tool. This allows arbitrary shell code to be executed upon button presses, as well as a few special things that I have programmed specifically for this application (mouse movement, scrolling, etc.).

## GUI Tool
In the future, by interacting with the named pipes in the exact same way, you could actually make a simple unix based GUI tool. I'll see if I have time or motivation to do this.

## Polybar Widget

I have also written a basic polyar widget for displaying the joycon information and managing the connection.

## Installation

Tested using g++ on Ubunutu 18.04 LTS.

## Usage


## Questions

If you can't get it to work feel free to drop me a question. I am happy to help you out.

## License

MIT - Steal this code and sell it.

I AM ABSOLUTELY NOT RESPONSIBLE FOR ANY DAMAGE DONE TO YOUR JOYCONS OR OTHER DEVICES.

THE CODE HAS BEEN TESTED BUT I PROVIDE NO GUARANTEE OF ITS STABILITY, USEABILITY OR USEFULNESS.
