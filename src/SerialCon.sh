#!/bin/bash
while true; do
    sum=0
    for zone in {0..3}; do
        temp=$(cat "/sys/class/thermal/thermal_zone${zone}/temp")
        sum=$((sum + temp))
    done
    CPUTEMP=$((sum / 4000))
    CPUFREQ=$(cat /proc/cpuinfo | grep "MHz" | awk '{sum+=$4} END {printf "%.2f", sum/NR/1000}')
    echo "CPU->${CPUTEMP},${CPUFREQ} FAN->242,252 RAM->90,3.41 WIFI->25.1,3.15"
    echo "CPU_${CPUTEMP},${CPUFREQ};FAN_242,252;RAM_90,3.41;WIFI_25.1,3.15;" >/dev/ttyACM0
    
    sleep 12
done
