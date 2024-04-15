# taggsystem
SUF taggsystem för maskiner

# Dependencies
Install the `MFRC522` - library for arduino

# Connections in prototype

## Esp32

| component pin | port on esp32 | 
| --        | ---         |
| LED red   | pin 2 (out) - also builtin led |
| LED black | GND         |
| Button 1  | 16          |
| Button 2  | GND         |
| relay s   | 22          |
| relay +   | 3,3V        |
| relay -   | GND         |
| RC VCC    | 3.3V        |
| RC RST    | 4           |
| RC GND    | GND         |
| RC MISO   | 19          |
| RC MOSI   | 23          |
| RC SCK    | 18          |
| RC NSS    | 5           |


# States

 0. Default. Identified user or admin will signal to the relay, holding button at the same time triggers state 1
 1. Button is pressed when no user is identified
 2. Admin state - Add user, button triggers next state, tag adds user
 3. Admin state - Add admin, button triggers next state, tag adds admin
 4. Admin state - Remove admin, button triggers next resets to next state, tag deletes user
 5. Trigger if no user is set, then the first user showing its card will be admin

# Build arduino

Install platformio. Make sure that the command `platformio` or `pio` is available.
if one does not exist try the other.

If you want to install arduino for the commandline on ubuntu use the command

```
pip3 install platformio
```

run

```bash
platformio run -e esp32` to find compilation errors
```

run 

```bash
platformio run -e esp32 -t upload` to build and upload the program to the arduino
```


Build and run esp32
```bash
platformio run -e esp32 --target upload
```


## Todo:
- [ ] Connect and test relay
- [ ] Asynchronous flash that does not delay state logic

## Advanced: Build test project (ubuntu linux pc tests, without a physical device)

Install 

```bash
sudo apt install cmake build-essensial
```

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



