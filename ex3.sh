#!/bin/bash
# Ramdisk
ROOTUSER_NAME=root
MOUNTPT=/tmp/ramdisk
SIZE=2048	        # 2K blocs
BLOCKSIZE=1024	    # mida bloc: 1K (1024 bytes)
DEVICE=/dev/ram0	# Primer Ram Disc

username=`id -nu`   # equivalent a fer username=$USER
[ "$username" != "$ROOTUSER_NAME" ] && echo "no autoritzat" && exit 1
[ ! -d "$MOUNTPT" ] && mkdir $MOUNTPT 
dd if=/dev/zero of=$DEVICE count=$SIZE bs=$BLOCKSIZE
mkfs.ext4 $DEVICE	    # Crea un sf ext4
# també es podria fer mkfs -t ext4 $DEVICE , o bé /sbin/mke4fs $DEVICE 
 
mount $DEVICE $MOUNTPT  # el munta
chmod 777 $MOUNTPT
echo $MOUNTPT " disponible"
exit 0