#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>

#include "ConfigurationEntryWidgetFactory.h"

using namespace std;
using namespace configuration;

ConfigurationEntryWidgetGenerator::ConfigurationEntryWidgetGenerator() {};

TextFieldEntryWidgetGenerator::TextFieldEntryWidgetGenerator() {};

QWidget* TextFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    valueField = new QLineEdit(QString(entry.getValue().c_str()));
    valueField->setAlignment(Qt::AlignRight);
    valueField->setFixedWidth(225);

    QWidget *containerWidget = new QWidget();
    containerWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);
    layout->setContentsMargins(0,0,0,0);
    return containerWidget;
}

IntegerFieldEntryWidgetGenerator::IntegerFieldEntryWidgetGenerator() {}

QWidget* IntegerFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    valueField = new QLineEdit(QString(entry.getValue().c_str()));
    valueField->setAlignment(Qt::AlignRight);
    valueField->setFixedWidth(225);
    valueField->setValidator(new QIntValidator(5000, 6000));

    QWidget *containerWidget = new QWidget();
    containerWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);
    layout->setContentsMargins(0,0,0,0);
    return containerWidget;

}

FloatFieldEntryWidgetGenerator::FloatFieldEntryWidgetGenerator() {}

QWidget* FloatFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    valueField = new QLineEdit(QString(entry.getValue().c_str()));
    valueField->setAlignment(Qt::AlignRight);
    valueField->setFixedWidth(225);
    valueField->setValidator(new QDoubleValidator());

    QWidget *containerWidget = new QWidget();
    containerWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);
    layout->setContentsMargins(0,0,0,0);
    return containerWidget;

}

shared_ptr<ConfigurationEntryWidgetFactory> ConfigurationEntryWidgetFactory::configurationEntryWidgetFactory = nullptr;

ConfigurationEntryWidgetFactory::ConfigurationEntryWidgetFactory() {

    shared_ptr<TextFieldEntryWidgetGenerator> generator = make_shared<TextFieldEntryWidgetGenerator>();
    entryWidgetGenerators.insert(pair<ConfigurationEntry::TYPE,
                                 shared_ptr<ConfigurationEntryWidgetGenerator>>(ConfigurationEntry::STRING,
                                                                                 static_pointer_cast<ConfigurationEntryWidgetGenerator>(generator)));

    shared_ptr<IntegerFieldEntryWidgetGenerator> integerGenerator = make_shared<IntegerFieldEntryWidgetGenerator>();
    entryWidgetGenerators.insert(pair<ConfigurationEntry::TYPE,
                                 shared_ptr<ConfigurationEntryWidgetGenerator>>(ConfigurationEntry::INTEGER,
                                                                                 static_pointer_cast<ConfigurationEntryWidgetGenerator>(integerGenerator)));

    shared_ptr<FloatFieldEntryWidgetGenerator> floatGenerator = make_shared<FloatFieldEntryWidgetGenerator>();
    entryWidgetGenerators.insert(pair<ConfigurationEntry::TYPE,
                                 shared_ptr<ConfigurationEntryWidgetGenerator>>(ConfigurationEntry::FLOAT,
                                                                                 static_pointer_cast<ConfigurationEntryWidgetGenerator>(floatGenerator)));
}

QWidget* ConfigurationEntryWidgetFactory::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    map<ConfigurationEntry::TYPE, shared_ptr<ConfigurationEntryWidgetGenerator>>::iterator it = entryWidgetGenerators.find(entry.getType());
    if(it == entryWidgetGenerators.end()) {
        return nullptr;
    }
    return it->second->generateConfigurationEntryWidget(entry);
}

shared_ptr<ConfigurationEntryWidgetFactory> ConfigurationEntryWidgetFactory::getInstance() {

    if(configurationEntryWidgetFactory == nullptr) {
        configurationEntryWidgetFactory = make_shared<ConfigurationEntryWidgetFactory>();
    }

    return configurationEntryWidgetFactory;
}


