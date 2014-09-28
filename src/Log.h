/**
 * Log.c
 *
 * Author: Jonathan Chapple
 * Contact: joncpl@gmail.com
 * Date: April 12, 2014
 *
 * Provides log-to-file functionality
 *
 */
#ifndef LOG_H
#define LOG_H


#define LOGFILE "resfix.log"

#define STRLEN 256
#define TIMEFORMAT  "%x %X"

typedef enum
{
	LOG_CRITICAL,
	LOG_ERROR,
	LOG_WARNING,
	LOG_ALERT,
	LOG_INFO,
	LOG_DEBUG
} LogType;

/**
 * Opens the log file to be written to
 */
int log_init();

/**
 * Closes the log file
 */
void log_close();

/**
 * Logs the given string to the log file
 * @param priority the priority of the message
 * @param s A formated (printf-style) string to log
 */
void Log(int priority, const char *s, ...);

#endif /* LOG_H */
