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

    int clipA=0;
    int clipB=0;
    int clipC=0;

    int toleranceA =0;
    int toleranceB =0;
    int toleranceC =0;

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

    dc_sumA=0;
    dc_sumB=0;
    dc_sumC=0;

    for(int i=0;i<1000;i++) {
        dc_sumA += data[i].phase_a_voltage;
        dc_sumB += data[i].phase_b_voltage;
        dc_sumC += data[i].phase_c_voltage;
    }

    dc_offsetA=dc_sumA/1000;
    dc_offsetB=dc_sumB/1000;
    dc_offsetC=dc_sumC/1000;

    clipA=0;
    clipB=0;
    clipC=0;

    for(int i=0;i<1000;i++) {
        if (data[i].phase_a_voltage >= 324.9 || data[i].phase_a_voltage <= -324.9)
        {
            clipA++;
        }
        if (data[i].phase_b_voltage >= 324.9 || data[i].phase_b_voltage <= -324.9)
        {
            clipB++;
        }
        if (data[i].phase_c_voltage >= 324.9 || data[i].phase_c_voltage <= -324.9) {
            clipC++;
        }
    }

    if (rmsA >= 207 && rmsA <= 253) {
        toleranceA=1;
    }
    if (rmsB >= 207 && rmsB <= 253) {
        toleranceB=1;
    }
    if (rmsC >= 207 && rmsC <= 253) {
        toleranceC=1;
    }

    printf("Phase a rms = %lf\n",rmsA);
    printf("Phase b rms = %lf\n",rmsB);
    printf("Phase c rms = %lf\n",rmsC);

    printf("Phase a Peak to Peak = %lf\n",peak_to_peakA);
    printf("Phase B Peak to Peak = %lf\n",peak_to_peakB);
    printf("Phase C Peak to Peak = %lf\n",peak_to_peakC);

    printf("Phase a dc offset = %lf\n",dc_offsetA);
    printf("Phase b dc offset = %lf\n",dc_offsetB);
    printf("Phase c dc offset = %lf\n",dc_offsetC);

    printf("Phase a clipped samples = %d\n",clipA);
    printf("Phase b clipped samples = %d\n",clipB);
    printf("Phase c clipped samples = %d\n",clipC);

    if (toleranceA ==1) {
        printf("Phase a rms with Tolerance: Yes\n");
    }
    else {
        printf("Phase a rms with Tolerance: No\n");
    }
    if (toleranceB ==1) {
        printf("Phase b rms with Tolerance: Yes\n");
    }
    else {
        printf("Phase b rms with Tolerance: No\n");
    }
    if (toleranceC ==1) {
        printf("Phase c rms with Tolerance: Yes\n");
    }

    return 0;
}
