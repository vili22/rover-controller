/*
 * MessageHandler.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: vvirkkal
 */
#include <iostream>
#include "MessageHandler.h"

MessageHandler::MessageHandler() : running(true), notified(false) {}

std::thread MessageHandler::start() {

	std::thread t(&MessageHandler::receiverFunc, this);
	return t;
}

std::queue<std::string>& MessageHandler::getMessageQueue() {

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



