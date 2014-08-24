#include "ServerMain.hpp"

using namespace std;

HTTPServer* server;

/*
信号处理回调函数，正常情况应该打印coredump信息
*/
void signalHandler(int signo)
{
	switch(signo)
	{
		case SIGINT:cout << "SIGINT Recieved." << endl; server->Stop(); break;
		case SIGSTOP:cout << "SIGSTOP" << endl; break;
		case SIGKILL: cout << "SIGKILL" << endl; break;
		case SIGPIPE: cout << "SIGPIPE Recieved." << endl; break;
	}
}
void mapSignalHandlers()
{
	if(signal(SIGINT, signalHandler) == SIG_ERR)
	{
		cerr << "Failed to map SIGINT handler." << endl;
	}
	if(signal(SIGKILL, signalHandler) == SIG_ERR)
	{
		cerr << "Failed to map SIGKILL handler." << endl;
	}
	if(signal(SIGSTOP, signalHandler) == SIG_ERR)
	{
		cerr << "Failed to map SIGSTOP handler." << endl;
	}
	if(signal(SIGPIPE, signalHandler) == SIG_ERR)
	{
		cerr << "Failed to map SIGPIPE handler." << endl;
	}
}

int main(int argc, char** argv)
{
	ServerConfig serverConfig;
	serverConfig.LoadFile("res/DB/Server.config");
	serverConfig.Init();

	HTTPServer os(serverConfig);
	//全局变量
	server = &os;
	//信号处理
	mapSignalHandlers();
	//启动服务
	return os.Start();
}
