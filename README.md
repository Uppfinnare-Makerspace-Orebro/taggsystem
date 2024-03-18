# taggsystem
SUF taggsystem för maskiner

# Dependencies
Install the `MFRC522` - library for arduino

# Connections in prototype

LED pin 6 (out)
button signal in 7
button activation pin 8 (should be always on)
relay pin 2


# States

0 - Default. Identified user or admin will signal to the relay, holding button at the same time triggers state 1
1 - Admin state - Add user, button triggers next state, tag adds user
2 - Admin state - Add admin, button triggers next state, tag adds admin
3 - Admin state - Remove admin, button triggers next resets to next state, tag deletes user

4 - Trigger if no user is set, then the first user showing its card will be admin

# Build arduino

Install platformio. Make sure that the command `platformio` or `pio` is available.
if one does not exist try the other.

run

`platformio run -t build` to find compilation errors

run 

`platformio run -t upload` to build and upload the program to the arduino

# Build test project (ubuntu linux pc tests, without a physical device)

Install cmake, build-essensial etc.

create build directory and build

```bash
mkdir build
cd build
cmake ../.. -DCMAKE_BUILD_TYPE=Debug
make -j
``` 

Run tests:

In the build directory

```bash
ctest .
```

# Build emscripten (web simulator)

Install emscripten

run like the simulator above but replace `cmake` with `emcmake cmake`...
and `make` with `emmake make`
