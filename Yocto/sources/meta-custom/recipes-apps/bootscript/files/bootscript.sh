#!/bin/bash

echo -e "######## Bootscript Start! ########"

# Try to configure ethernet
ifconfig end0 192.168.1.10 netmask 255.255.255.0

if [ $? -ne 0 ]; then
    echo "Network configuration failed!"
    exit 1
else
    echo "Network configured successfully"
fi

# Mount SD Card
mkdir -p /mnt/sd
mount /dev/mmcblk0p1 /mnt/sd
echo "Mounted SD"
tcp-server
exit 0