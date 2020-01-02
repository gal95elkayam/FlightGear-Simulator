# FlightGear-Simulator
An Interpreter project for a FlightGear flight simulator. The program connects to the simulator and flys the aircraft based on the user's commands.
Prerequisites

    Linux environment to run the code

## Installing

   . Download and install the simulator on your computer - https://www.flightgear.org/download/
   . Add the generic_small.xml file to the /data/Protocol directory where you installed the simulator
   . Config the following settings in the 'Settings' tab in the simulator:

    --telnet=socket,in,10,127.0.0.1,5402,tcp
    --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small

simulator-settings-config

This will open two communication sockets - 'in' where you send commands to the simulator, and 'out' where you receive data from it.
## Running

a. Exceute the code using the terminal or any c++ work environment. The program will wait for a connection from the simulator.

b. Click the 'Fly!' icon in the simulator in the bottom left corner (see above picture), and wait for the simulator to load. It will connect to the interpreter in the meantime.

The code is designed to read lines of commands entered in a terminal from the user once the program has started running. The commands can be entered one at a time or by using a pre-made script (make sure each command starts in a new line).

   irst, enter the following commands to open a local communication server to the simulator and connect to it:

     openDataServer 5400
     connect 127.0.0.1 5402


   Initialize your variables:

    var heading <- sim(""/instrumentation/heading-indicator/indicated-heading-deg"")
    var airspeed <- sim("/instrumentation/airspeed-indicator/indicated-speed-kt")
    var roll <- sim("/instrumentation/attitude-indicator/indicated-roll-deg")
    var pitch <- sim("/instrumentation/attitude-indicator/internal-pitch-deg")
    var rudder -> sim("/controls/flight/rudder")
    var aileron -> sim("/controls/flight/aileron")
    var elevator -> sim("/controls/flight/elevator")
    var alt <- sim("/instrumentation/altimeter/indicated-altitude-ft")
    var rpm <- sim("/engines/engine/rpm")

   Initialize variables bind a variable to a specific path. See generic_small.xml file for all paths.

   Exceute your commands:

    breaks = 0
    throttle = 1
    var h0 = heading
    while alt < 1000 {
    rudder = (h0 – heading)/20
    aileron = - roll / 70
    elevator = pitch / 50
    print alt
    sleep 250
    }
    print "done"

The program reads the code, parses it and sends the commands to the simulator, changing the behavior of the aircraft accordingly. In this example, the interpreter enters the loop, adjusts variables, prints the current altitude of the aircraft and halts the reading for 250 miliseconds. When the altitude is over 1000, the loop will terminate and the next lines will be parsed.

When the program reads the keyword "done", it will stop sending commands to the simulator, terminating the communication with it and ending the program.
