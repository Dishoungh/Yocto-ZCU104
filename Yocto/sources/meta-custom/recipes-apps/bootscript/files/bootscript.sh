#!/bin/bash

echo -e "######## Bootscript Start! ########"

# Mount SD Card
mkdir -p /mnt/sd
mount /dev/mmcblk0p1 /mnt/sd
echo "Mounted SD"
tcp-server