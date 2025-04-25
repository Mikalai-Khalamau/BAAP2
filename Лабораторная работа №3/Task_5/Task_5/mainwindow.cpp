#include "mainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>

const int k600=600;
const int k1000=1000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    model_(new QFileSystemModel(this)),
    treeView_(new QTreeView(this)),
    textEdit_(new QTextEdit(this)),
    statusLabel_(new QLabel(this)),
    infoLabel_(new QLabel(this)),
    openButton_(new QPushButton(this))
{
    setupUI();

    resize(k1000, k600);
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

    //Введите команды в терминал для проверки
    // find . -type f | wc -l количество папок
    // expr $(find . -type d | wc -l) - 1 количество файлов

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

