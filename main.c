#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(){
    double sumA=0;
    double rmsA=0;
    double sumB=0;
    double rmsB=0;
    double sumC=0;
    double rmsC=0;

    double maxA=0;
    double maxB=0;
    double maxC=0;
    double minA=0;
    double minB=0;
    double minC=0;

    double peak_to_peakA;
    double peak_to_peakB;
    double peak_to_peakC;

    double dc_sumA;
    double dc_sumB;
    double dc_sumC;
    double dc_offsetA;
    double dc_offsetB;
    double dc_offsetC;


 WaveformSample data[1000];
    FILE *fp;
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

    sumA=0;
    sumB=0;
    sumC=0;

    for(int i=0;i<1000;i++) {
        sumA=sumA+data[i].phase_a_voltage*data[i].phase_a_voltage;
        sumB=sumB+data[i].phase_b_voltage*data[i].phase_b_voltage;
        sumC=sumC+data[i].phase_c_voltage*data[i].phase_c_voltage;
    }

    rmsA=sqrt(sumA/1000);
    rmsB=sqrt(sumB/1000);
    rmsC=sqrt(sumC/1000);

    maxA=data[0].phase_a_voltage;
    maxB=data[0].phase_b_voltage;
    maxC=data[0].phase_c_voltage;
    minA=data[0].phase_a_voltage;
    minB=data[0].phase_b_voltage;
    minC=data[0].phase_c_voltage;

    for (int i = 0; i < 1000; i++) {
        if (data[i].timestamp < maxA) {
            maxA=data[i].phase_a_voltage;
        }
        if (data[i].timestamp > maxB) {
            maxB=data[i].phase_b_voltage;
        }
        if (data[i].timestamp < minA) {
            minA=data[i].phase_a_voltage;
        }
        if (data[i].timestamp > minB) {
            minB=data[i].phase_b_voltage;
        }
        if (data[i].timestamp < maxC) {
            maxC=data[i].phase_c_voltage;
        }
        if (data[i].timestamp > maxC) {
            maxC=data[i].phase_c_voltage;
        }
    }

    peak_to_peakA=maxA-minA;
    peak_to_peakB=maxB-minB;
    peak_to_peakC=maxC-minC;


    printf("Phase a rms = %lf\n",rmsA);
    printf("Phase b rms = %lf\n",rmsB);
    printf("Phase c rms = %lf\n",rmsC);

    printf("Phase a Peak to Peak = %lf\n",peak_to_peakA);
    printf("Phase B Peak to Peak = %lf\n",peak_to_peakB);
    printf("Phase C Peak to Peak = %lf\n",peak_to_peakC);

    return 0;
}
