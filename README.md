# Simple Digital Filter

This project implements a simple first-order low-pass digital filter in C++ that processes audio in real-time. The filter can be adjusted in real-time through the terminal while playing white noise.

## Features

- First-order low-pass filter implementation
- Real-time cutoff frequency adjustment through terminal input
- White noise generation
- Real-time audio playback using PortAudio
- Thread-safe filter parameter updates

## Dependencies

- PortAudio (for audio I/O)
- pkg-config (for finding PortAudio)

## Installation

1. Install dependencies using Homebrew:
```bash
brew install portaudio pkg-config
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Generate build files:
```bash
cmake ..
```

4. Build the project:
```bash
make
```

## Running the Program

After building, run the program:
```bash
./digital_filter
```

The program will:
1. Start playing white noise through your speakers
2. Allow you to adjust the cutoff frequency in real-time by entering new values in the terminal
3. Enter 0 to quit the program

Example usage:
```
Enter new cutoff frequency (Hz) or 0 to quit: 200
Cutoff frequency set to 200 Hz
Enter new cutoff frequency (Hz) or 0 to quit: 500
Cutoff frequency set to 500 Hz
Enter new cutoff frequency (Hz) or 0 to quit: 0
```

## Filter Implementation

The filter implements a first-order low-pass filter using the following equation:
```
y[n] = alpha * x[n] + (1 - alpha) * y[n-1]
```

Where:
- `alpha` is the filter coefficient calculated from the cutoff frequency
- `x[n]` is the input sample (white noise)
- `y[n]` is the output sample
- `y[n-1]` is the previous output sample

## Real-time Adjustment

The filter's cutoff frequency can be adjusted at any time by entering a new value in the terminal. The filter coefficients are automatically recalculated when the cutoff frequency changes, and the changes take effect immediately on the audio output.

## Technical Details

- Sample rate: 44.1 kHz
- Audio format: 32-bit floating point
- Output: Stereo
- Buffer size: 256 samples
- Thread-safe parameter updates using mutex 