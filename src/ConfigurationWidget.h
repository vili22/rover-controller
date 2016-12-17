#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <string>

#include <QWidget>
#include <QListWidget>
#include <QCloseEvent>


class ConfigurationWidget : public QWidget{

    Q_OBJECT
    public:
        ConfigurationWidget(QWidget *parent);
        virtual ~ConfigurationWidget();
        void addConfigurationItem(std::string label, std::string value);

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        void initializeView();

        QListWidget *listWidget;
        int MAX_WIDTH ;


};

#endif // CONFIGURATIONWIDGET_H
