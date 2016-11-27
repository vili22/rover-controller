#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <vector>
#include <string>

namespace utils {

	std::vector<std::vector<double>> parse_sensor_data(const std::string filename);
}


#endif // FILEUTILS_H_
