#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define PERIOD 10000000
#define PULSE_BASE 1000
#define SLEEP 10000
#define PI 3.14159265358979323846
#define DEBUG 0

int main()
{
  timespec ts;
  int led = open(
  	"/sys/devices/platform/leds-gpio/leds/beaglebone::usr3/brightness", O_WRONLY);

  while (true) {
  	clock_gettime(CLOCK_REALTIME, &ts);
  	unsigned long long nsec = ts.tv_nsec;
	unsigned long long mod = nsec % PERIOD;
	long double pct = mod / (long double)PERIOD;
	long double radians = pct * 2 * PI;
	long double sine = sinl(radians) + 1.0;
	if (DEBUG) {
		int stars = sine * 40;
		int i = 0;
		while (i < stars) {
			printf("*");
			i++;
		}
		printf("\n");
	}
	long on_nsec = (long)(sine * PULSE_BASE);
	write(led, "1", 1);
	ts.tv_sec = 0;
	ts.tv_nsec = on_nsec;
	nanosleep(&ts, NULL);
	write(led, "0", 1);
	ts.tv_nsec = SLEEP;
	nanosleep(&ts, NULL);
  }
}
