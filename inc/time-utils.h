#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_

#include <stdint.h>
#include <time.h>

#define nSEC_IN_SEC 1000000000ULL

#define msec_to_nsec(t) ((t) * 1000000ULL)

static inline uint64_t timespec_to_ns(struct timespec* ts)
{
	return (uint64_t)ts->tv_sec * nSEC_IN_SEC + (uint64_t)ts->tv_nsec;
}

static inline struct timespec ns_to_timespec(uint64_t ns)
{
	struct timespec ts;
	ts.tv_nsec = ns % nSEC_IN_SEC;
	ts.tv_sec = ns / nSEC_IN_SEC;
	return ts;
}

static inline void add_to_timespec(struct timespec* ts, uint64_t addition)
{
	*ts = ns_to_timespec(timespec_to_ns(ts) + addition);
}

static inline uint64_t gettime_ns(clockid_t clk_id)
{
	struct timespec ts = { 0 };
	clock_gettime(clk_id, &ts);
	return timespec_to_ns(&ts);
}

static inline uint64_t gettime_us(clockid_t clk_id)
{
	return gettime_ns(clk_id) / 1000ULL;
}

static inline uint64_t gettime_ms(clockid_t clk_id)
{
	return gettime_us(clk_id) / 1000ULL;
}

static inline uint64_t gettime_s(clockid_t clk_id)
{
	return gettime_ms(clk_id) / 1000ULL;
}

#endif /* TIME_UTILS_H_ */
