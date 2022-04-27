mkdir build 2> /dev/null
(cd build && ninja && ./all_tests)

inotifywait -e close_write,moved_to,create -m tests lib lib-behaviour shared |
while read -r directory events filename; do
  (cd build && cmake .. && ninja && ./all_tests)
done
