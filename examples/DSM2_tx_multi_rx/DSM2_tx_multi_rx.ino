/*
  Demonstrates control of multiple receivers with a single transmitter module.
  
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
#include "dsm2_tx.h"

#define BIND0_SWITCH  2
#define BIND0_LED     3
#define BIND1_SWITCH  4
#define BIND1_LED     5
#define ERROR_LED     6

DSM2_tx tx(6);

/*
 * This is the callback for the bind process--it controls the UI during the bind process
 * Bind completed:  state = 0
 * Bind in progress:  state = 1
 * Bind error:  state = 2
 */
void bind_cb( int state, byte model_id ) {
  if( state == 1 ) {
    digitalWrite(model_id == 0 ? BIND0_LED : BIND1_LED, HIGH);
  }
  else {
    digitalWrite(model_id == 0 ? BIND0_LED : BIND1_LED, LOW);
  }
  if( state == 2 ) {
    digitalWrite(ERROR_LED, HIGH);
  }
}

#define MAX_VAL 200
int value0 = 0;
int delta0 = 5;
int value1 = 100;
int delta1 = 5;
int next_step( int *value, int *delta ) {
  *value += *delta;
  if( *value > MAX_VAL ){
    *delta *= -1;
    *value = MAX_VAL;
  }
  else if( *value < 0 ){
    *value = 0;
    *delta *= -1;
  }
  return *value;
}

void setup() {
  pinMode(BIND0_SWITCH, INPUT);
  pinMode(BIND1_SWITCH, INPUT);
  pinMode(BIND0_LED, OUTPUT);
  pinMode(BIND1_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);

  tx.begin();
  
  // Only do one bind per boot-up; switch 0 trumps switch 1
  // Donor radio module must be powered off to re-enter bind mode. 
  // (This must be done manually)
  if( digitalRead(BIND0_SWITCH) == HIGH ) {
    tx.bind(bind_cb, 0);
  }
  else if( digitalRead(BIND1_SWITCH) == HIGH ) {
    tx.bind(bind_cb, 1);
  }
}

void loop() {
  int value = next_step(&value0, &delta0);
  for( byte i = 0; i < tx.channel_count; i++ ){
    tx.set_channel(i, value, MAX_VAL);
  }
  tx.send_frame(0);
  
  value = next_step(&value1, &delta1);
  for( byte i = 0; i < tx.channel_count; i++ ){
    // Send a slightly different command to channels on the second receiver.
    tx.set_channel(i, value, MAX_VAL);
  }
  tx.send_frame(1);
}

