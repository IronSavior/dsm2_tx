#include <cstring>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "dsm2_tx.test.h"
#include "dsm2_tx.h"

using namespace std;

unsigned long millis() {
  return clock();
}

void delay(unsigned long ms) {
  unsigned long start = millis();
  while(millis() - start < ms){}
}

void FakeSerial::begin(unsigned long speed) {
  return;
}

void FakeSerial::end() {
  return;
}

size_t FakeSerial::write( const unsigned char buf[], size_t size ) {

  ios_base::fmtflags oldFlags = cout.flags();
  streamsize oldPrec = cout.precision();
  char oldFill = cout.fill();
  
  cout << "Serial::write: ";
  cout << internal << setfill('0');

  for( unsigned int i = 0; i < size; i++ ){
    cout << setw(2) << hex << (unsigned int)buf[i] << " ";
  }
  cout << endl;
  
  cout.flags(oldFlags);
  cout.precision(oldPrec);
  cout.fill(oldFill);

  return size;
}

int main(int argc, char **argv){
  DSM2_tx tx(6);
  tx.begin();
  tx.send_frame();
}

FakeSerial Serial;
