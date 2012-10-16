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

class Trim : public InputElement {
protected:
  int _offset;
  unsigned int _margin;
  InputElement *_upstream;
public:
  Trim() : _offset(0), _margin(0), _upstream(NULL) {};
  void set_source( InputElement &upstream );
  void set_margin( unsigned int margin );
  void set_offset( int offset );
  int value();
};
