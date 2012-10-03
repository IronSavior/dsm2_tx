#pragma once
#include <ctime>
#include <cstring>

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

typedef unsigned char byte;
typedef unsigned short int word;

unsigned long millis();
long map(long, long, long, long, long);
void delay(unsigned long ms);
unsigned long millis();

class FakeSerial {
public:
  void begin(unsigned long);
  void end();
  size_t write(const uint8_t*, size_t);
};

extern FakeSerial Serial;
