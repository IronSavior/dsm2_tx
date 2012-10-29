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
#include "interpolated_curve.h"
#include "expo_curve.h"

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
  raw.set_value(1);
  trim.set_margin(0);
  trim.set_offset(1);
  cout << "max offset 0: " << input.value() << endl;
}


void print_map_test(long fromlow, long fromhigh, long tolow, long tohigh) {
  long x = 0;
  cout << "center x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = 1;
  cout << "center +1 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = -1;
  cout << "center -1 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = 33;
  cout << "center +33 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = -33;
  cout << "center -33 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MIN_VALUE+1;
  cout << "min +1 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MAX_VALUE-1;
  cout << "max -1 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MIN_VALUE+33;
  cout << "min +33 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MAX_VALUE-45;
  cout << "max -33 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MIN_VALUE/2;
  cout << "min/2 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MAX_VALUE/2;
  cout << "max/2 x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MIN_VALUE;
  cout << "min x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  x = InputElement::MAX_VALUE;
  cout << "max x= " << x << ": " << map(x,fromlow,fromhigh,tolow,tohigh) << endl;
  cout << endl;
}

void map_test() {
  long fromlow, fromhigh, tolow, tohigh;
  fromlow  = InputElement::MIN_VALUE;
  fromhigh = InputElement::MAX_VALUE;
  
  cout << "** map tests" << endl;
  cout <<  "min: " << InputElement::MIN_VALUE;
  cout << " max: " << InputElement::MAX_VALUE << endl;

  cout << "Target range same as source:" << endl;
  tolow = InputElement::MIN_VALUE;
  tohigh = InputElement::MAX_VALUE;
  print_map_test(fromlow,fromhigh,tolow,tohigh);

  cout << "10% reduced margin:" << endl;
  tolow = InputElement::MIN_VALUE-InputElement::MIN_VALUE/10;
  tohigh = InputElement::MAX_VALUE-InputElement::MAX_VALUE/10;
  print_map_test(fromlow,fromhigh,tolow,tohigh);

  cout << "25% reduced margin:" << endl;
  tolow = InputElement::MIN_VALUE-InputElement::MIN_VALUE/4;
  tohigh = InputElement::MAX_VALUE-InputElement::MAX_VALUE/4;
  print_map_test(fromlow,fromhigh,tolow,tohigh);

  cout << "reduced margin by 1:" << endl;
  tolow = InputElement::MIN_VALUE+1;
  tohigh = InputElement::MAX_VALUE-1;
  print_map_test(fromlow,fromhigh,tolow,tohigh);

  cout << "Target range 0 - 0x03FF:" << endl;
  tolow = 0;
  tohigh = 0x03FF;
  print_map_test(fromlow,fromhigh,tolow,tohigh);
}

void print_expo_points_test( ExpoCurve &curve ) {
  unsigned int count = curve.get_point_count();
  InterpolatedCurve::Point *points = curve.get_points();
  cout << "Expo Points Test - points: " << count << " - factor: " << curve.get_factor() << endl;
  for( int i = 0; i < count; i++) {
    cout << "  " << i << ":    " << points[i].x << " \t , \t " << points[i].y << endl;
  }
  cout << endl;
}

void expo_points_test() {
  ExpoCurve curve;
  for( float factor = 0.0; factor < 1.1; factor += 0.1 ) {
    curve.set_factor(factor);
    print_expo_points_test(curve);
  }
}

void expo_values_test() {
  ExpoCurve expo;
  RawInput raw;
  expo.set_source(raw);
  expo.set_factor(0.5);
  print_expo_points_test(expo);
  cout << "Expo Values Test -- factor: " << expo.get_factor() << endl;
  for( int v = RawInput::MIN_VALUE; v <= RawInput::MAX_VALUE; v += RawInput::MAX_VALUE/5 ) {
    raw.set_value(v);
    cout << "  x = " << raw.value() << "  y = " << expo.value() << endl;
  }
  cout << endl;
}

void run_tests();
int main(int argc, char **argv){
  initialize_mock_arduino();
  run_tests();
}

void run_tests() {
  expo_values_test();
}
