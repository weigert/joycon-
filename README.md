# joycon++
Unix joycon driver in C++ with simple command-line interface for communication and binding of input actions.

As there already exist joycon drivers for windows, this is only for unix.

I couldn't find a nicely interfaceable joycon driver for linux so I wrote this for average users.

## How it Works

### C++ API
The joycon API contains a joycon manager class. This manages the joycon communication.

You can bind and unbind connected bluetooth devices if they are joycons.

It keeps track of a vector of joycon datastructures, stores their relevant information, streams their inputs and keeps track of input events, which you can poll to trigger arbitrary code upon inputs.

You can for instance define callbacks upon event triggering via joycon input.

If you are interested in how the code works, I recommend looking at the raw joycon C++ API without all the other bells and whistles.

## Server and Command-Line Tool
The joycon server wraps the C++ API. It listens on a named pipe for user inputs through the command line tool, which allows for user-friendly interfacing with the API.

The server will keep track of the joycon objects, lets you query it for information, set joycon information, bind and unbind the joycons, and profile the joycons using a config file.

The profile will listen for input events and trigger arbitrary code (e.g. shell commands) or pre-defined callbacks (e.g. mouse movement for joysticks, scrolling, etc).

You can query information such as batter state or joycon color, for use in other applications.

## Polybar Widget
The polybar widget will ping the server to see if it is online, and if it is will display all bound joycons in their respective colors and allow for simple binding and unbinding. This allows for easy management of your joycons. It will also display their battery state.

## GUI Tool
In the future, by interacting with the named pipes in the exact same way, you could actually make a simple unix based GUI tool. I'll see if I have time or motivation to do this.

## Installation

Tested using g++ on Ubunutu 18.04 LTS.

## Compiling

## Usage
See the individual folders for usage information.

    joycon-api

      Pure C++ Joycon-API, which lets you interface with the bluetooth devices.

    joycon-server

      The joycon server. Simply launch the server and it will be listening for commandline input!
      This can be launched as a daemon and then acts as a form of driver.

    joycon-interface

      The commandline tool with options. Use this to interface with the server.

## Questions

You will find more information about the individual in their individual readme files.

If you can't get it to work feel free to drop me a question. I am happy to help you out.

## License

MIT - Steal this code and sell it.

I AM ABSOLUTELY NOT RESPONSIBLE FOR ANY DAMAGE DONE TO YOUR JOYCONS OR OTHER DEVICES.

THE CODE HAS BEEN TESTED BUT I PROVIDE NO GUARANTEE OF ITS STABILITY, USEABILITY OR USEFULNESS.
