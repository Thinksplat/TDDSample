PROJ=$1
if [ -z "$PROJ" ]; then
  PROJ="PrototypePinball"
fi
rm -rf lib/* include/*
cp ../$PROJ/main.cpp src
cp -r ../lib include/.
cp -r ../shared include/.
cp -r ../lib-behaviour include/.
cp -r ../interface include/.
cp ../bsp-arduino/* include/.
