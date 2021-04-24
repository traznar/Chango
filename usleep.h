#pragma once

// Sets resolution of timers used by Sleep() and SetWaitableTimer() to most accurate and lowest values possible supported by system.
// Same as timeBeginPeriod() but accepts microsecond precision for requested resolution.
unsigned long setHighestTimerResolution(unsigned long timer_res_us);

// Suspends the current thread in sleep for time period, in microseconds.
void usleep(__int64 usec);