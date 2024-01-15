
#include <Arduino.h>
#include <emscripten/html5.h>
#include <iostream>

void doLoop(void *) {
    loop();

    emscripten_set_timeout(&doLoop, 1000, nullptr);
}

int main() {
    setup();

    std::cout << "started" << std::endl;

    doLoop(nullptr);
}
