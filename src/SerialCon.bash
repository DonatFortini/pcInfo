#!/bin/bash
while [ test /dev/ttyACM0 ]; do
    sum=0
    for zone in {0..3}; do
        temp=$(cat "/sys/class/thermal/thermal_zone${zone}/temp")
        sum=$((sum + temp))
    done
    CPUTEMP=$((sum / 4000))
    CPUFREQ=$(cat /proc/cpuinfo | grep "MHz" | awk '{sum+=$4} END {printf "%.2f", sum/NR/1000}')

    echo "${CPUTEMP}${CPUFREQ}" >/dev/ttyACM0
done
