inotifywait -e close_write,moved_to,create -m tests lib shared |
while read -r directory events filename; do
  (cd build && cmake .. && make && make test)
done
