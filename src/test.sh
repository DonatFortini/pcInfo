data="CPU->${CPUTEMP},${CPUFREQ} FAN->242,252 RAM->90,3.41 WIFI->25.1,3.15"
echo "Sending: $data"
echo "$data" >/dev/ttyACM0
sleep 1
