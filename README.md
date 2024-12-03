# ZYNQ-NCO

**This project is for the Microarchitectures and softcores class**

This project uses the **[Numerically Controlled Oscillator (NCO)](https://github.com/AbeRodz/Numeric-Controlled-Oscillator)** made in VHDL as an IP Core. The NCO is used to generate sinewaves dynamically with Vivado's C SDK. Some applications are Frequency Shift Keying (FSK).

## Key Features

- **Waveform Generation**: Tye NCO supports sine, square, triangle, and sawtooth waveforms, other applications could be created with those waveforms.
- **LUT-based Sine Wave**: The sine wave is generated using a precomputed LUT with 1024 samples for high precision.
- **VHDL Implementation**: Code is structured to be synthesizable and suitable for FPGA and packaged as an IP Core.
- **Easy interaction from C**: Using C SDK the NCO can be managed from a microprocessor.

