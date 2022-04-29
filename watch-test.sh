mkdir build 2> /dev/null
(cd build && ninja && ./all_tests)
  echo "Done"

inotifywait -e close_write,moved_to,create -m tests lib lib-behaviour shared bsp-linux |
while read -r directory events filename; do
  (cd build && cmake .. && ninja && ./all_tests)
  echo "Done"
done
