/*
 * BufferedSocketReader.h
 *
 *  Created on: Sep 18, 2015
 *      Author: vvirkkal
 */

#ifndef BUFFEREDSOCKETREADER_H_
#define BUFFEREDSOCKETREADER_H_

#include <string>
#include <vector>

namespace Networking {

	class BufferedSocketReader {

		public:
			BufferedSocketReader(int socket);
			~BufferedSocketReader();
			std::string readLine();
			void abort();

		private:
			int readInput(char *buffer, int lenBuffer);
			bool parseInput(char *buffer);
			bool splitInput(std::string input);
			int socket, nLines;
			bool reading;
			std::vector<std::string> inputLines;
			std::string prevMessagePart;

	};
}



#endif /* BUFFEREDSOCKETREADER_H_ */
