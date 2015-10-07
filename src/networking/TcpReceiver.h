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

namespace Networking {

	class TcpReceiver {

	public:
		TcpReceiver(std::shared_ptr<BufferedSocketReader> reader);
		void loop();
		std::thread start();
		void abort();

	private:
		bool running;
		std::shared_ptr<BufferedSocketReader> reader;
	};
}


#endif /* TCPRECEIVER_H_ */
