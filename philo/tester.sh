#!/bin/bash

if [ "$#" -ne 5 ]; then
	echo "Usage: $0 n_philos time_to_die time_to_eat time_to_sleep n_runs"
	exit 1
fi

N_PHILOS=$1
DIE=$2
EAT=$3
SLEEP=$4
RUNS=$5

PHILO_EXEC="./philo"
TOTAL=0
MIN=-1
MAX=0
DIED=0

for ((i=1; i<=RUNS; i++)); do
	OUTPUT=$($PHILO_EXEC $N_PHILOS $DIE $EAT $SLEEP)
	LAST_LINE=$(echo "$OUTPUT" | tail -n 1)
	TIME=$(echo "$LAST_LINE" | awk '{print $1}')
	MSG=$(echo "$LAST_LINE" | awk '{$1=""; print $0}')

	if [[ "$MSG" == *"died"* ]]; then
		DIED=$((DIED + 1))
		TOTAL=$((TOTAL + TIME))
		if [[ $MIN -eq -1 || $TIME -lt $MIN ]]; then
			MIN=$TIME
		fi
		if [[ $TIME -gt $MAX ]]; then
			MAX=$TIME
		fi
	fi

	echo "[$i/$RUNS] $LAST_LINE"
done

echo
echo "======== Summary ========"
echo "Runs with death: $DIED / $RUNS"
if [[ $DIED -gt 0 ]]; then
	AVG=$(echo "scale=2; $TOTAL / $DIED" | bc)
	echo "Earliest death: $MIN ms"
	echo "Latest death:   $MAX ms"
	echo "Average death:  $AVG ms"
else
	echo "No deaths occurred 🎉"
fi
