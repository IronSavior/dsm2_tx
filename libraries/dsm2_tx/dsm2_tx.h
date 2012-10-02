/*
  DSM2_tx implements the serial communication protocol used for operating
  the RF modules that can be found in many DSM2-compatible transmitters.
  
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

// Channel values are 10-bits wide and unsigned, maximum value is 0x03FF
#define CHANNEL_MIN_VALUE  0
#define CHANNEL_MAX_VALUE  0x03FF

// The first byte of any frame is the command
#define CMD_NORMAL 0x18
#define CMD_BIND   0x98

/*
This defines the maximum number of channels for the purpose of sizing the transmission buffer.
It's safe to leave this at 8.  You set the actual number of channels to be transmitted during
run-time in the constructor. */
#define MAX_CHANNELS 8

/*
Additional Notes:  It is believed this value cannot be higher than 8 because it appears to be
used as a 3-bit channel array index on the wire.  It has not been observed by me to have ever
been higher than 6, but I speculate that it could indeed be more than 3-bits wide.  More testing
is required, and values higher than 6-8 may not be supported by all TX hardware. */

// This class will enforce a minimum interval (in milliseconds) between transmissions.
#define MIN_TX_INTERVAL 10

// First byte is the bind command
// Second byte is the model id
// last 12 bytes are magic numbers that signify a bind action
#define BIND_MAGIC {CMD_BIND, 0x00, 0x00, 0xAA, 0x05, 0xFF, 0x09, 0xFF, 0x0D, 0xFF, 0x13, 0x54, 0x14, 0xAA}

class DSM2_tx {
protected:
  union {
    struct {
      byte cmd;
      byte model_id;
      union {
        word value;
        struct {
          byte msb;
          byte lsb;
        };
      } channels[MAX_CHANNELS];
    };
    byte raw[sizeof(word)*MAX_CHANNELS + sizeof(byte)*2];
  } tx_buf;
  
  enum State {
    BIND_OK,
    BINDING,
    NORMAL
  };
  
  State state;
  unsigned long last_tx_time;
  void write_frame();

public:
  const unsigned int channel_count;
  
  // You're playing with fire if channels > MAX_CHANNELS
  DSM2_tx(unsigned int channels = MAX_CHANNELS) : state(BIND_OK), last_tx_time(0), channel_count(channels) {};
  
  void begin();
  void end();
  int set_channel( unsigned int channel, unsigned int value, unsigned int bound_max = CHANNEL_MAX_VALUE, unsigned int bound_min = CHANNEL_MIN_VALUE );
  int bind( void (*cb)(int state, byte model_id) = 0, byte model_id = 0,  unsigned int duration_ms = 10000, unsigned int interval_ms = 50);
  int send_frame( byte model_id = 0 );
  unsigned long get_last_tx_time();
};
