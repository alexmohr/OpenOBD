# OpenOBD
[![Build Status](https://travis-ci.org/alexmohr/OpenOBD.svg?branch=master)](https://travis-ci.org/alexmohr/OpenOBD)

This is an open implementation of the OBD protocol. It utilizes socket can for communication on Linux ( windows not supported at the moment ).
At the moment the only supported communication protocol is ISO 15765 CAN (ISO-TP), at any baudrate the used can adapter supports.
The standard defines 250 kbit/s or 500 kbit/s.

## Features
### Simualte a vehicle
With the vehicle simulation an OBD dongle can be used without an actual vehicle. This can be used for testing new implementations.
Currently only ISO-TP is supported as protocol.  

### OBD Tester
The software can be used to communicate with a vehicle to read OBD data from it. This requires a can connection to the vehicle. 
Note that the tester mode cannot be used together with an interface like ELM327 but is rather a full implementation of the CAN protocol. 
This means you need a CAN connection to the vehicle. The baud rate must be set on the connected can interface. This software will only 
connect to the interface via socket so will not be able to configure baud rates.

### ELM 327 
The current version supports a very basic implementation for ELM interfaces using WIFI. 
Interfaces using USB, serial adpaters or bluetooth won't be supported due to the lack of hardware on my side. 
A pull request or a sponsered interface to add support for these would be welcome.

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
The CLI is a terminal like frontend which allows setting and reading values. It can act as a tester or as an ecu. 
At the moment it is very basic and does only support Service 1 and a small subset of pids.-0
![CLI Example](https://github.com/alexmohr/OpenOBD/blob/master/doc/cli_example.png)
