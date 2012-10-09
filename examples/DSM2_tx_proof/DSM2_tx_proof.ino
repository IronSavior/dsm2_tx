/*
  Demonstrates basic usage of DSM2_tx class
  
  Copyright (C) 2012  Erik Elmore <erik@ironsavior.net>

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
#include "Arduino.h"
#include "dsm2_tx.h"

#define BIND_SWITCH  2
#define BIND_LED     3
#define ERROR_LED    5

DSM2_tx tx(6);

/*
 * This is the callback for the bind process--it controls the UI during the bind process
 * Bind completed:  state = 0
 * Bind in progress:  state = 1
 * Bind error:  state = 2
 */
void bind_cb( int state, byte model_id ) {
  if( state == 1 ) {
    digitalWrite(BIND_LED, HIGH);
  }
  else {
    digitalWrite(BIND_LED, LOW);
  }
  if( state == 2 ) {
    digitalWrite(ERROR_LED, HIGH);
  }
}

#define MAX_VAL 200
int current_value = 0;
int delta = 5;
int next_step() {
  current_value += delta;
  if( current_value > MAX_VAL ){
    delta *= -1;
    current_value = MAX_VAL;
  }
  else if ( current_value < 0 ){
    current_value = 0;
    delta *= -1;
  }
  return current_value;
}

void setup() {
  pinMode(BIND_SWITCH, INPUT);
  pinMode(BIND_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);

  tx.begin();
  
  if( digitalRead(BIND_SWITCH) == HIGH ) {
    tx.bind(bind_cb);
  }
}

void loop() {
  int current_step = next_step();
  for( byte i = 0; i < tx.channel_count; i++ ){
    tx.set_channel(i, current_step, MAX_VAL);
  }
  tx.send_frame();
}

