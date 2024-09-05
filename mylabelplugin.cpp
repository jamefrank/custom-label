#include "mylabelplugin.h"
 
#include "mylabel.h"
 
MyLabelPlugin::MyLabelPlugin(QObject *parent)
{
}
 
QString MyLabelPlugin::name() const
{
    return "MyLabel";
}
 
QString MyLabelPlugin::includeFile() const
{
    return "mylabel.h";
}
 
QString MyLabelPlugin::group() const
{
    return tr("Custom Widgets");
}
 
QIcon MyLabelPlugin::icon() const
{
    return QIcon(":/images/mylabel.png");
}
 
QString MyLabelPlugin::toolTip() const
{
    return tr("An custom label widget");
}
 
QString MyLabelPlugin::whatsThis() const
{
    return tr("balabala balabala.");
}
 
bool MyLabelPlugin::isContainer() const
{
    return false;
}
 
QWidget *MyLabelPlugin::createWidget(QWidget *parent)
{
    return new MyLabel(parent);
}