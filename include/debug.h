//-- debug.h -------------------------------------------
#include <stdio.h>
#include <time.h>
// format is a string like as "%d %s..."
#define DEBUG(format, ...) do {\
        time_t tm_time;\
        struct tm *st_time; \
        char buff[1024]; \
                time( &tm_time);\
                st_time = localtime( &tm_time);\
                strftime( buff, 1024, "DEBUG %Y-%m-%d %H:%M:%S", st_time);\
                fprintf(stderr, "%s:%s:%d:%s():" format "\n", buff,__FILE__, __LINE__, __func__, ##__VA_ARGS__);}while(0)
				
#define INFO(format, ...) do {\
	time_t tm_time;\
	struct tm *st_time; \
	char buff[1024]; \
	time( &tm_time);\
	st_time = localtime( &tm_time);\
	strftime( buff, 1024, "DEBUG %Y-%m-%d %H:%M:%S", st_time);\
	fprintf(stderr, "%s:%s:%d:%s():" format "\n", buff,__FILE__, __LINE__, __func__, ##__VA_ARGS__);}while(0)
	
#define WARN(format, ...) do {\
	time_t tm_time;\
	struct tm *st_time; \
	char buff[1024]; \
	time( &tm_time);\
	st_time = localtime( &tm_time);\
	strftime( buff, 1024, "DEBUG %Y-%m-%d %H:%M:%S", st_time);\
	fprintf(stderr, "%s:%s:%d:%s():" format "\n", buff,__FILE__, __LINE__, __func__, ##__VA_ARGS__);}while(0)
	
#define ERROR(format, ...) do {\
	time_t tm_time;\
	struct tm *st_time; \
	char buff[1024]; \
	time( &tm_time);\
	st_time = localtime( &tm_time);\
	strftime( buff, 1024, "DEBUG %Y-%m-%d %H:%M:%S", st_time);\
	fprintf(stderr, "%s:%s:%d:%s():" format "\n", buff,__FILE__, __LINE__, __func__, ##__VA_ARGS__);}while(0)
	
// struct timeval a, b, result
// CMP <, >, ==, ...

#define TIMER_CMP(a, b, CMP) \
	(((a)->tv_sec == (b)->tv_sec) ? \
	((a)->tv_usec CMP (b)->tv_usec) : \
	((a)->tv_sec CMP (b)->tv_sec))

#define TIMER_ADD(a, b, result) \
	do { \
		(result)->tv_sec = (a)->tv_sec + (b)->tv_sec; \
		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec; \
		if ((result)->tv_usec >= 1000000) \
		{ \
			++(result)->tv_sec; \
			(result)->tv_usec -= 1000000; \
		} \
	} while (0)
	
#define TIMER_SUB(a, b, result) \
	do { \
		(result)->tv_sec = (a)->tv_sec - (b)->tv_sec; \
		(result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
		if ((result)->tv_usec < 0) { \
			--(result)->tv_sec; \
			(result)->tv_usec += 1000000; \
		} \
	} while (0)	
