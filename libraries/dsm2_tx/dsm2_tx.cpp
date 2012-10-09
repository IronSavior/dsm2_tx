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

#include <cstring>
#include "dsm2_tx.h"

void DSM2_tx::begin() {
  Serial.begin(125000);
}

void DSM2_tx::end() {
  Serial.end();
}

// Channel index is zero-based
int DSM2_tx::set_channel( unsigned int channel, unsigned int value, unsigned int bound_max, unsigned int bound_min ){
  if( state == BINDING ) return 1;
  if( channel >= channel_count ) return 1;
  word v = channel << 10 | map(value, bound_min, bound_max, CHANNEL_MIN_VALUE, CHANNEL_MAX_VALUE);
  tx_buf.channels[channel].lsb = lowByte(v);
  tx_buf.channels[channel].msb = highByte(v);
  return 0;
}

/*
 * The optional callback (cb) will be called repeatedly during binding.  This is to enable the caller to handle
 * any UI concerns (visual/audio indicators, etc).  The callback is blocking, so it should not take too much
 * time or call delay().
 *
 * The integer parameter to the callback indicates the state of the binding process:
 * 0 indicates binding is completed
 * 1 indicates binding is in progress
 * 2 indicates an error condition (binding is not available)
 *
 * The byte parameter to the callback indicates the model match ID.
 * 
 * The return value is 0 if successful or 1 if binding is not available.
 */
int DSM2_tx::bind( void (*cb)(int,byte), byte model_id,  unsigned int duration_ms, unsigned int interval_ms ){
  if( state != BIND_OK ) {
    if( cb ) (*cb)(2, model_id);
    return 1;
  }
  state = BINDING;
  
  byte bind_buf[sizeof(tx_buf)] = BIND_MAGIC;
  memcpy(&tx_buf, &bind_buf, sizeof(tx_buf));
  tx_buf.model_id = model_id;
  
  unsigned long timeout = millis() + duration_ms;
  do {
    write_frame();
    if( cb ) (*cb)(1, model_id);
    // Don't call delay() with value < 1 or a value significantly higher than interval_ms
    delay(constrain(millis() - (last_tx_time + interval_ms), 1, interval_ms + 1));
  } while( timeout > millis() );
  
  for( unsigned int i = 0; i < channel_count; i++ ) {
    set_channel(i, 0);
  }
  state = BIND_OK;
  
  if( cb ) (*cb)(0, model_id);
  return 0;
}

int DSM2_tx::send_frame( byte model_id ){
  if( state == BINDING ) {
    return 1;
  }
  state = NORMAL;
  tx_buf.model_id = model_id;
  tx_buf.cmd = CMD_NORMAL;
  write_frame();
  return 0;
}

void DSM2_tx::write_frame() {
  unsigned long now = millis();
  unsigned long elapsed = now - last_tx_time;
  if( elapsed < MIN_TX_INTERVAL ) {
    delay(MIN_TX_INTERVAL - elapsed + 1);
  }
  last_tx_time = millis();
  Serial.write(tx_buf.raw, sizeof(tx_buf.cmd) + sizeof(tx_buf.model_id) + sizeof(word) * channel_count);
}

unsigned long DSM2_tx::get_last_tx_time() {
  return last_tx_time;
}
