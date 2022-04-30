mkdir build 2> /dev/null
# Run the command first
sh build-arduino.sh PrototypeRaw

inotifywait -e close_write,moved_to,create -m $1 $2 $3 $4 $5 $6 $7 $8 $9 |
while read -r directory events filename; do
  sh build-arduino.sh PrototypeRaw
done
