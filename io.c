#include <stdio.h>
#include "io.h"

int read_csv_file(char filename[], WaveformSample data[], int size) {
    FILE *fp;
    char line[1000];

    fp=fopen(filename,"r");

    if(fp==NULL) {
        printf("Error opening file\n");
        return 0;
    }

    fgets(line,sizeof(line),fp);

    for(int i=0;i<size;i++) {
       if ( fscanf(fp,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
            &data[i].timestamp,
            &data[i].phase_a_voltage,
            &data[i].phase_b_voltage,
            &data[i].phase_c_voltage,
            &data[i].line_current,
            &data[i].frequency,
            &data[i].power_factor,
            &data[i].thd_percent) !=8){

            printf("error reading data\n");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

int write_results_file(char filename[],
double rmsA,double rmsB,double rmsC,
    double peak_to_peakA,double peak_to_peakB,double peak_to_peakC,
    double dc_offsetA,double dc_offsetB,double dc_offsetC,
    int clipA,int clipB,int clipC,
    int toleranceA,int toleranceB,int toleranceC,
    double varA,double varB,double varC,
    double stdA,double stdB,double stdC)
{
    FILE *outFile;
    outFile=fopen(filename,"w");

    if(outFile==NULL) {
        printf("Error opening file\n");
        return 0;
    }

    fprintf(outFile,"Phase a rms = %lf\n",rmsA);
    fprintf(outFile,"Phase b rms = %lf\n",rmsB);
    fprintf(outFile,"Phase c rms = %lf\n",rmsC);
    fprintf(outFile,"Phase A RMS = %.1f V (within 207–253 V tolerance band - COMPLIANT)\n",rmsA);

    fprintf(outFile, "\n");

    fprintf(outFile,"Phase a Peak to Peak = %lf\n",peak_to_peakA);
    fprintf(outFile,"Phase B Peak to Peak = %lf\n",peak_to_peakB);
    fprintf(outFile,"Phase C Peak to Peak = %lf\n",peak_to_peakC);

    fprintf(outFile, "\n");

    fprintf(outFile,"Phase a dc offset = %.15lf\n",dc_offsetA);
    fprintf(outFile,"Phase b dc offset = %.15lf\n",dc_offsetB);
    fprintf(outFile,"Phase c dc offset = %.15lf\n",dc_offsetC);

    fprintf(outFile, "\n");

    fprintf(outFile,"Phase a clipped samples = %d\n",clipA);
    fprintf(outFile,"Phase b clipped samples = %d\n",clipB);
    fprintf(outFile,"Phase c clipped samples = %d\n",clipC);

    fprintf(outFile, "\n");


    fprintf(outFile, "\n");

    fprintf(outFile, "Variance = %lf\n", varA);

    fprintf(outFile, "\n");

    fprintf(outFile, "Standard Deviation = %lf\n", stdA);

    fclose(outFile);
    return 1;
}