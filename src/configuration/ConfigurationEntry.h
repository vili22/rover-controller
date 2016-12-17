#ifndef CONFIGURATIONENTRY_H
#define CONFIGURATIONENTRY_H

#include <string>

namespace configuration {
    class ConfigurationEntry {
        public:
            enum TYPE {STRING, BOOLEAN, INTEGER, FLOAT};
            ConfigurationEntry(std::string name, TYPE type, std::string category);
            std::string getName();
            TYPE getType();
            std::string getCategory();

        private:
            std::string name;
            TYPE type;
            std::string category;
    };
}

#endif // CONFIGURATIONENTRY_H
