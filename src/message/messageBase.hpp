#ifndef MESSAGEBASE_DEF
#define MESSAGEBASE_DEF

#include <cstdint>

enum MsgType{
	IPC_Connect_req,
	IPC_Connect_rep
};

class Message{
public:
	MsgType type;
	uint32_t length;
};

#endif