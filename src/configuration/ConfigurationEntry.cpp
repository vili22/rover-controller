#include "ConfigurationEntry.h"

using namespace std;
using namespace configuration;

ConfigurationEntry::ConfigurationEntry(string name, TYPE type, string category, string value) {

   this->name = name;
   this->type = type;
   this->category = category;
   this->value = value;
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

string ConfigurationEntry::getValue() {
    return value;
}

void ConfigurationEntry::setValue(string newValue) {

    value = newValue;
}
