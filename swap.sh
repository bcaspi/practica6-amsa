#!/bin/bash
#Swap

ROOT_UID=0
FILE=/tmp/swap
BLOCKSIZE=1024
MINBLOCKS=100
[ "$UID" -ne "$ROOT_UID" ] && echo "no autoritzat" && exit 1
dd if=/dev/zero of=$FILE bs=$BLOCKSIZE count=$MINBLOCKS
/sbin/mkswap -f $FILE $MINBLOCKS	# Crea fitxer swap
/sbin/swapon $FILE	                # Activa el fitxer swap
echo "Fitxer Swap creat i activat"
exit 0