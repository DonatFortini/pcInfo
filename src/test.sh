data="CPUX${CPUTEMP},${CPUFREQ} FANX242,252 RAMX90,3.41 WIFIX25.1,3.15"
echo "Sending: $data"
echo "$data" >/dev/ttyACM0
sleep 1
