#include "log_general.h"


void log_write(log_level_t level,
                   const char *tag,
                   const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
}

int log_timestamp(void)
{
    return 0;
}
