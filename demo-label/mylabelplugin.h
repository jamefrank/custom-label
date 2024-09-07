#ifndef MYLABELPLUGIN_H
#define MYLABELPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class MyLabelPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QDesignerCustomWidgetInterface_iid FILE "mylabel.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    MyLabelPlugin(QObject *parent = nullptr);
    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
};

#endif // MYLABELPLUGIN_H