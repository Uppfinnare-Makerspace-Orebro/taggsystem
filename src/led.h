#pragma once

void initLed(int pin);

void flash(int num, int delayMs = 100);
void updateLed(int passedMs);
void setLed(bool value);
