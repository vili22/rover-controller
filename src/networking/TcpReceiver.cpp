/*
 * TcpReceiver.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: vvirkkal
 */

#include <mutex>
#include <iostream>
#include <stdexcept>

#include "TcpReceiver.h"
#include "MessageHandler.h"

using namespace std;
using namespace networking;

shared_ptr<TcpReceiver> TcpReceiver::tcpReceiver = nullptr;

TcpReceiver::TcpReceiver() : running(false) {}

shared_ptr<TcpReceiver> TcpReceiver::getInstance() {

    if(tcpReceiver == nullptr) {
        tcpReceiver = make_shared<TcpReceiver>();
    }
    return tcpReceiver;
}

void TcpReceiver::setSocketReader(shared_ptr<BufferedSocketReader> newReader) {
    reader = newReader;
}


void networking::TcpReceiver::loop() {

	mutex mutex;
	bool testRunning = true;

	while(testRunning) {

		try {
			string line = this->reader->readLine();
			if(line.length() > 0) {
				unique_lock<std::mutex> locker(MessageHandler::getInstance()->getReceiverLock());
				MessageHandler::getInstance()->getMessageQueue().push(line);
				MessageHandler::getInstance()->setNotified(true);
				MessageHandler::getInstance()->getReceiverConditionVariable().notify_one();
			}
		}catch(const runtime_error &e) {
			cout << e.what() << endl;
			return;
		}
		mutex.lock();
		testRunning = this->running;
		mutex.unlock();
		if(!testRunning) {
			std::cout << "aborted" << std::endl;
		}
	}
}

thread networking::TcpReceiver::start() {

    running = true;
	thread t(&networking::TcpReceiver::loop, this);
	return t;
}

void networking::TcpReceiver::abort() {

	mutex mutex;

	reader->abort();
	MessageHandler::getInstance()->getReceiverConditionVariable().notify_one();
	mutex.lock();
	running = false;
	mutex.unlock();
}




