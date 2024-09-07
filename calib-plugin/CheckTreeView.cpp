#include "CheckTreeView.h"

#include <QApplication>
#include <QFileInfo>
#include <QRegExp>
#include <QString>

CustomModel::CustomModel(QObject *parent) : QFileSystemModel(parent) {}

QVariant CustomModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::CheckStateRole) {
        if (checklist.contains(index)) {
            return checklist[index];
        } else {
            return Qt::Unchecked;
        }
    }
    return QFileSystemModel::data(index, role);
}

Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const { return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable; }

bool CustomModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (role == Qt::CheckStateRole) {
        setNodeCheckState(index, value, role);
        setParentNodeCheckState(index);
    }
    this->setReadOnly(false);
    QApplication::restoreOverrideCursor();
    return QFileSystemModel::setData(index, value, role);
}

bool CustomModel::setNodeCheckState(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::CheckStateRole) {
        Qt::CheckState currentNodeCheckState = static_cast<Qt::CheckState>(value.toUInt());
        if (checklist.contains(index)) {
            checklist[index] = currentNodeCheckState;
        } else {
            checklist.insert(index, currentNodeCheckState);
        }
        setChildNodesCheck(index, value);

        emit dataChanged(index, index);
        return true;
    }
    return QFileSystemModel::setData(index, value, role);
}

bool CustomModel::setChildNodesCheck(const QModelIndex &index, const QVariant &value) {
    int i = 0;
    if (canFetchMore(index)) {
        fetchMore(index);
        QEventLoop eventLoop;
        QObject::connect(this, SIGNAL(directoryLoaded(QString)), &eventLoop, SLOT(quit()));

        eventLoop.exec();  // blocks untill directoryLoaded signal is fired
    }
    int childrenCount = rowCount(index);
    QModelIndex child;
    for (i = 0; i < childrenCount; i++) {
        child = QFileSystemModel::index(i, 0, index);
        setNodeCheckState(child, value, Qt::CheckStateRole);
    }
    return true;
}

bool CustomModel::setParentNodeCheckState(const QModelIndex &currentNodeIndex) {
    QModelIndex parentNodeIndex = parent(currentNodeIndex);
    if (parentNodeIndex.isValid()) {
        Qt::CheckState parentNodeCheckState = getCheckStateAccordingToChildren(parentNodeIndex);
        if (checklist.contains(parentNodeIndex)) {
            checklist[parentNodeIndex] = parentNodeCheckState;
        } else {
            checklist.insert(parentNodeIndex, parentNodeCheckState);
        }
        emit dataChanged(parentNodeIndex, parentNodeIndex);
        return setParentNodeCheckState(parentNodeIndex);
    }
    return true;
}

Qt::CheckState CustomModel::getCheckStateAccordingToChildren(const QModelIndex &currentNodeIndex) {
    Qt::CheckState checkState = Qt::Unchecked;
    int childrenCheckCount = 0;
    bool isAnyChildChecked = false;
    bool isAnyChildPartiallyChecked = false;
    if (hasChildren(currentNodeIndex)) {
        int i;
        int childrenCount = rowCount(currentNodeIndex);
        QModelIndex childIndex;
        for (i = 0; i < childrenCount; i++) {
            childIndex = QFileSystemModel::index(i, 0, currentNodeIndex);
            if (checklist.contains(childIndex)) {
                Qt::CheckState currentCheckState = checklist[childIndex];
                if (currentCheckState == Qt::Checked) {
                    childrenCheckCount++;
                    isAnyChildChecked = true;
                } else if (currentCheckState == Qt::PartiallyChecked) {
                    isAnyChildPartiallyChecked = true;
                }
            }
        }
        if (childrenCount == childrenCheckCount) {
            checkState = Qt::Checked;
        } else if (isAnyChildChecked || isAnyChildPartiallyChecked) {
            checkState = Qt::PartiallyChecked;
        }
    }
    return checkState;
}

CheckTreeView::CheckTreeView(QWidget *parent) : QTreeView(parent), folder_path_(""), filter_list_("") {}

CheckTreeView::~CheckTreeView() {}

QString CheckTreeView::folderPath() const { return folder_path_; }

void CheckTreeView::setFolderPath(const QString &path) {
    //
    if (folder_path_ == path) return;

    //
    QFileInfo folder_info(path);
    if (!(folder_info.exists() && folder_info.isDir())) return;

    //
    QStringList valid_filter_list;
    bool is_valid = _isValidNameFilter(filter_list_, valid_filter_list);

    //
    folder_path_ = path;
    CustomModel *model = new CustomModel();
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    if (is_valid) model->setNameFilters(valid_filter_list);
    model->setRootPath(QDir::rootPath());
    model->setResolveSymlinks(true);
    this->setModel(model);
    for (int i = 1; i < model->columnCount(); ++i) this->hideColumn(i);
}

QString CheckTreeView::filterList() const { return filter_list_; }

void CheckTreeView::setFilterList(const QString &filter_list) { filter_list_ = filter_list; }

bool CheckTreeView::_isValidNameFilter(const QString &filterString, QStringList &filters) {
    // 使用分号分割字符串
    filters = filterString.split(QLatin1Char(';'), Qt::SkipEmptyParts);

    // 定义正则表达式来匹配后缀名模式
    QRegExp validPattern("^\\*\\.[a-zA-Z0-9]+$");

    // 检查每个部分是否都符合后缀名模式
    for (const QString &filter : filters) {
        if (!validPattern.exactMatch(filter.trimmed())) {
            return false;
        }
    }

    return !filters.isEmpty();  // 至少有一个有效的后缀名
}
