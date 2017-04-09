/*
 * TcpSocket.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: vvirkkal
 */
#include <cstring>
#include <iostream>
#include <stdexcept>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/tcp.h>

#include "TcpSocket.h"


networking::TcpSocket::TcpSocket(std::string ipAddress, int port) {

	this->sockfd = 0;
	this->ip = ipAddress;
	this->port = port;
	this->createConnection();
}

networking::TcpSocket::~TcpSocket() {

}

void networking::TcpSocket::createConnection() {

	struct sockaddr_in serv_addr;

	if((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		throw std::runtime_error("Unable to create socket");
	}

//	if(fcntl(this->sockfd, F_SETFL, fcntl(this->sockfd, F_GETFL) | O_NONBLOCK) < 0) {
//		throw std::runtime_error("Unable to set non blocking");
//	}

//	int val = 1;
//	if(setsockopt(this->sockfd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) < 0) {
//		throw std::runtime_error("Failed to set no delay mode\n");
//	}

	std::memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port);

	if(inet_pton(AF_INET, this->ip.c_str(), &serv_addr.sin_addr) <= 0) {
		throw std::runtime_error("Unable to find address");
	}

	if(connect(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		throw std::runtime_error("Unable to connect to given address");
	}
}

int networking::TcpSocket::getSocket() {

	return this->sockfd;
}

int networking::TcpSocket::writeLine(std::string message) {

	return write(this->sockfd, message.c_str(), message.length());

}


