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

class MessageHandler {

public:
	MessageHandler();
	void receiverFunc();
	std::thread start();
	void abort();
	void addMessageList(QListWidget *messageList);
	void setNotified(bool);
	std::queue<std::string>& getMessageQueue();
	std::mutex& getReceiverLock();
	std::condition_variable& getReceiverConditionVariable();

private:

	std::mutex receiverLock;
	std::condition_variable receiverCondition;
	std::queue<std::string> receivedMessages;
	bool running, notified;
	QListWidget *messageList;
};



#endif /* MESSAGEHANDLER_H_ */
