#include <math.h>
#include "waveform.h"

double compute_rms(const double values[], int size) {
    int i;
    double sum;

    sum=0;

    for(i=0;i<size;i++) {
        sum += values[i] * values[i];
    }
    return sqrt(sum/size);
}

double compute_peak_to_peak(const double values[], int size) {
    int i;
    double max, min;

    max=values[0];
    min=values[0];

    for(i=1;i<size;i++) {
        if(values[i] > max)
            max=values[i];
        if(values[i] < min)
            min=values[i];
    }
    return max-min;
}

double compute_dc_offset(const double values[], int size) {
    int i;
    double sum;
    sum=0;

    for(i=0;i<size;i++) {
        sum += values[i];
    }

    return sum/size;
}

int count_clipped(const double values[], int size) {
    int i;
    int count=0;
    count =0;
    for(i=0;i<size;i++) {
        if (values[i] >=324.9|| values[i] <=-324.9) {
            count++;
        }
    }
    return count;
}

int check_clipped(const double rms) {
    if (rms >= 207 && rms <= 253) {
        return 1;
    }
    return 0;
}

double compute_variance(double values[], int size)
{
    int i;
    double mean;
    double sum;

    mean = compute_dc_offset(values, size);
    sum = 0;

    for (i = 0; i < size; i++)
    {
        sum += (values[i] - mean) * (values[i] - mean);
    }

    return sum / size;
}

double compute_standard_deviation(double values[], int size)
{
    return sqrt(compute_variance(values, size));
}