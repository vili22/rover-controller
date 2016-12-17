#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include "ConfigurationEntryWidgetFactory.h"

using namespace std;
using namespace configuration;

ConfigurationEntryWidgetGenerator::ConfigurationEntryWidgetGenerator() {};

TextFieldEntryWidgetGenerator::TextFieldEntryWidgetGenerator() {};

QWidget* TextFieldEntryWidgetGenerator::generateConfigurationEntryWidget(ConfigurationEntry entry) {

    QLabel *newLabel = new QLabel(QString(entry.getName().c_str()));

    QLineEdit *valueField = new QLineEdit();
    valueField->setMaxLength(65);

    QWidget *containerWidget = new QWidget();
    containerWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);

    return containerWidget;
}

ConfigurationEntryWidgetFactory::ConfigurationEntryWidgetFactory() {

    shared_ptr<TextFieldEntryWidgetGenerator> generator = make_shared<TextFieldEntryWidgetGenerator>();
    entryWidgetGenerators.insert(pair<ConfigurationEntry::TYPE,
                                 shared_ptr<ConfigurationEntryWidgetGenerator>>(ConfigurationEntry::STRING,
                                                                                 static_pointer_cast<ConfigurationEntryWidgetGenerator>(generator)));
}
