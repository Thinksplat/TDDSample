mkdir build 2> /dev/null
(cd build && cmake .. && make && ./all_tests)

inotifywait -e close_write,moved_to,create -m tests lib lib-behaviour shared |
while read -r directory events filename; do
  (cd build && cmake .. && make && ./all_tests)
done
