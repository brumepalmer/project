#include "waveform.h"
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int main(){

    double phase_a_values[1000];
    double phase_b_values[1000];
    double phase_c_values[1000];

    double rmsA,rmsB,rmsC;
    double peak_to_peakA,peak_to_peakB,peak_to_peakC;
    double dc_offsetA,dc_offsetB,dc_offsetC;
    int clipA,clipB,clipC;
    int toleranceA,toleranceB,toleranceC;

    WaveformSample data[1000];

    if (read_csv_file("power_quality_log.csv",data,1000) == 1) {
        return 1;
    }

    for(int i=0;i<1000;i++) {
        phase_a_values[i] = data[i].phase_a_voltage;
        phase_b_values[i] = data[i].phase_b_voltage;
        phase_c_values[i] = data[i].phase_c_voltage;
    }

    rmsA= compute_rms(phase_a_values,1000);
    rmsB= compute_rms(phase_b_values,1000);
    rmsC= compute_rms(phase_c_values,1000);

    peak_to_peakA = compute_peak_to_peak(phase_a_values,1000);
    peak_to_peakB = compute_peak_to_peak(phase_b_values,1000);
    peak_to_peakC = compute_peak_to_peak(phase_c_values,1000);

    dc_offsetA= compute_dc_offset(phase_a_values,1000);
    dc_offsetB= compute_dc_offset(phase_b_values,1000);
    dc_offsetC= compute_dc_offset(phase_c_values,1000);

    clipA= count_clipped(phase_a_values,1000);
    clipB= count_clipped(phase_b_values,1000);
    clipC= count_clipped(phase_c_values,1000);

    toleranceA=check_clipped(rmsA);
    toleranceB=check_clipped(rmsB);
    toleranceC=check_clipped(rmsC);

   if (write_results_file("results.txt",
                           rmsA,rmsB,rmsC,
                           peak_to_peakA,peak_to_peakB,peak_to_peakC,
                           dc_offsetA,dc_offsetB,dc_offsetC,
                           clipA,clipB,clipC,
                           toleranceA,toleranceB,toleranceC) == 0) {
       return 1;
   }

    return 0;
}