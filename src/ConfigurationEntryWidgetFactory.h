#ifndef CONFIGURATIONENTRYWIDGETFACTORY_H
#define CONFIGURATIONENTRYWIDGETFACTORY_H

#include <map>
#include <memory>

#include <QWidget>

#include "ConfigurationEntry.h"

class ConfigurationEntryWidgetGenerator {

    public:
         ConfigurationEntryWidgetGenerator();
         virtual QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry) = 0;

};

class TextFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        TextFieldEntryWidgetGenerator();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
};

class NumberFieldEntryWidgetGenerator : ConfigurationEntryWidgetGenerator {

    public:
        NumberFieldEntryWidgetGenerator();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
};

class BooleanFieldEntryWidgetGenerator : ConfigurationEntryWidgetGenerator {

    public:
        BooleanFieldEntryWidgetGenerator();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
};

class ConfigurationEntryWidgetFactory {

    public:
        ConfigurationEntryWidgetFactory();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);

    protected:

    private:
        std::map<configuration::ConfigurationEntry::TYPE, std::shared_ptr<ConfigurationEntryWidgetGenerator>> entryWidgetGenerators;
};

#endif // CONFIGURATIONENTRYWIDGETFACTORY_H
