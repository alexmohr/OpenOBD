# OpenOBD
[![Build Status](https://travis-ci.org/alexmohr/OpenOBD.svg?branch=master)](https://travis-ci.org/alexmohr/OpenOBD)

This is an open implementation of the OBD protocol. It utilizes socket can for communication on Linux ( windows not supported at the moment ).

Supported OS: Linux 

## Features ( most features are not done yet because this is a work in progress )
### Simualte a vehicle
With the vehicle simulation an OBD dongle can be used without an actual vehicle. This can be used for testing new implementations. 

### OBD Tester
The software can be used to communicate with a vehicle to read OBD data from it. At a later point a graphical user interface will be added. 
This repository contains an open implementation of the OBD protocol. 
It can simulate a vehicle or can be used to communicate with an actual vehicle to read obd data. 

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
cmake --build .
# there is currently no install script because no usable front end exists yet 
````
