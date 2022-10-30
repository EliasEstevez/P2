#!/bin/bash

# Be sure that this file has execution permissions:
# Use the nautilus explorer or chmod +x run_vad.sh

# Write here the name and path of your program and database
DIR_P2=$HOME/PAV/P2
DB=$DIR_P2/db.v4
<<<<<<< HEAD
CMD="$DIR_P2/bin/vad --alfa1=$1"
=======
CMD="$DIR_P2/bin/vad  --alfa1=$1"           #aqui meter en $1 el valor por defecto no?
<<<<<<< HEAD
>>>>>>> 6f0b0fbfff56b6249505210491ff263d0252d8f7
=======
#CMD="$DIR_P2/bin/vad  --alfa2=$2"
>>>>>>> bd57dca0aec8fdda36bf5f8ba015ed0ee61e3ed0

for filewav in $DB/*/*wav; do
#    echo
    echo "**************** $filewav ****************"
    if [[ ! -f $filewav ]]; then 
	    echo "Wav file not found: $filewav" >&2
	    exit 1
    fi

    filevad=${filewav/.wav/.vad}

    $CMD -i $filewav -o $filevad || exit 1

# Alternatively, uncomment to create output wave files
#    filewavOut=${filewav/.wav/.vad.wav}
#    $CMD $filewav $filevad $filewavOut || exit 1

done

scripts/vad_evaluation.pl $DB/*/*lab

exit 0
