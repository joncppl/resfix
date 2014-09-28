/**
 * Exception.hpp
 *
 * Author: Jonathan Chapple
 * Contact: joncpl@gmail.com
 * Date: April 12, 2014
 *
 * Contains exception code
 *
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif


#include <string>

//Exceptions
typedef enum {
	EXCEPTION_URL,
	EXCEPTION_XML,
	EXCEPTION_SQL,
	EXCEPTION_FILE,
	EXCEPTION_TYPE,
	EXCEPTION_THREAD
} ExceptionType;

class Exception
{
private:
	/**
	 * The type of exception
	 */
	ExceptionType type;
	/**
	 * A message to go along with the exception
	 */
	std::string message;
	/**
	 * Optional c-style error if it was returned
	 */
	int iCerror;
public:
	Exception(ExceptionType type, std::string message)
	{
		this->type = type;
		this->message = message;
		this->iCerror = 0;
		Log(LOG_ERROR, "Exception: %s\n", message.c_str());
	}
	Exception(ExceptionType type, std::string message, int iError)
	{
		this->type = type;
		this->message = message;
		this->iCerror = iError;
		Log(LOG_ERROR, "Exception: %s with code\n", message.c_str(), iError);
	}

	std::string getMessage()
	{
		return message;
	}

	ExceptionType getType()
	{
		return type;
	}

	int getCerror()
	{
		return iCerror;
	}
};



#endif /* EXCEPTION_H */
