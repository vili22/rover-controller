/*
 * MessageHandler.h
 *
 *  Created on: Oct 10, 2015
 *      Author: vvirkkal
 */

#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

#include <QListWidget>

#include "SensorProcessor.h"

class MessageHandler {

public:
	MessageHandler();
	void receiverFunc();
	std::thread start();
	void abort();
	void setNotified(bool);
	std::queue<std::string>& getMessageQueue();
	std::mutex& getReceiverLock();
	std::condition_variable& getReceiverConditionVariable();
    static std::shared_ptr<MessageHandler> getInstance();
private:

    static std::shared_ptr<MessageHandler> messageHandler;
	std::mutex receiverLock;
	std::condition_variable receiverCondition;
	std::queue<std::string> receivedMessages;
	bool running, notified;
	SensorProcessor sensorProcessor;
};



#endif /* MESSAGEHANDLER_H_ */
