#include "CheckTreeViewPlugin.h"

#include "CheckTreeView.h"

CheckTreeViewPlugin::CheckTreeViewPlugin(QObject *parent) {}

QString CheckTreeViewPlugin::name() const { return "CheckTreeView"; }

QString CheckTreeViewPlugin::includeFile() const { return "CheckTreeView.h"; }

QString CheckTreeViewPlugin::group() const { return tr("Custom Widgets"); }

QIcon CheckTreeViewPlugin::icon() const { return QIcon(); }

QString CheckTreeViewPlugin::toolTip() const { return tr("checkble file tree"); }

QString CheckTreeViewPlugin::whatsThis() const { return QString(); }

bool CheckTreeViewPlugin::isContainer() const { return false; }

QWidget *CheckTreeViewPlugin::createWidget(QWidget *parent) { return new CheckTreeView(parent); }