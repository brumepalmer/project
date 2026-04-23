#ifndef WAVEFORM_H
#define WAVEFORM_H

typedef struct
{
    double timestamp;
    double phase_a_voltage;
    double phase_b_voltage;
    double phase_c_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

double compute_rms(const double values[], int size);
double compute_peak_to_peak(const double values[], int size);
double compute_dc_offset(const double values[], int size);
int count_clipped(const double values[], int size);
int check_clipped(const double values);

#endif
