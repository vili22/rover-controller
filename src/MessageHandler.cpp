/*
 * MessageHandler.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: vvirkkal
 */
#include <iostream>
#include "MessageHandler.h"

using namespace std;

shared_ptr<MessageHandler> MessageHandler::messageHandler = nullptr;

MessageHandler::MessageHandler() : running(false), notified(false) {}

shared_ptr<MessageHandler> MessageHandler::getInstance() {

    if(messageHandler == nullptr) {
        messageHandler = make_shared<MessageHandler>();
    }

    return messageHandler;
}

std::thread MessageHandler::start() {

    running = true;
	thread t(&MessageHandler::receiverFunc, this);
	return t;
}

queue<string>& MessageHandler::getMessageQueue() {

	return this->receivedMessages;
}

std::mutex& MessageHandler::getReceiverLock() {

	return this->receiverLock;
}

std::condition_variable& MessageHandler::getReceiverConditionVariable() {

	return this->receiverCondition;
}

void MessageHandler::setNotified(bool n) {

	this->notified = n;
}

void MessageHandler::receiverFunc() {

	while(this->running) {

		std::unique_lock<std::mutex> receiverLocker(this->receiverLock);
		while(!this->notified && this->running) {

			this->receiverCondition.wait(receiverLocker);
		}

		if(!this->running) {
			return;
		}

		while(!this->receivedMessages.empty()) {

			this->sensorProcessor.newSensorReading(this->receivedMessages.front());
			this->receivedMessages.pop();
		}

		this->notified = false;

	}
}

void MessageHandler::abort() {

	std::mutex mutex;
	mutex.lock();
	this->running = false;
	mutex.unlock();
}



