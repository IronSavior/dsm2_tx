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

#ifndef _TEST_
#include <Arduino.h>
#else
#include "mock_arduino.h"
#endif

#include "expo_curve.h"

void ExpoCurve::set_factor( const float factor ) {
  _factor = constrain(factor, 0, 1);
  compute_points();
}

float ExpoCurve::get_factor() {
  return _factor;
}

void ExpoCurve::compute_points() {
  float k = EXPO_C * ((EXPO_C - 1.0)*_factor*_factor*_factor+_factor)/EXPO_C + 1.0;
  for( unsigned int i = 0; i < EXPO_POINTS; i++ ) {
    float x = 2.0/(EXPO_POINTS - 1.0) * i - 1.0;
    float y = ((k-1.0)*x*x*x*x*x + x)/k;
    _points[i].x = x * MAX_VALUE;
    _points[i].y = y * MAX_VALUE;
  }
}
