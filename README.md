# OpenOBD
[![Build Status](https://travis-ci.org/alexmohr/OpenOBD.svg?branch=master)](https://travis-ci.org/alexmohr/OpenOBD)

This is an open implementation of the OBD protocol. It utilizes socket can for communication on Linux ( windows not supported at the moment ).
At the moment the only supported communication protocol is ISO 15765 CAN (ISO-TP), at any baudrate the used can adapter supports.
The standard defines 250 kbit/s or 500 kbit/s.
Please note that all configuration of the can interfaces must be done before using this software.

## Features
### Simulate a vehicle
With the vehicle simulation an OBD dongle can be used without an actual vehicle. This can be used for testing new implementations.
### OBD Tester
The software can be used to communicate with a vehicle to read OBD data from it. This requires a can connection to the vehicle. 
Note that the tester mode cannot be used together with an interface like ELMClient but is rather a full implementation of the CAN protocol. 
This means you need a CAN connection to the vehicle. The baud rate must be set on the connected can interface. This software will only 
connect to the interface via socket so will not be able to configure baud rates.

### ELM 327 
This software supportes ELM interfaces using wifi and serial.
Furthermore can expose the CAN interface with the ELM API altough only a very small command subset is implemented

## Building and running
As this is a work in progress, no pre built binaries are available at the moment.
Prerequisites:
* cmake 
* gcc-8 
* can-utils
* g++-8
Any other compiler than g++-8 with C++17 support should work as well but is not ( yet ) supported officially.

````
mkdir build
cd build
cmake ../
make
sudo make install
````

## CLI
![CLI Example](https://github.com/alexmohr/OpenOBD/blob/master/doc/cli_example.png)

The CLI is a terminal like frontend which allows setting and reading values. It can act as a tester or as an ecu. 
It supports:
* Autocomplete via tab
* History
* Very simple scripting engine

The "scripting" is not really a fully fledged programming language like lua or python but allows to execute commands
in the order of how they are written down in a plain text file. 
To slow down the execution of the commands the sleep command can be used which delays the execution by the given 
amount of milliseconds. 

## Web interface
Coming in the future <3
