#!/bin/bash

BUILDID="build-$RANDOM"
INSTANCE="travisci/ci-garnet:packer-1515445631-7dfb2e1"

sudo systemctl start docker
sudo docker run --name $BUILDID -dit $INSTANCE /sbin/init
sudo docker exec -it $BUILDID bash -l

