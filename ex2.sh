#!/bin/bash

check_mem_free() { 
    percentage=($(awk '$1 == "MemTotal:" {MemTotal = $2} $1 == "MemFree:" {percentage = ($2/MemTotal)*100} END {if(percentage < 10) {print percentage} else {print 0}}' /proc/meminfo))
    if [ ${percentage[0]} != 0 ]; then # percentage < 10
        for item in /tmp/*; do
            if [ $item == "/tmp/swap" ]; then
                echo "El fitxer de swap ja ha estat creat"
                return 
            fi
        done
        echo "Procedim a la creació del fitxer swap:"
        ./swap.sh
    fi
}

for i in {1..60}; do
	check_mem_free
	sleep 1
done