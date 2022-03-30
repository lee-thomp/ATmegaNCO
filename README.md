### ATmegaNCO ###

This is an attempt to create a synthesiser oscillator using an ATmega328p (or other AVR) microcontroller.
Development work is mainly targetting the Arduino Nano platform, but a bare chip should work with similar clocking and I/O.

#### Simple Saw ####

This branch of the project implements a single sawtooth oscillator that samples a voltage on a user selectable pin (see `ADC_CHANNEL_MAGIC` in `OscillatorConfig.h`), and outputs a sawtooth waveform on pin D6.
The oscillator should span the note range C0-E6 with four discrete steps per semitone, though due to resolution issues some detuning may occur.

This (branch of the) project uses [avr_debug](https://github.com/jdolinay/avr_debug) currently, but this could be removed entirely seeing as functionality is proven.
