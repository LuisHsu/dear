#include "area.hpp"

#include <iostream>

Area::Area(){
/*** Area module ***/
	const std::string modDir("mod/area");
	// Get module directory
	DIR *areaModDir = opendir(modDir.c_str());
	if(!areaModDir){
		perror("[Area module] Open module directory error:");
	}
	// Load modules
	struct dirent *entry = nullptr;
	while((entry = readdir(areaModDir)) != nullptr){
		if(entry->d_type == DT_REG){
			// Get dl handle
			void *modHandle = dlopen((modDir + "/" + entry->d_name).c_str(), RTLD_LAZY);
			if(!modHandle){
				std::cerr << "[Area module] Error open module " << entry->d_name << " : " << dlerror() << std::endl;
			}
			// Get create function
			area_module_create_t createFunc = (area_module_create_t) dlsym(modHandle, "createModule");
			if(!createFunc){
				std::cerr << "[Area module] Error open create function : " << dlerror() << std::endl;
			}
			// Create module instance
			areaModules[entry->d_name] = createFunc(this);
		}
	}
}
Area::~Area(){
	// Delete area modules
	for(std::pair<std::string, AreaModule*> modulePair : areaModules){
		modulePair.second->removeModule();
	}
}
void Area::handleMessage(Message *message, void *deliver, DeliverType type, void *data){
	User *user = nullptr;
	if(type == DEAR_MESSAGE_IPCserver){
		user = (User *)((IPCServer *)deliver)->userData;
	}else{
		// TODO: TCP user
	}
	switch(message->type){
		case DEAR_Connect_request:
			connectRequest(message, deliver, type, data);
		break;
		case DEAR_KeyUp_request:
			std::cout << "KeyUp: " << ((KeyboardRequest *) message)->key << std::endl;
		break;
		case DEAR_KeyDown_request:
			std::cout << "KeyDown: " << ((KeyboardRequest *) message)->key << std::endl;
		break;
		case DEAR_PointerMotion_request:
			if(user->currentHandler()){
				user->currentHandler()->pointerMotion(message, deliver, type, data);
			}
		break;
		case DEAR_PointerUp_request:
			std::cout << "PointerUp: " << ((PointerButtonRequest *) message)->button << std::endl;
		break;
		case DEAR_PointerDown_request:
			std::cout << "PointerDown: " << ((PointerButtonRequest *) message)->button << std::endl;
		break;
		case DEAR_PointerAxis_request:
			if(user->currentHandler()){
				user->currentHandler()->pointerAxis(message, deliver, type, data);
			}
		break;
		default:
		break;
	}
}
void Area::connectRequest(Message *message, void *deliver, DeliverType type, void *data){
	User *newUser = nullptr;
	if(type == DEAR_MESSAGE_IPCserver){
		IPCServer *server = (IPCServer *)deliver;
		// Set new user
		newUser = new User(server);
		server->userData = newUser;
		users.push_back(newUser);
	}else{
		// TODO: TCP user
	}
	users.push_back(newUser);
	// Init area modules
	for(std::pair<std::string, AreaModule*> areaModulePair : areaModules){
		areaModulePair.second->userInit(newUser);
	}
	// Init user modules
	newUser->initModule();
	// Send connect notice
	Message *msg = new Message;
	msg->type = DEAR_Connect_notice;
	msg->length = sizeof(*msg);
	sendMessage(msg, deliver, type, data);
}
void Area::sendMessage(Message *message, void *deliver, DeliverType type, void *data, uv_write_cb callback, void *callbackData){
	switch(type){
		case MessageHandler::DeliverType::DEAR_MESSAGE_IPCserver:
			((IPCServer *)deliver)->sendMessage(message, callback, callbackData);
		break;
		case MessageHandler::DeliverType::DEAR_MESSAGE_TCPserver:
			((TCPServer *)deliver)->sendMessage(message, (uv_stream_t *)data, callback, callbackData);
		break;
		default:
		break;
	}
}
void Area::messageReady(void *deliver, DeliverType type){
	switch(type){
		case DEAR_MESSAGE_IPCserver:
			std::cout << "IPC listening." << std::endl;
		break;
		case DEAR_MESSAGE_TCPserver:
			std::cout << "TCP listening." << std::endl;
		break;
		default:
		break;
	}
}