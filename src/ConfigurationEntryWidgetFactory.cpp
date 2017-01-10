#include <sstream>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>

#include "ConfigurationEntryWidgetFactory.h"

using namespace std;
using namespace configuration;

ConfigurationEntryWidgetGenerator::ConfigurationEntryWidgetGenerator() : QWidget() {};

TextFieldEntryWidgetGenerator::TextFieldEntryWidgetGenerator(ConfigurationEntry entry) : ConfigurationEntryWidgetGenerator() {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    this->valueField = new QLineEdit(QString(entry.getValue().c_str()));
    valueField->setAlignment(Qt::AlignRight);
    valueField->setFixedWidth(225);


    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);
    layout->setContentsMargins(0,2,0,2);
};

TextFieldEntryWidgetGenerator::TextFieldEntryWidgetGenerator() {}


QWidget* TextFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

   return new TextFieldEntryWidgetGenerator(entry);
}

string TextFieldEntryWidgetGenerator::getConfigurationValue() {

    return valueField->text().toUtf8().constData();

}
IntegerFieldEntryWidgetGenerator::IntegerFieldEntryWidgetGenerator(ConfigurationEntry entry) : ConfigurationEntryWidgetGenerator() {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    valueField = new QLineEdit(QString(entry.getValue().c_str()));
    valueField->setAlignment(Qt::AlignRight);
    valueField->setFixedWidth(225);
    valueField->setValidator(new QIntValidator(5000, 6000));

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);
    layout->setContentsMargins(0,2,0,2);
}

IntegerFieldEntryWidgetGenerator::IntegerFieldEntryWidgetGenerator() {}

QWidget* IntegerFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    return new IntegerFieldEntryWidgetGenerator(entry);

}

string IntegerFieldEntryWidgetGenerator::getConfigurationValue() {

    return valueField->text().toUtf8().constData();

}


FloatFieldEntryWidgetGenerator::FloatFieldEntryWidgetGenerator(ConfigurationEntry entry) : ConfigurationEntryWidgetGenerator() {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    valueField = new QLineEdit(QString(entry.getValue().c_str()));
    valueField->setAlignment(Qt::AlignRight);
    valueField->setFixedWidth(225);
    valueField->setValidator(new QDoubleValidator());

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);
    layout->setContentsMargins(0,2,0,2);
}

FloatFieldEntryWidgetGenerator::FloatFieldEntryWidgetGenerator() {}

QWidget* FloatFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    return new FloatFieldEntryWidgetGenerator(entry);
}

string FloatFieldEntryWidgetGenerator::getConfigurationValue() {

    return valueField->text().toUtf8().constData();

}

BooleanFieldEntryWidgetGenerator::BooleanFieldEntryWidgetGenerator(ConfigurationEntry entry) : ConfigurationEntryWidgetGenerator() {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));
    toggleField = new QCheckBox();

    istringstream is(entry.getValue());
    bool state;
    is >> boolalpha >> state;

    if(state) {
        toggleField->setCheckState(Qt::Checked);
    }
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(toggleField);
    layout->setContentsMargins(0,2,0,2);
}

BooleanFieldEntryWidgetGenerator::BooleanFieldEntryWidgetGenerator() {}

QWidget* BooleanFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    return new BooleanFieldEntryWidgetGenerator(entry);
}

string BooleanFieldEntryWidgetGenerator::getConfigurationValue() {

    if(toggleField->checkState()) {
        return "true";
    } else {
        return "false";
    }

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

    shared_ptr<BooleanFieldEntryWidgetGenerator> booleanGenerator = make_shared<BooleanFieldEntryWidgetGenerator>();
    entryWidgetGenerators.insert(pair<ConfigurationEntry::TYPE,
                                 shared_ptr<ConfigurationEntryWidgetGenerator>>(ConfigurationEntry::BOOLEAN,
                                                                                 static_pointer_cast<ConfigurationEntryWidgetGenerator>(booleanGenerator)));
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


