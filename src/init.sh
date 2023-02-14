#!/bin/sh
# Note /bin/sh will get auto created by igloo

echo "Test image running"

echo "Bringing up network with igloo busybox"
/igloo/utils/busybox ip link set lo up

echo "Launching UDP service on 8080 with key hi"
/bin/udp_server 8080 hi &

echo "Launching UDP service on 9000 with key foo"
/bin/udp_server 9000 foo &

echo "Fake init finishes, sleeping forever"
/igloo/utils/busybox sleep 9999;
