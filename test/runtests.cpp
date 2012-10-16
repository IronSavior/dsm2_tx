/*
  DSM2_tx implements the serial communication protocol used for operating
  the RF modules that can be found in many DSM2-compatible transmitters.

  Copyrigt (C) 2012  Erik Elmore <erik@ironsavior.net>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.  
*/

#include "mock_arduino.h"
#include "dsm2_tx.h"
#include "raw_input.h"
#include "trim.h"

using namespace std;

void millis_test() {
  unsigned long start = millis();
  cout << "millis() test start: " << start << endl;
  while( millis() - start < 10000 ) {
    cout << millis() << endl;
    sleep(1);
  }
  unsigned long end = millis();
  cout << "End of test - duration: " << end - start << "ms" << endl;
}

void delay_test() {
  unsigned long start = millis();
  cout << "delay() test start: " << start << endl;
  while( millis() - start < 10000 ) {
    cout << millis() << endl;
    delay(250);
  }
  unsigned long end = millis();
  cout << "End of test - duration: " << end - start << "ms" << endl;
}

void raw_input_test() {
  RawInput raw;
  InputElement &input = raw;
  
  cout << "raw initial value: " << raw.value() << endl;
  
  raw.set_value(-16);
  cout << "raw value " << raw.value() << " (expected: -16)" << endl;
  cout << "input value " << input.value() << " (expected: -16)" << endl;
}

void bind_test() {
  DSM2_tx tx(6);
  tx.bind();
}

void transmit_frame_test() {
  DSM2_tx tx(6);
  for( int i = 0; i < 6; i++) {
    tx.set_channel(i, 0);
  }
  tx.send_frame();
}

void trim_test() {
  RawInput raw;
  Trim trim;
  trim.set_source(raw);
  InputElement &input = trim;
  
  cout << "  Trim Tests" << endl;
  cout << "initial value: " << input.value() << endl;
  raw.set_value(32000);
  trim.set_offset(0);
  cout << "1 offset 0: " << input.value() << endl;
}

void map_test() {
  long x, fromlow, fromhigh, tolow, tohigh;
  fromlow  = InputElement::MIN_VALUE;
  fromhigh = InputElement::MAX_VALUE;
  tolow = InputElement::MIN_VALUE;
  tohigh = InputElement::MAX_VALUE;
  x = 0;
  cout << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = 1;
  cout << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = -1;
  cout << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = 5;
  cout << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
}

void run_tests();
int main(int argc, char **argv){
  initialize_mock_arduino();
  run_tests();
}

void run_tests() {
  cout << "min: " << InputElement::MIN_VALUE << " max: " << InputElement::MAX_VALUE << endl;
  trim_test();
  map_test();
}
