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

#pragma once
#include "input_element.h"
#include <cstddef>

class InterpolatedCurve : public InputElement {
public:
  struct Point { int x, y; };
protected:
  Point *_points;
  unsigned int _point_count;
  InputElement *_upstream;
public:
  InterpolatedCurve() : _points(NULL), _point_count(0), _upstream(NULL) {};
  InterpolatedCurve( Point* points, const unsigned int point_count ) : _points(points), _point_count(point_count), _upstream(NULL) {};
  void set_source( InputElement &upstream );
  void set_points( Point points[], const unsigned int point_count );
  Point* get_points();
  unsigned int get_point_count();
  int value();
};
