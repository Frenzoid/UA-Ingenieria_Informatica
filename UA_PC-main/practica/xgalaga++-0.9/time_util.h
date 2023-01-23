#ifndef TIME_UTIL_H
#define TIME_UTIL_H

double CurrentMicroSecond();

// Sleep until 'interval_start_time' + 'interval' is CurrentMicroSecond().
// Return CurrentMicroSecond(). Do not sleep at all if 
// 'interval_start_time' + 'interval' >= CurrentMicroSecond().
double SleepTimeInterval(double interval_start_time, double interval);

#endif
