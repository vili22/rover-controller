#include <sstream>
#include <iostream>

#include "Configuration.h"

using namespace std;
using namespace configuration;

std::shared_ptr<Configuration> Configuration::configuration = nullptr;

Configuration::Configuration() {

}

shared_ptr<Configuration> Configuration::getInstance() {

    if(configuration == nullptr) {
        configuration = make_shared<Configuration>();
    }

    return configuration;
}

void Configuration::setConfiguration(string key, ConfigurationEntry configurationEntry) {

    map<string,ConfigurationEntry>::iterator it = configurationEntries.find(key);
    if(it == configurationEntries.end()) {
        configurationEntries.insert(pair<string, ConfigurationEntry>(key, configurationEntry));
    } else {
        configurationEntries.insert(it, pair<string, ConfigurationEntry>(key, configurationEntry));
    }
}

ConfigurationEntry& Configuration::getConfiguration(string key) {

    map<string, ConfigurationEntry>::iterator it;
    it = configurationEntries.find(key);

    return it->second;
}

string Configuration::getConfigurationString(string key) {

    ConfigurationEntry entry = getConfiguration(key);
    return entry.getValue();
}

int Configuration::getConfigurationInteger(std::string key) {

    ConfigurationEntry entry = getConfiguration(key);
    return stoi(entry.getValue());
}

double Configuration::getConfigurationFloat(std::string key) {

    ConfigurationEntry entry = getConfiguration(key);
    return stod(entry.getValue());
}

bool Configuration::getConfigurationBoolean(std::string key) {

    ConfigurationEntry entry = getConfiguration(key);
    istringstream is(entry.getValue());
    bool booleanValue;
    is >> boolalpha >> booleanValue;
    return booleanValue;
}



 std::map<std::string, ConfigurationEntry> Configuration::getConfigurationEntries() {

    return configurationEntries;
 }

void Configuration::initializeConfiguration() {

    Configuration::getInstance()->setConfiguration("HOST_IP_ADDRESS", ConfigurationEntry("HOST_IP_ADDRESS",
                                                                                          ConfigurationEntry::STRING,
                                                                                           "CONNECTION",
                                                                                           "192.168.1.69"));
    Configuration::getInstance()->setConfiguration("HOST_PORT", ConfigurationEntry("HOST_PORT",
                                                                                    ConfigurationEntry::INTEGER,
                                                                                    "CONNECTION",
                                                                                    "5550"));
    Configuration::getInstance()->setConfiguration("VIDEO_PORT", ConfigurationEntry("VIDEO_PORT",
                                                                                    ConfigurationEntry::INTEGER,
                                                                                    "CONNECTION",
                                                                                    "5001"));
    Configuration::getInstance()->setConfiguration("WHEEL_DIAMETER", ConfigurationEntry("WHEEL_DIAMETER",
                                                                                    ConfigurationEntry::FLOAT,
                                                                                    "ROVER_DETAILS",
                                                                                    "0.064"));
    Configuration::getInstance()->setConfiguration("BASE_LENGTH", ConfigurationEntry("BASE_LENGTH",
                                                                                    ConfigurationEntry::FLOAT,
                                                                                    "ROVER_DETAILS",
                                                                                    "0.145"));
    Configuration::getInstance()->setConfiguration("ENCODER_RESOLUTION", ConfigurationEntry("ENCODER_RESOLUTION",
                                                                                    ConfigurationEntry::INTEGER,
                                                                                    "ROVER_DETAILS",
                                                                                    "20"));
    Configuration::getInstance()->setConfiguration("STORE_TO_FILE", ConfigurationEntry("STORE_TO_FILE",
                                                                                    ConfigurationEntry::BOOLEAN,
                                                                                    "SENSORS",
                                                                                    "false"));
}





