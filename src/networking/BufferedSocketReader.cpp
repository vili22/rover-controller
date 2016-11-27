/*
 * BufferedSocketReader.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: vvirkkal
 */
#include <cstring>
#include <iostream>
#include <mutex>
#include <stdexcept>

#include <sys/types.h>
#include <unistd.h>

#include "BufferedSocketReader.h"

Networking::BufferedSocketReader::BufferedSocketReader(int socket) {

	this->socket = socket;
	this->nLines = 0;
	this->reading = true;
	this->prevMessagePart = "";
}

Networking::BufferedSocketReader::~BufferedSocketReader() {

	close(this->socket);
}

std::string Networking::BufferedSocketReader::readLine() {

	if(this->nLines > 0) {
		std::string line = *inputLines.begin();
		inputLines.erase(inputLines.begin());
		this->nLines--;
		return line;
	}

	int result, lenBuffer = 256;
	char buffer[lenBuffer+1];
	bool testReading = true;
	std::mutex mutex;

	memset(buffer, 0, lenBuffer + 1);

	while(!parseInput(buffer)) {

		memset(buffer, 0, lenBuffer);
		result = readInput(buffer, lenBuffer);
		mutex.lock();
		testReading = this->reading;
		mutex.unlock();
		if(!testReading) {
			return "";
		}
		if(result < 0) {
			std::cout << "error" << std::endl;
			throw std::runtime_error("Socket reading error");
		}
	}

	std::string line = *inputLines.begin();
	inputLines.erase(inputLines.begin());
	this->nLines--;
	return line;
}

int Networking::BufferedSocketReader::readInput(char *buffer, int lenBuffer) {

	int result = 0;
	struct timeval timeout;
	fd_set sockets;
	std::mutex mutex;
	bool testReading = true;

	while(result == 0 && testReading) {

		FD_ZERO(&sockets);
		FD_SET(this->socket, &sockets);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		result = select(this->socket+1, &sockets, NULL, NULL, &timeout);
		if(result < 0) {
			return result;
		}
		mutex.lock();
		testReading = this->reading;
		mutex.unlock();
	}

	if(!this->reading) {
		return 0;
	}

	if(FD_ISSET(this->socket, &sockets)) {
		result = read(this->socket,buffer,lenBuffer-1);
	}

	return result;
}

bool Networking::BufferedSocketReader::parseInput(char *buffer) {

	std::string newInput(buffer);
	if(newInput.compare("") == 0) {
		return false;
	}

	newInput = this->prevMessagePart.append(newInput);
	this->prevMessagePart = "";

	return splitInput(newInput);
}

bool Networking::BufferedSocketReader::splitInput(std::string input) {

	bool found = false;
	std::size_t prev = 0;
	std::size_t next = input.find('\n');
	std::string line;

	while(next != std::string::npos) {
		this->nLines++;
		found = true;
		line = input.substr(prev, next-prev);
		inputLines.push_back(line);
		prev = next+1;
		next = input.find('\n', prev);
	}

	if(prev < input.length()) {
		this->prevMessagePart = input.substr(prev, input.length()-prev);
	}
	return found;
}

void Networking::BufferedSocketReader::abort() {

	std::mutex mutex;

	mutex.lock();
	this->reading = false;
	mutex.unlock();
}




