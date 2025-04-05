#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QSplitter>
#include "filecounter.h"

QT_BEGIN_NAMESPACE
namespace ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openDirectory();
    void openFile(const QModelIndex &index);
    void checkWithFind(const QString& path);
private:
    QFileSystemModel *model_;
    FileCounter fileCounter_;

    // Виджеты
    QTreeView *treeView_;
    QTextEdit *textEdit_;
    QLabel *statusLabel_;
    QPushButton *openButton_;

    void setupUI();
};

#endif // MAINWINDOW_H
