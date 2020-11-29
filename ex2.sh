#!/bin/bash

check_mem_free() { 
    awk -v swap_id="$1" '$1 == "MemTotal:" {MemTotal = $2} $1 == "MemFree:" {percentage = ($2/MemTotal)*100}
        END {
            if(percentage < 10){
                print "Memòria lliure inferior al 10%\n Es procedeix a la creació d'\''un fitxer swap...\n"
                system(sprintf("./swap.sh %s",swap_id))
            }
        }
    ' /proc/meminfo
}

for i in {1..60}; do
	check_mem_free "$i"
	sleep 1
done