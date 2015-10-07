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

Networking::TcpReceiver::TcpReceiver(std::shared_ptr<Networking::BufferedSocketReader> br) : running(true), reader(br){

}

void Networking::TcpReceiver::loop() {

	std::mutex mutex;
	bool testRunning = true;

	while(testRunning) {

		try {
			std::string line = this->reader->readLine();
			if(line.length() > 0) {
				std::cout << line << "\n";
			}
		}catch(const std::runtime_error &e) {
			std::cout << e.what() << std::endl;
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

std::thread Networking::TcpReceiver::start() {

	std::thread t(&Networking::TcpReceiver::loop, this);
	return t;
}

void Networking::TcpReceiver::abort() {

	std::mutex mutex;

	this->reader->abort();
	mutex.lock();
	this->running = false;
	mutex.unlock();
}




