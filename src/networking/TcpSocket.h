/*
 * TcpSocket.h
 *
 *  Created on: Sep 15, 2015
 *      Author: vvirkkal
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <string>

namespace Networking {
	class TcpSocket {

	public:
		TcpSocket(std::string ip, int port);
		~TcpSocket();
		int getSocket();

	private:
		void createConnection();

		int sockfd;
		int port;
		std::string ip;
	};
}
#endif /* TCPSOCKET_HPP_ */
