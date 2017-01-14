/*
 * TcpReceiver.h
 *
 *  Created on: Oct 4, 2015
 *      Author: vvirkkal
 */

#ifndef TCPRECEIVER_H_
#define TCPRECEIVER_H_

#include <memory>
#include <thread>

#include "BufferedSocketReader.h"

namespace networking {

	class TcpReceiver {

	public:
        TcpReceiver();
		void loop();
		std::thread start();
		void abort();
		static std::shared_ptr<TcpReceiver> getInstance();
		void setSocketReader(std::shared_ptr<networking::BufferedSocketReader> reader);

	private:
        static std::shared_ptr<TcpReceiver> tcpReceiver;
		bool running;
		std::shared_ptr<BufferedSocketReader> reader;
	};
}


#endif /* TCPRECEIVER_H_ */
