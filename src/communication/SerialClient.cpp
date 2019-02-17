//
// Created by me on 26/01/19.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <asm/termbits.h> /* struct termios2 */
#include <time.h>
#include <syslog.h>
#include <net/if.h>
#include <linux/can.h>
#include <stdarg.h>
#include <thread>


#include "SerialClient.h"
#include "easylogging++.h"


SerialClient::SerialClient(int baudrate, char *ttyDevice) {
    this->baudrate = baudrate;

    size_t ttyLen = static_cast<int>(strlen(ttyDevice));
    if (ttyLen > 0) {
        this->ttyDevice = new char[ttyLen + 1];
        strcpy(this->ttyDevice, ttyDevice);
    }
}

SerialClient::~SerialClient() {
    delete[] ttyDevice;
}


int SerialClient::openInterface() {
    ttyFd = ::open(ttyDevice, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (ttyFd == -1) {
        LOG(ERROR) << "Failed to open Interface: '" << ttyDevice << "': " << strerror(errno);
        return -1;
    }

    if (0 == this->baudrate) {
        return openSerialPortAutoBaud();
    }

    return openSerialPort();
}

int SerialClient::openSerialPort() {
    int result;
    struct termios2 tio;

    result = ioctl(ttyFd, TCGETS2, &tio);
    if (result == -1) {
        el::Loggers::getLogger("default")->error("ioctl() failed: %s\n", strerror(errno));
        close(ttyFd);
        return -1;
    }

    tio.c_cflag &= ~CSTOPB;            // 1 stop bit
    tio.c_cflag &= ~CRTSCTS;           // Disable hardware flow control
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag = BOTHER | CS8;
    tio.c_iflag = IGNPAR;
    tio.c_oflag = 0;
    tio.c_lflag = 0;
    tio.c_ispeed = (speed_t) baudrate;
    tio.c_ospeed = (speed_t) baudrate;

    result = ioctl(ttyFd, TCSETS2, &tio);
    if (result == -1) {
        el::Loggers::getLogger("default")->error("ioctl() failed: %s\n", strerror(errno));
        close(ttyFd);
        return -1;
    }

    clientOpen = true;
    return 0;
}

int SerialClient::openSerialPortAutoBaud() {
    const string testMessage = getElmConfigString(ELM_CONFIG_ECHO, false) + ELM_FLOW_NEWLINE;

    int recvSize = 0;
    int bufSize = 255;
    int retVal = 1;
    byte *buf = new byte[255];


    for (const auto &baudrate: POSSILBE_BAUDRATES) {
        memset(buf, 0, bufSize);
        this->baudrate = baudrate;
        if (openSerialPort() != 0) {
            LOG(DEBUG) << "Failed to open interface with baudrate: " << baudrate;
            continue;
        }

        if (send((byte *) testMessage.c_str(), static_cast<int>(testMessage.size())) > 0) {
            this_thread::sleep_for(500ms);
            receive(buf, bufSize, recvSize);
            if (messageContains(buf, recvSize, ELM_FLOW_OK)) {
                LOG(INFO) << "Found baudrate for adapter: " << baudrate;
                retVal = 0;
                break;
            }
        }

        closeInterface();
    }

    if (retVal != 0)
        LOG(ERROR) << "Could not find baudrate automatically. Try setting it by hand.";
    delete[] buf;
    return retVal;
}

int SerialClient::closeInterface() {
    int res = close(ttyFd);
    if (res != 0) {
        el::Loggers::getLogger("default")->error("Failed closing ttyFd %s \n", strerror(errno));
    }
    clientOpen = false;
    return res;
}

int SerialClient::send(byte *buf, int buflen) {
    int result = (int) write(ttyFd, buf, (size_t) buflen);
    return result;
}

void SerialClient::receive(byte *buffer, int buffSize, int &readSize) {
    readSize = static_cast<int>(read(ttyFd, buffer, buffSize));
}

int SerialClient::configureInterface() {
    write(ttyFd, ELM_DEVICE_RESET.c_str(), ELM_DEVICE_RESET.size());
    this_thread::sleep_for(1s); // give device time to init.
    return 0;
}

bool SerialClient::isOpen() {
    return clientOpen;
}


