#ifndef DEAR_IPCSERVER_DEF
#define DEAR_IPCSERVER_DEF

extern "C"{
	#include <uv.h>
	#include <unistd.h>
}
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <message/message.hpp>

class IPCServer{
public:
	IPCServer(uv_loop_t *loop, const char *path, MessageHandler *handler);
	~IPCServer();
	void start();
	void sendMessage(Message *message, uv_write_cb callback = nullptr, void *callbackData = nullptr);
private:
	uv_loop_t *uvLoop;
	uv_pipe_t serverPipe;
	uv_pipe_t *clientPipe = nullptr;
	MessageHandler *handler;
	bool connecting;
	std::vector<char> messageBuf;
};

#endif