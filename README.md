dsm2_tx
=======

dsm2_tx is an Arduino library that provides a simple API for controlling the RF
modules that may be found in many DSM2-compatible transmitters.  I think this
should be useful to anyone who wishes to develop their own custom control
hardware or otherwise wants to write their own transmitter logic.  I have also
begun work on some transmitter logic components (like input trims, expo curves,
etc).  I will keep that work here as well for the time being.

## Download and Install
To download this library using git:

```$ git clone git://github.com/IronSavior/dsm2_tx.git dsm2_tx```

 or

```$ git clone https://github.com/IronSavior/dsm2_tx.git dsm2_tx```

To install, copy libraries/dsm2_tx to your Arduino/libraries/ directory.

## Documentation

See the examples directory for example Arduino sketches.

## Why?

The reason I started this project is because I wanted to see if I could control
my model planes with a USB joystick or other commodity game controller.  I'm
not quite there yet, but I think I can do it.

### Acknowledgements

DSM2 and DSMX are trademarks or registered trademarks of Horizon Hobby, Inc.

### Copyrights

Original work is Copyright (C) 2012 Erik Elmore <erik@ironsavior.net>

### License
See LICENSE file for full text.

> This program is free software: you can redistribute it and/or modify
> it under the terms of the GNU General Public License as published by
> the Free Software Foundation, either version 3 of the License, or
> (at your option) any later version.
> 
> This program is distributed in the hope that it will be useful,
> but WITHOUT ANY WARRANTY; without even the implied warranty of
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
> GNU General Public License for more details.
> 
> You should have received a copy of the GNU General Public License
> along with this program. If not, see <http://www.gnu.org/licenses/>.
