# joycon++ commandline tool

## Options

Usage: joycon --subcommand [required] <optional>

Bluetooth Connection:
  --find: List all Available Bluetooth Joycons
  --connect <ID>: Connect to an available joycon based on an ID. If no ID is specified, connects to all available.
  --disconnect <ID>: Disconnect to a connected joycon based on ID. If no ID is specified, disconnects from all.

Server Communication:
  --ping: Pings the joycon-server!
  --close: Safely closes the joycon-server.

Joycon Management:
  --list: List all bluetooth-connected and managed joycons
  --bind <ID>: Binds a bluetooth connected joycon to the joycon manager
  --release <ID>: Releases a managed joycon from the joycon manager

Joycon Settings (for managed joycons):
  --pair (pair two joycons manually)
  --unpair (unpair a joycon and its partner)
  --autopair (will wait for you to press the shoulder buttons)

  --player (set the player number for a joycon or joycon pair)
  --profile (bind the joycons button inputs to a specific profile from a config file)

Cosmetic Stuff:
  --rumble <amplitude> <frequency> (send a rumble to a specific joycon to test it)
  --blink <N> <HZ> <Intensity> (send a quick homebutton blink to the joycon)

Setters and Getters:
  --info (list a specific joycons data, color, ID, L / R, etc.)
  --setcolor (set the joycons color)
