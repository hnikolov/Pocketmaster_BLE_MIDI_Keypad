#ifndef _MIDI_COMMANDS_H_
#define _MIDI_COMMANDS_H_

#include <BLEMidi.h>

// Send BLE MIDI CC --------------------------------------------------------------------------------------
void bank_dec()      { BLEMidiClient.controlChange(1, 22,  0); } // Preset number reduced by 10
void bank_inc()      { BLEMidiClient.controlChange(1, 23,  0); } // Preset number increased by 10
void preset_dec()    { BLEMidiClient.controlChange(1, 24,  0); } // Preset number reduced by 1
void preset_inc()    { BLEMidiClient.controlChange(1, 25,  0); } // Preset number increased by 1
void nr_off()        { BLEMidiClient.controlChange(1, 43, 63); } // Noise Reduction module OFF
void nr_on()         { BLEMidiClient.controlChange(1, 43, 64); } // Noise Reduction module ON
void fx1_off()       { BLEMidiClient.controlChange(1, 44, 63); } // FX1 module OFF
void fx1_on()        { BLEMidiClient.controlChange(1, 44, 64); } // FX1 module ON
void drv_off()       { BLEMidiClient.controlChange(1, 45, 63); } // Drive module OFF
void drv_on()        { BLEMidiClient.controlChange(1, 45, 64); } // Drive module ON
void amp_off()       { BLEMidiClient.controlChange(1, 46, 63); } // Amplifier module OFF
void amp_on()        { BLEMidiClient.controlChange(1, 46, 64); } // Amplifier module ON
void ir_off()        { BLEMidiClient.controlChange(1, 47, 63); } // Cab Impulse Response module OFF
void ir_on()         { BLEMidiClient.controlChange(1, 47, 64); } // Cab Impulse Response module ON
void eq_off()        { BLEMidiClient.controlChange(1, 48, 63); } // EQ module OFF
void eq_on()         { BLEMidiClient.controlChange(1, 48, 64); } // EQ module ON
void fx2_off()       { BLEMidiClient.controlChange(1, 49, 63); } // FX2 module OFF
void fx2_on()        { BLEMidiClient.controlChange(1, 49, 64); } // FX2 module ON
void dly_off()       { BLEMidiClient.controlChange(1, 50, 63); } // Delay module OFF
void dly_on()        { BLEMidiClient.controlChange(1, 50, 64); } // Delay module ON
void rvb_off()       { BLEMidiClient.controlChange(1, 51, 63); } // Reverb module OFF
void rvb_on()        { BLEMidiClient.controlChange(1, 51, 64); } // Reverb module ON
void tuner_off()     { BLEMidiClient.controlChange(1, 58, 63); } // Tuner module OFF
void tuner_on()      { BLEMidiClient.controlChange(1, 58, 64); } // Tuner Reduction module ON
void looper_off()    { BLEMidiClient.controlChange(1, 59, 63); } // Looper module OFF
void looper_on()     { BLEMidiClient.controlChange(1, 59, 64); } // Looper module ON
void looper_rec()    { BLEMidiClient.controlChange(1, 60,  0); } // Looper record start
void looper_stop()   { BLEMidiClient.controlChange(1, 62, 63); } // Looper stop
void looper_play()   { BLEMidiClient.controlChange(1, 62, 64); } // Looper play
void looper_del()    { BLEMidiClient.controlChange(1, 64,  0); } // Delete loop
void looper_post()   { BLEMidiClient.controlChange(1, 67, 63); } // Looper placement post
void looper_pre()    { BLEMidiClient.controlChange(1, 67, 64); } // Looper placement pre
void drum_menu_off() { BLEMidiClient.controlChange(1, 92, 63); } // Drum/Metronome menu OFF
void drum_menu_on()  { BLEMidiClient.controlChange(1, 92, 64); } // Drum/Metronome menu ON
void drum_stop()     { BLEMidiClient.controlChange(1, 93, 63); } // Drum/Metronome stop
void drum_play()     { BLEMidiClient.controlChange(1, 93, 64); } // Drum/Metronome play

// Functions with arguments
void preset_sel(uint8_t preset)      { BLEMidiClient.controlChange(1,  1, preset); } // Preset select (1-50: P01-P50; 51-100: F01-F50)
void master_vol(uint8_t volume)      { BLEMidiClient.controlChange(1,  6, volume); } // Master volume (0-100)
void preset_vol(uint8_t volume)      { BLEMidiClient.controlChange(1,  7, volume); } // Preset volume (0-100)
void looper_rec_vol(uint8_t volume)  { BLEMidiClient.controlChange(1, 65, volume); } // Looper recording volume (0-100)
void looper_play_vol(uint8_t volume) { BLEMidiClient.controlChange(1, 66, volume); } // Looper playback volume (0-100)
void drum_rhythm(uint8_t rhythm)     { BLEMidiClient.controlChange(1, 94, rhythm); } // Drum/Metronome rhythm (0-9)
void drum_volume(uint8_t volume)     { BLEMidiClient.controlChange(1, 95, volume); } // Drum/Metronome volume (0-100)

bool t_drm = false;
bool t_lpr = false;
void looper_tgl()
{
  if( t_lpr == true ) { looper_off(); }
  else                { looper_on(); t_drm = false; }
  t_lpr = !t_lpr;
}

bool p_lpr = false;
void looper_r_p()
{
  if( p_lpr == true ) { looper_play(); }
  else                { looper_rec(); }
  p_lpr = !p_lpr;
}

//bool t_drm = false;
void drum_tgl()
{
  if( t_drm == true ) { drum_menu_off(); }
  else                { drum_menu_on(); t_lpr = false; }
  t_drm = !t_drm;
}

bool p_drm = false;
void drum_p_s()
{
  if( p_drm == true ) { drum_play(); }
  else                { drum_stop(); }
  p_drm = !p_drm;
}

int8_t rhythm = 3; // 4/4
void rhythm_next()
{
  rhythm++;
  if( rhythm == 10 ) { rhythm = 0; }
  drum_rhythm(rhythm);
}

void rhythm_prev()
{
  rhythm--;
  if( rhythm == -1 ) { rhythm = 9; }
  drum_rhythm(rhythm);
}

// Toggle modules -------------------------------
bool t_rvb = false;
void reverb_tgl()
{
  if( t_rvb == true ) { rvb_off(); }
  else                { rvb_on();  }
  t_rvb = !t_rvb;
}

bool t_amp = false;
void amp_tgl()
{
  if( t_amp == true ) { amp_off(); }
  else                { amp_on();  }
  t_amp = !t_amp;
}

bool t_ir = false;
void ir_tgl()
{
  if( t_ir == true ) { ir_off(); }
  else               { ir_on();  }
  t_ir = !t_ir;
}

bool t_dly = false;
void delay_tgl()
{
  if( t_dly == true ) { dly_off(); }
  else                { dly_on();  }
  t_dly = !t_dly;
}

bool t_drv = false;
void drive_tgl()
{
  if( t_drv == true ) { drv_off(); }
  else                { drv_on();  }
  t_drv = !t_drv;
}

bool t_fx1 = false;
void fx1_tgl()
{
  if( t_fx1 == true ) { fx1_off(); }
  else                { fx1_on();  }
  t_fx1 = !t_fx1;
}

bool t_fx2 = false;
void fx2_tgl()
{
  if( t_fx2 == true ) { fx2_off(); }
  else                { fx2_on();  }
  t_fx2 = !t_fx2;
}

bool t_eq = false;
void eq_tgl()
{
  if( t_eq == true ) { eq_off(); }
  else               { eq_on();  }
  t_eq = !t_eq;
}

bool t_nr = false;
void nr_tgl()
{
  if( t_nr == true ) { nr_off(); }
  else               { nr_on();  }
  t_nr = !t_nr;
}

int8_t vol_drm = 80;
int8_t vol_lpr = 80;
int8_t vol_mst = 30;
void vol_upd(int8_t val)
{
  if( t_drm == true )
  {
    vol_drm += val;
    if( vol_drm >= 100 ) { vol_drm = 100; }
    if( vol_drm <=   0 ) { vol_drm =   0; }
    drum_volume(vol_drm); 
  }
  else if( t_lpr == true )
  {
    vol_lpr += val;
    if( vol_lpr >= 100 ) { vol_lpr = 100; }
    if( vol_lpr <=   0 ) { vol_lpr =   0; }
    looper_play_vol(vol_lpr);
  }
  else
  {
    vol_mst += val;
    if( vol_mst >= 100 ) { vol_mst = 100; }
    if( vol_mst <=   0 ) { vol_mst =   0; }
    master_vol(vol_mst);
  }
}

// Example of array of functions and the respective calls
// void(*midi_commands[]) (void) = { bank_dec, bank_inc };
// midi_commands[1]();

#endif // _MIDI_COMMANDS_H_
