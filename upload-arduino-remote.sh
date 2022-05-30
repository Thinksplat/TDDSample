cd platformio
sh prepare.sh $1
pio remote run  --target upload
