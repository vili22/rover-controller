#include <iostream>

#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>

#include "ConfigurationWidget.h"
#include "Configuration.h"
#include "ConfigurationEntryWidgetFactory.h"

using namespace std;
using namespace configuration;

ConfigurationWidget::ConfigurationWidget() : QWidget(){

    setAttribute(Qt::WA_DeleteOnClose);
    initializeView();

}

ConfigurationWidget::~ConfigurationWidget() {

}

void ConfigurationWidget::initializeView() {


    QPalette bgc(palette());
    bgc.setColor(QPalette::Background, Qt::black);

    setAutoFillBackground(true);
    setPalette(bgc);

    QRect rec = QApplication::desktop()->availableGeometry();
    int height = rec.height();
    int width = rec.width();
    setMinimumSize(0.65 * width, 0.65 * height);

    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    listWidget->setStyleSheet("QListWidget {background : gray; selection-color : gray; selection-background-color : gray}\
                              QListWidget::item {background : gray}");
    listWidget->setFocusPolicy(Qt::NoFocus);
    QVBoxLayout *content = new QVBoxLayout(this);
    content->addWidget(listWidget);

    addConfigurations();

    QWidget *buttonWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
    QPushButton *saveButton = new QPushButton("save");
    QPushButton *cancelButton = new QPushButton("cancel");
    layout->addWidget(saveButton);
    layout->addWidget(cancelButton);
    layout->addStretch(0);

    content->addWidget(buttonWidget);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveConfiguration()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void ConfigurationWidget::closeEvent(QCloseEvent *event) {

    event->accept();
}

void ConfigurationWidget::addConfigurations() {

    map<string, ConfigurationEntry> entries = Configuration::getInstance()->getConfigurationEntries();
    map<string, ConfigurationEntry>::iterator it;

    map<string, QVBoxLayout*> groupPanels;

    for(it = entries.begin(); it != entries.end(); ++it) {

        if(groupPanels.find(it->second.getCategory()) == groupPanels.end()) {

                QWidget *panelTitel = new QWidget(this);
                QHBoxLayout *titleLayout = new QHBoxLayout(panelTitel);
                titleLayout->setContentsMargins(3,8,0,8);
                QLabel *newLabel = new QLabel(QString(it->second.getCategory().c_str()));
                newLabel->setStyleSheet("QLabel { color : blue; }");
                titleLayout->addWidget(newLabel);
                titleLayout->addStretch(0);

                QWidget *panelContainer = new QWidget(this);
                QVBoxLayout *panelLayout = new QVBoxLayout(panelContainer);
                panelLayout->setSpacing(0);

                panelLayout->addWidget(panelTitel);
                panelContainer->setStyleSheet("WidgetItem:selected { background: gray}");

                QListWidgetItem *listItem = new QListWidgetItem();
                listWidget->addItem(listItem);
                listWidget->setItemWidget(listItem, panelContainer);

                groupPanels.insert(pair<string, QVBoxLayout*>(it->second.getCategory(), panelLayout));
        }
    }

    for(it = entries.begin(); it != entries.end(); ++it) {

        QWidget *newWidget = ConfigurationEntryWidgetFactory::getInstance()->generateConfigurationEntryWidget(it->second);
        groupPanels.find(it->second.getCategory())->second->addWidget(newWidget);
        entryWidgets.insert(pair<string, QWidget*>(it->second.getName(), newWidget));
    }

    for(int k = 0; k < listWidget->count(); k++) {

        QListWidgetItem *item = listWidget->item(k);
        item->setSizeHint(listWidget->itemWidget(item)->sizeHint());
    }

}

void ConfigurationWidget::saveConfiguration() {

    map<string, QWidget*>::iterator it;

    for(it = entryWidgets.begin(); it != entryWidgets.end(); it++) {

        ConfigurationEntry entry = Configuration::getInstance()->getConfiguration(it->first);
        QWidget *entryWidget = it->second;
        ConfigurationEntryWidgetGenerator *generator = static_cast<ConfigurationEntryWidgetGenerator*>(entryWidget);
        entry.setValue(generator->getConfigurationValue());
    }
}

void ConfigurationWidget::cancel() {
    std::cout << "cancel asked \n";
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver)) {
        // get the color to paint with
        QVariant var = index.model()->data(index, Qt::BackgroundRole);

        // draw the row and its content
        painter->fillRect(option.rect, var.value<QColor>());
        painter->drawText(option.rect, index.model()->data(index, Qt::DisplayRole).toString());
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}
