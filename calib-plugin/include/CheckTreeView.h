#pragma once

#include <QFileSystemModel>
#include <QSet>
#include <QTreeView>

class CustomModel : public QFileSystemModel {
    Q_OBJECT
   public:
    explicit CustomModel(QObject *parent = Q_NULLPTR);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

   private:
    QMap<QPersistentModelIndex, Qt::CheckState> checklist;

    bool setNodeCheckState(const QModelIndex &index, const QVariant &value, int role);
    bool setChildNodesCheck(const QModelIndex &index, const QVariant &value);

    bool setParentNodeCheckState(const QModelIndex &currentNodeIndex);
    Qt::CheckState getCheckStateAccordingToChildren(const QModelIndex &currentNodeIndex);
};

class CheckTreeView : public QTreeView {
    Q_OBJECT

    Q_PROPERTY(QString folder_path READ folderPath WRITE setFolderPath)
    Q_PROPERTY(QString filter_list READ filterList WRITE setFilterList)

   public:
    CheckTreeView(QWidget *parent = Q_NULLPTR);
    ~CheckTreeView();

    QString folderPath() const;
    void setFolderPath(const QString &path);

    QString filterList() const;
    void setFilterList(const QString &filter_list);

    QVector<QString> selectedFiles() const;
    QVector<int> selectedRows() const;

   protected:
    void contextMenuEvent(QContextMenuEvent *event);

   private:
    bool _isValidNameFilter(const QString &filterString, QStringList &filters);
    void _slotSelect();
    void _slotReset();
    void _slotDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

   signals:
    void selectedChanged();

   private:
    QString folder_path_;
    QString filter_list_;
    QSet<QModelIndex> selected_indexes_;
};
