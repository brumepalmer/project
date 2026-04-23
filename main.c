#include "waveform.h"
#include <stdio.h>
#include <stdlib.h>

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
    FILE *fp;
    FILE *out_file;
    char line[1000];

    fp=fopen("power_quality_log.csv","r");
    if(fp==NULL) {
        printf("Cannot open file\n");
        return 1;

    }
    fgets(line,sizeof(line),fp);

    for(int i=0;i<1000;i++)
    {
        fscanf(fp,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &data[i].timestamp,
            &data[i].phase_a_voltage,
            &data[i].phase_b_voltage,
            &data[i].phase_c_voltage,
            &data[i].line_current,
            &data[i].frequency,
            &data[i].power_factor,
            &data[i].thd_percent);
    }

    fclose(fp);

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

    out_file = fopen("results.txt","w");
    if (out_file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fprintf(out_file,"Phase a rms = %lf\n",rmsA);
    fprintf(out_file,"Phase b rms = %lf\n",rmsB);
    fprintf(out_file,"Phase c rms = %lf\n",rmsC);

    fprintf(out_file,"Phase a Peak to Peak = %lf\n",peak_to_peakA);
    fprintf(out_file,"Phase B Peak to Peak = %lf\n",peak_to_peakB);
    fprintf(out_file,"Phase C Peak to Peak = %lf\n",peak_to_peakC);

    fprintf(out_file,"Phase a dc offset = %lf\n",dc_offsetA);
    fprintf(out_file,"Phase b dc offset = %lf\n",dc_offsetB);
    fprintf(out_file,"Phase c dc offset = %lf\n",dc_offsetC);

    fprintf(out_file,"Phase a clipped samples = %d\n",clipA);
    fprintf(out_file,"Phase b clipped samples = %d\n",clipB);
    fprintf(out_file,"Phase c clipped samples = %d\n",clipC);

    if (toleranceA ==1) {
        fprintf(out_file,"Phase a rms with Tolerance: Yes\n");
    }
    else {
        fprintf(out_file,"Phase a rms with Tolerance: No\n");
    }
    if (toleranceB ==1) {
        fprintf(out_file,"Phase b rms with Tolerance: Yes\n");
    }
    else {
        fprintf(out_file,"Phase b rms with Tolerance: No\n");
    }
    if (toleranceC ==1) {
        fprintf(out_file,"Phase c rms with Tolerance: Yes\n");
    }
    else {
        fprintf(out_file,"Phase c rms with Tolerance: No\n");
    }

    fclose(out_file);

    return 0;
}