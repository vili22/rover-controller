#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <memory>
#include <map>
#include <string>

#include "ConfigurationEntry.h"

namespace configuration {
    class Configuration {
        public:
            Configuration();
            void setConfiguration(std::string key, ConfigurationEntry);
            std::string getConfigurationString(std::string key);
            static void initializeConfiguration();
            static std::shared_ptr<Configuration> getInstance();

        private:
            static std::shared_ptr<Configuration> configuration;
            std::map<std::string, ConfigurationEntry> configurationEntries;
    };
}

#endif // CONFIGURATION_H
