
/*
 * This file is based on the can-utils linux software and published under gpl
 * isotpsend.c
 * isotprecv.c
 *
 * Copyright (c) 2008 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which case the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data structures and external interfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * Send feedback to <linux-can@vger.kernel.org>
 *
 */


#include "CanIsoTP.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/isotp.h>


CanIsoTP::CanIsoTP(unsigned int rxId, unsigned int txId, char *ifname) {
    this->rxId = rxId;
    this->txId = txId;

    size_t nameLen = static_cast<int>(strlen(ifname));
    if (nameLen > 0) {
        this->ifname = static_cast<char *>(malloc(nameLen));
        strcpy(this->ifname, ifname);
    }
}


CanIsoTP::~CanIsoTP() {
    delete ifname;
}


int CanIsoTP::openInterface() {
    if (rxId > MAX_CAN_ID_EXTENDED || rxId == 0 ||
        txId > MAX_CAN_ID_EXTENDED || txId == 0
        || txId == rxId) {
        return InvalidIds;
    }

    struct sockaddr_can addr;
    static struct can_isotp_options opts;
    static struct can_isotp_fc_options fcopts;
    static struct can_isotp_ll_options llopts;
    int force_rx_stmin = 0;

    addr.can_addr.tp.tx_id = addr.can_addr.tp.rx_id = NO_CAN_ID;

    addr.can_addr.tp.tx_id = static_cast<canid_t>(txId);
    if (txId > MAX_CAN_ID_NORMAL) { // set extended flag
        addr.can_addr.tp.tx_id |= CAN_EFF_FLAG;
    }

    addr.can_addr.tp.rx_id = static_cast<canid_t>(rxId);
    if (rxId > MAX_CAN_ID_NORMAL) {
        addr.can_addr.tp.rx_id |= CAN_EFF_FLAG;
    }

    opts.flags |= (CAN_ISOTP_TX_PADDING | CAN_ISOTP_RX_PADDING);
    //opts.flags |= (CAN_ISOTP_CHK_PAD_LEN | CAN_ISOTP_CHK_PAD_DATA);


    if ((socketHandle = socket(PF_CAN, SOCK_DGRAM, CAN_ISOTP)) < 0) {
        perror("socket");
        return FailedToOpenSocket;
    }

    setsockopt(socketHandle, SOL_CAN_ISOTP, CAN_ISOTP_OPTS, &opts, sizeof(opts));
    setsockopt(socketHandle, SOL_CAN_ISOTP, CAN_ISOTP_RECV_FC, &fcopts, sizeof(fcopts));


    if (llopts.tx_dl) {
        if (setsockopt(socketHandle, SOL_CAN_ISOTP, CAN_ISOTP_LL_OPTS, &llopts, sizeof(llopts)) < 0) {
            perror("link layer sockopt");
            return FailedToOpenSocket;
        }
    }

    if (opts.flags & CAN_ISOTP_FORCE_RXSTMIN) {
        setsockopt(socketHandle, SOL_CAN_ISOTP, CAN_ISOTP_RX_STMIN, &force_rx_stmin, sizeof(force_rx_stmin));
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = if_nametoindex(ifname);

    struct timeval tv;
    tv.tv_sec = 1;  /* 1 sec timeout */
    setsockopt(socketHandle, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));


    if (bind(socketHandle, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        closeInterface();
        return FailedToOpenSocket;
    }

    return 0;
}

