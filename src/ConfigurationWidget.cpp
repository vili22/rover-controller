#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include "ConfigurationWidget.h"

using namespace std;

ConfigurationWidget::ConfigurationWidget(QWidget *parent) : QWidget(parent, Qt::Window){

    initializeView();
    addConfigurationItem("test", "");

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

    listWidget = new QListWidget();
    listWidget->setAutoFillBackground(true);
    listWidget->setPalette(bgc);
    QHBoxLayout *content = new QHBoxLayout(this);
    content->addWidget(listWidget);
}

void ConfigurationWidget::closeEvent(QCloseEvent *event) {

    event->accept();
}

void ConfigurationWidget::addConfigurationItem(const string labelText,const string value) {

    QLabel *newLabel = new QLabel(QString(labelText.c_str()));

    QLineEdit *valueField = new QLineEdit();
    valueField->setMaxLength(MAX_WIDTH);

    QWidget *containerWidget = new QWidget(this);
    containerWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout(containerWidget);
    layout->addWidget(newLabel);
    layout->addStretch(0);
    layout->addWidget(valueField);

    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(0,65));
    listWidget->addItem(listItem);
    listWidget->setItemWidget(listItem, containerWidget);
}
