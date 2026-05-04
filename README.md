# Power Quality Waveform Analyser

## Overview
This program reads power quality data from a CSV file and analyses waveforms.

It calculates:
- RMS voltage
- Peak-to-peak voltage
- DC offset
- Clipping detection
- Tolerance compliance
- Variance and standard deviation

Results are written to a text file (`results.txt`)

## How to Run

1. Place `power_quality_log.csv` in:
   cmake-build-debug/

2. Build the project in CLion.

3. Run the program.

4. Open `results.txt` to view results.

## Program Structure

- `main.c`  
  Controls program flow

- `waveform.c / waveform.h`  
  Contains all calculation functions

- `io.c / io.h`  
  Handles file reading and writing

## Key Features

- Modular design using multiple source files
- Structured data using `struct`
- File input/output using `fopen`, `fscanf`, `fprintf`
- Error handling for file reading
- Clean formatted output with units

## Example Output
Phase A RMS = 229.8 V

Phase A Peak to Peak = 650.0 V

Phase A DC Offset = -0.000000000000000 V

Variance = 52812.5 V^2

Standard Deviation = 229.8 V

## Author
Oghenebrume Palmer-Ikuku
25057464

## Notes
This project was developed as part of coursework on waveform analysis and C programming.