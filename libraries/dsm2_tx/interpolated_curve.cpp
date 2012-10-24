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

int InterpolatedCurve::value() {
  return 0;
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
