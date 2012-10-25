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

#include "interpolated_curve.h"

/* This method makes the following assumptions:
 *   1. The _points[] data member contians at least 2 defined Points.
 *   2. All defined Points have x and y values between MIN_VALUE and MAX_VALUE.
 *   3. The Points in the array are ordered according to ascending values of x.
 */
int InterpolatedCurve::value() {
  int v = constrain(_upstream->value(), MIN_VALUE, MAX_VALUE);
  if( _point_count < 2 ) { return v; }  // Error condition
  if( _points[0].x >= v ) { return _points[0].y; }
  for( unsigned int i = 1; i < _point_count; i++ ) {
    if( _points[i].x >= v ) {
      return map(v, _points[i-1].x, _points[i].x,
                    _points[i-1].y, _points[i].y);
    }
  }
  // This is an error condition that is not otherwise reported.
  // It won't happen as long as the points are set up correctly.
  return v;
}

void InterpolatedCurve::set_source( InputElement &upstream ) {
  _upstream = &upstream;
}

void InterpolatedCurve::set_points( Point points[], const unsigned int point_count ) {
  _point_count = point_count;
  _points = points;
}

unsigned int InterpolatedCurve::get_point_count() {
  return _point_count;
}

InterpolatedCurve::Point* InterpolatedCurve::get_points() {
  return _points;
}
