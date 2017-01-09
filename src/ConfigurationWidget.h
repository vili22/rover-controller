#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <string>
#include <map>

#include <QWidget>
#include <QListWidget>
#include <QCloseEvent>
#include <QStyledItemDelegate>
#include <QPainter>


class ConfigurationWidget : public QWidget{

    Q_OBJECT
    public:
        ConfigurationWidget();
        virtual ~ConfigurationWidget();

    protected:
        void closeEvent(QCloseEvent *event);

    private slots:
        void saveConfiguration();
        void cancel();

    private:
        std::map<std::string, QWidget*> entryWidgets;
        void initializeView();
        void addConfigurations();

        QListWidget *listWidget;
        int MAX_WIDTH ;


};

class Delegate : public QStyledItemDelegate {

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};


#endif // CONFIGURATIONWIDGET_H
