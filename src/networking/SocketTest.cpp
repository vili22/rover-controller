/*
 * SocketTest.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: vvirkkal
 */
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <memory>
#include <thread>
#include <chrono>

#include "TcpSocket.h"
#include "TcpReceiver.h"


int main() {

	std::shared_ptr<Networking::TcpSocket> tcpSocket;
	try{
		tcpSocket = std::make_shared<Networking::TcpSocket>("192.168.1.64", 5555);
	}catch(std::exception const& e) {
		std::cout << e.what() << "here\n";
		return -1;
	}

	Networking::TcpReceiver receiver(std::make_shared<Networking::BufferedSocketReader>(tcpSocket->getSocket()));
	std::thread t = receiver.start();
	std::this_thread::sleep_for(std::chrono::seconds(25));
	receiver.abort();
	t.join();
//	std::string line ="";
//
//	while(line.compare("exit") != 0) {
//		try {
//			line = reader.readLine();
//			std::cout << line << " " << line.length() << "\n";
//		}catch(std::exception const& e) {
//			std::cout << e.what() << std::endl;
//			delete tcpSocket;
//			return -1;
//		}
//	}


	return 0;
}


