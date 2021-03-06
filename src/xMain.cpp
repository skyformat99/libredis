#include "xRedis.h"
#include "xCurrentThread.h"
#include "xLog.h"
#include <stdio.h>


xAsyncLogging *g_asyncLog = nullptr;
void asyncOutput(const char* msg, int len)
{
	printf("%s\n",msg);
	g_asyncLog->append(msg, len);
}

char *ascii_logo =
"                _._                                                  \n"
"           _.-``__ ''-._                                             \n"
"      _.-``    `.  `_.  ''-._           redis 1.0 					  \n"
"  .-`` .-```.  ```\\/    _.,_ ''-._                                  \n"
" (    '      ,       .-`  | `,    )     Running in release			  \n"
" |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379                   \n"
" |    `-._   `._    /     _.-'    |  								  \n"
"  `-._    `-._  `-./  _.-'    _.-'                                   \n"
" |`-._`-._    `-.__.-'    _.-'_.-'|                                  \n"
" |    `-._`-._        _.-'_.-'    |                   				  \n"
"  `-._    `-._`-.__.-'_.-'    _.-'                                   \n"
" |`-._`-._    `-.__.-'    _.-'_.-'|                                  \n"
" |    `-._`-._        _.-'_.-'    |                                  \n"
"  `-._    `-._`-.__.-'_.-'    _.-'                                   \n"
"      `-._    `-.__.-'    _.-'                                       \n"
"          `-._        _.-'                                           \n"
"              `-.__.-'                                               \n";
int main(int argc, char* argv[])
{	
	if (argc < 4)
	{
		fprintf(stderr, "Usage: server <address> <port> <threads>\n");
	}
	else
	{		
		const char* ip = argv[1];
		uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
		int32_t threadCount =  atoi(argv[3]);
		
		xLogger::setOutput(asyncOutput);
	    
		xAsyncLogging log("libredis", 2000);
		log.start();
		g_asyncLog = &log;
		xRedis redis(ip,port,threadCount);
		redis.run();
	}
	return 0;
}
