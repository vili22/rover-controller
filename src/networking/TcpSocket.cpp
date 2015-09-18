/*
 * TcpSocket.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: vvirkkal
 */
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "TcpSocket.h"


Networking::TcpSocket::TcpSocket(std::string ipAddress, int port) {

	this->sockfd = 0;
	this->ip = ipAddress;
	this->port = port;
	createConnection();
}

Networking::TcpSocket::~TcpSocket() {

	close(this->sockfd);
}

void Networking::TcpSocket::createConnection() {

	struct sockaddr_in serv_addr;

	if((this->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

	}

	std::memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(this->port);

	if(inet_pton(AF_INET, this->ip.c_str(), &serv_addr.sin_addr)<=0) {
	}

	if(connect(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {

	}
}


