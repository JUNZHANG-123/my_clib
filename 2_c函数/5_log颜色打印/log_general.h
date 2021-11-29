#ifndef __LOG_GENERAL_H__
#define __LOG_GENERAL_H__
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LOG_NONE,       /*!< No log output */
    LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    LOG_INFO,       /*!< Information messages which describe normal flow of events */
    LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} log_level_t;

#define LOG_LOCAL_LEVEL LOG_DEBUG

extern void log_write(log_level_t level,
                   const char *tag,
                   const char *format, ...);
extern int log_timestamp(void);

#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V

#define LOG_FMT(x)      "[%s %s %d]: " x, __FILE__, __FUNCTION__, __LINE__

#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%u) %s: " format LOG_RESET_COLOR "\n"
				   
#define LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==LOG_ERROR )          { log_write(LOG_ERROR,      tag, LOG_FORMAT(E, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==LOG_WARN )      { log_write(LOG_WARN,       tag, LOG_FORMAT(W, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==LOG_DEBUG )     { log_write(LOG_DEBUG,      tag, LOG_FORMAT(D, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else if (level==LOG_VERBOSE )   { log_write(LOG_VERBOSE,    tag, LOG_FORMAT(V, format), log_timestamp(), tag, ##__VA_ARGS__); } \
        else                            { log_write(LOG_INFO,       tag, LOG_FORMAT(I, format), log_timestamp(), tag, ##__VA_ARGS__); } \
    } while(0)

#define LOG_LEVEL_LOCAL(level, tag, format, ...) do {               \
        if ( LOG_LOCAL_LEVEL >= level ) LOG_LEVEL(level, tag, format, ##__VA_ARGS__); \
    } while(0)
		
	
#define LOGE( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_ERROR,   tag, format, ##__VA_ARGS__)
#define LOGW( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_WARN,    tag, format, ##__VA_ARGS__)
#define LOGI( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_INFO,    tag, format, ##__VA_ARGS__)
#define LOGD( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_DEBUG,   tag, format, ##__VA_ARGS__)
#define LOGV( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_VERBOSE, tag, format, ##__VA_ARGS__)


#endif