#ifndef IO_H
#define IO_H

#include "waveform.h"

int read_csv_file(char filename[], WaveformSample data[], int size);
int write_results_file(char filename[],  double rmsA,double rmsB,double rmsC,
    double peak_to_peakA,double peak_to_peakB,double peak_to_peakC,
    double dc_offsetA,double dc_offsetB,double dc_offsetC,
    int clipA,int clipB,int clipC,
    int toleranceA,int toleranceB,int toleranceC);

#endif
