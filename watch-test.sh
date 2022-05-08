mkdir build 2> /dev/null
(cd build && cmake .. -G Ninja && ninja && ./all_tests)
  echo "Done"

inotifywait -e close_write,moved_to,create -m tests lib lib-behaviour shared bsp-linux interface |
while read -r directory events filename; do
  (cd build && cmake .. -G Ninja && ninja && ./all_tests)
  echo "Done"
done
