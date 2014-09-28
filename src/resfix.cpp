#include <iostream>
#include <cstdlib>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
extern "C"
{
	#include "Log.h"
}
#include "Exception.hpp"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#define sleep(x) Sleep(x)
#endif

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t writeFunction(void *ptr, size_t size, size_t nmemb, char *userp)
{
	  size_t realsize = size * nmemb;
	  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
	  if(mem->memory == NULL) {
	    /* out of memory! */
	    Log(LOG_ERROR, "not enough memory (realloc returned NULL)\n");
	    return 0;
	  }

	  memcpy(&(mem->memory[mem->size]), ptr, realsize);
	  mem->size += realsize;
	  mem->memory[mem->size] = 0;

	  return realsize;
}

std::string httpGetBasicAuth(std::string sUrl, std::string sUsername, std::string sPassword, void *pData)
{
	CURL *curl;
	struct MemoryStruct msChunk;
	std::string sRet;
	int iError;
	//Initiate cURL
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl)
	{
		Log(LOG_ERROR, "Failed to initiate curl. The request will not be completed.\n");
		throw Exception(EXCEPTION_URL, "failed to initiate curl");
	}
	msChunk.memory = (char *)malloc(1);
	msChunk.size = 0;

	curl_easy_setopt(curl, CURLOPT_URL, sUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
	if ((0 != sUsername.compare("")) && (0 != sPassword.compare("")))
	{
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_easy_setopt(curl, CURLOPT_USERNAME, sUsername.c_str());
		curl_easy_setopt(curl, CURLOPT_PASSWORD, sPassword.c_str());
	}
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&msChunk);

	if (pData)
	{
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, pData);
	}

	iError = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (!iError)
	{
		sRet = std::string(msChunk.memory);
	}
	else
	{
		Log(LOG_ERROR, "Curl failed with error %d.\n", iError);
		throw Exception(EXCEPTION_URL, "curl perform failed", iError);
	}
	free(msChunk.memory);
	return sRet;
}


int main()
{
	log_init();
	Log(LOG_INFO, "Starting in 5 seconds.\n");
	std::cout << "Starting in 5 seconds.\n";
	sleep(5000);
	Log(LOG_INFO, "Waiting until you are in the penalty box.\n"); 
	std::cout << "Waiting until you are in the penalty box.\n";
	
	while (1)
	{
		std::string resNetData;
		
		
		t1:
		try
		{
			resNetData = httpGetBasicAuth("http://ubcit.webi.it.ubc.ca/__shared/Pagelet5764.html","","",NULL);
		}
		catch (Exception e)
		{
			goto t1;
		}
		if (resNetData.find("not currently in the ResNet Penalty Box.") == std::string::npos)
		{
			Log(LOG_INFO, "You are in penalty box.\n");
			std::cout << "You are in penalty box.\n";
			t2:
			try
			{
				resNetData = httpGetBasicAuth("http://192.168.1.1/cgi/cgi_wanmac.js","","",NULL);
			}
			catch (Exception e)
			{
				goto t2;
			}
			//std::cout << resNetData;
			size_t start = resNetData.find("wan_mac") + strlen("wan_mac");
			size_t end = resNetData.find(";", start);
			std::string mac = resNetData.substr(end - 4 - 2*6 - 3, 17);
			std::cout << "Your current mac is " << mac << ".\n";
			unsigned int umac[6];
			sscanf(mac.c_str(), "%x:%x:%x:%x:%x:%x",&umac[0],&umac[1],&umac[2],&umac[3],&umac[4],&umac[5]);
			if (umac[5] == 255)
			{
				if (umac[4] == 255)
				{
					if (umac[3] == 255)
					{
						if (umac[2] == 255)
						{
							if (umac[1] == 255)
							{
								if (umac[0] == 255)
								{
									umac[0] = 0;
								}
								else
								{
									umac[0]++;
								}
								umac[1] = 0;
							}
							else
							{
								umac[1]++;
							}
							umac[2] = 0;
						}
						else
						{
							umac[2]++;
						}						
						umac[3] = 0;
					}
					else
					{
						umac[3]++;
					}
					umac[4] = 0;
				}
				else 
				{
					umac[4]++;
				}
				umac[5] = 0;
			}
			else 
			{
			umac[5]++;
			}
			char buf[30];
			Log(LOG_INFO, "Your current mac is %s.\n", mac.c_str());
			sprintf(buf, "%X:%X:%X:%X:%X:%X", umac[0],umac[1],umac[2],umac[3],umac[4],umac[5]);
			std::cout << "Setting your mac to " << buf << ".\n";
			Log(LOG_INFO, "Settings your mac to mac %s.\n", buf);
			sprintf(buf, "%X%%3A%X%%3A%X%%3A%X%%3A%X%%3A%X", umac[0],umac[1],umac[2],umac[3],umac[4],umac[5]);
			char buf2[500];
			sprintf(buf2, "CMD=ATM_MAC_CONF&SET0=50693120%%3D%s", buf);
			//std::cout << buf2 << "\n";
			//login
			
			t3:
			try
			{
				httpGetBasicAuth("http://192.168.1.1/login.cgi","","",(void *)"GO=wan_mac.htm&pws=d41d8cd98f00b204e9800998ecf8427e");
			}
			catch (Exception e)
			{
				goto t3;
			}
			
			t4:
			try
			{
				resNetData = httpGetBasicAuth("http://192.168.1.1/apply.cgi","","", (void *) &(buf2[0]));
			}
			catch (Exception e)
			{
				goto t4;
			}
			//std::cout << resNetData << "\n";
			sleep(30000);
		}
		else 
		{
			Log(LOG_INFO, "Not in penalty box.\n");
		}
				
		sleep(5000);
	}
	log_close();
	return 0;
}