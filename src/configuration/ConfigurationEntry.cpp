#include "ConfigurationEntry.h"

using namespace std;
using namespace configuration;

ConfigurationEntry::ConfigurationEntry(string name, TYPE type, string category) {

   this->name = name;
   this->type = type;
   this->category = category;
}

string ConfigurationEntry::getName() {
    return name;
}

ConfigurationEntry::TYPE ConfigurationEntry::getType() {
    return type;
}

string ConfigurationEntry::getCategory() {
    return category;
}

