#include "time_util.h"
#include <sys/time.h>
#include <sys/select.h>


double CurrentMicroSecond()
{
	timeval now;
	gettimeofday(&now, 0);
	return now.tv_sec + now.tv_usec / 1000000.0;
}


double SleepTimeInterval(double interval_start_time, double interval)
{
	const double remaining (interval_start_time + interval - CurrentMicroSecond());
	if (remaining > 0) {
		timeval timeout;
		timeout.tv_sec  = remaining;
		timeout.tv_usec = (remaining - timeout.tv_sec) * 1000000;
		select(0, 0, 0, 0, &timeout);
	}
	return CurrentMicroSecond();
}
