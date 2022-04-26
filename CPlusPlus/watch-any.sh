mkdir build 2> /dev/null

inotifywait -e close_write,moved_to,create -m $2 $3 $4 $5 $6 |
while read -r directory events filename; do
  (cd build && cmake .. && make && $1)
done
