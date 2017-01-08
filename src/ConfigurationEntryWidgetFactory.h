#ifndef CONFIGURATIONENTRYWIDGETFACTORY_H
#define CONFIGURATIONENTRYWIDGETFACTORY_H

#include <map>
#include <memory>

#include <QWidget>

#include "ConfigurationEntry.h"

class ConfigurationEntryWidgetGenerator : public QWidget {

    public:
         ConfigurationEntryWidgetGenerator();
         virtual QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry) = 0;
         virtual std::string geConfigurationValue
};

class TextFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        TextFieldEntryWidgetGenerator(ConfigurationEntry entry);
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();
};

class IntegerFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        IntegerFieldEntryWidgetGenerator(ConfigurationEntry entry);
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();
};

class FloatFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        FloatFieldEntryWidgetGenerator(ConfigurationEntry entry);
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();
};

class BooleanFieldEntryWidgetGenerator : ConfigurationEntryWidgetGenerator {

    public:
        BooleanFieldEntryWidgetGenerator(ConfigurationEntry entry);
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();
};

class ConfigurationEntryWidgetFactory {

    public:
        ConfigurationEntryWidgetFactory();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        static std::shared_ptr<ConfigurationEntryWidgetFactory> getInstance();

    protected:

    private:
        std::map<configuration::ConfigurationEntry::TYPE, std::shared_ptr<ConfigurationEntryWidgetGenerator>> entryWidgetGenerators;
        static std::shared_ptr<ConfigurationEntryWidgetFactory> configurationEntryWidgetFactory;
};

#endif // CONFIGURATIONENTRYWIDGETFACTORY_H
