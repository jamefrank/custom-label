#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class CheckTreeViewPlugin : public QObject, public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QDesignerCustomWidgetInterface_iid)
    Q_INTERFACES(QDesignerCustomWidgetInterface)

   public:
    CheckTreeViewPlugin(QObject *parent = nullptr);
    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
};