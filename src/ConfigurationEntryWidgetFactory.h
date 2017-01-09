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
         virtual std::string getConfigurationValue() = 0;
};

class TextFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        TextFieldEntryWidgetGenerator(configuration::ConfigurationEntry entry);
        TextFieldEntryWidgetGenerator();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();

    private:
        QLineEdit *valueField;
};

class IntegerFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        IntegerFieldEntryWidgetGenerator(configuration::ConfigurationEntry entry);
        IntegerFieldEntryWidgetGenerator();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();
        QLineEdit *valueField;
};

class FloatFieldEntryWidgetGenerator : public ConfigurationEntryWidgetGenerator {

    public:
        FloatFieldEntryWidgetGenerator(configuration::ConfigurationEntry entry);
        FloatFieldEntryWidgetGenerator();
        QWidget* generateConfigurationEntryWidget(configuration::ConfigurationEntry entry);
        std::string getConfigurationValue();
        QLineEdit *valueField;
};

class BooleanFieldEntryWidgetGenerator : ConfigurationEntryWidgetGenerator {

    public:
        BooleanFieldEntryWidgetGenerator(configuration::ConfigurationEntry entry);
        BooleanFieldEntryWidgetGenerator();
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
