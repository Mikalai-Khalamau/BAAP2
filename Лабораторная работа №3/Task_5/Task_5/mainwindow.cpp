#include "mainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    model_(new QFileSystemModel(this)),
    treeView_(new QTreeView(this)),
    textEdit_(new QTextEdit(this)),
    statusLabel_(new QLabel(this)),
    openButton_(new QPushButton(this))
{
    setupUI();
}

void MainWindow::setupUI()
{
    // Настройка модели
    model_->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

    // Настройка treeView
    treeView_->setModel(model_);
    treeView_->setHeaderHidden(true);

    // Настройка textEdit
    textEdit_->setReadOnly(true);

    // Настройка кнопки
    openButton_->setText("Открыть папку");

    // Настройка метки статуса
    statusLabel_->setText("Выберите начальную папку");

    // Создаем разделитель
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(treeView_);
    splitter->addWidget(textEdit_);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

    // Компоновка
    QVBoxLayout *main_layout = new QVBoxLayout();
    QHBoxLayout *top_layout = new QHBoxLayout();

    top_layout->addWidget(openButton_);
    top_layout->addStretch();
    top_layout->addWidget(statusLabel_);

    main_layout->addLayout(top_layout);
    main_layout->addWidget(splitter);

    // Центральный виджет
    QWidget *central_widget = new QWidget(this);
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);

    // Подключение сигналов
    connect(openButton_, &QPushButton::clicked, this, &MainWindow::openDirectory);
    connect(treeView_, &QTreeView::doubleClicked, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{

}

void MainWindow::openDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Выберите начальную папку");
    if (!dir.isEmpty()) {
        model_->setRootPath(dir);
        treeView_->setRootIndex(model_->index(dir));

        fileCounter_.count(dir);
         checkWithFind(dir);
        statusLabel_->setText(
            QString("Папок: %1 | Файлов: %2 | Всего: %3")
                .arg(fileCounter_.dirCount())
                .arg(fileCounter_.fileCount())
                .arg(fileCounter_.dirCount() + fileCounter_.fileCount())
            );
    }
}

void MainWindow::openFile(const QModelIndex &index)
{
    if (!model_->isDir(index)) {
        QString file_path = model_->filePath(index);
        QFile file(file_path);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit_->setPlainText(in.readAll());
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка",
                                 "Не удалось открыть файл: " + file.errorString());
        }
    }
}
void MainWindow::checkWithFind(const QString& path)
{
    fileCounter_.count(path);
    int our_files = fileCounter_.fileCount();
    int our_dirs = fileCounter_.dirCount(); // не учитывает корень

    QProcess p;
    p.start("sh", QStringList() << "-c"
                                << QString("find \"%1\" -type f | wc -l").arg(path));
    p.waitForFinished();
    int find_files = p.readAllStandardOutput().trimmed().toInt();

    p.start("sh", QStringList() << "-c"
                                << QString("find \"%1\" -type d | wc -l").arg(path));
    p.waitForFinished();
    int find_dirs = p.readAllStandardOutput().trimmed().toInt();

    qDebug() << "Сравнение (исключая . и ..):";
    qDebug() << "Файлы:" << "наш код =" << our_files << "| find =" << find_files;
    qDebug() << "Папки:" << "наш код =" << our_dirs << "(+1 с корнем = " << (our_dirs + 1) << ") | find =" << find_dirs;
}
