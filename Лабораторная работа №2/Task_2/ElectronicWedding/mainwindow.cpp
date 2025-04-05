#include "mainwindow.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    // Создаём виджеты ввода
    QLabel* idLabel = new QLabel("ID:");
    idEdit_ = new QLineEdit;

    QLabel* sexLabel = new QLabel("Пол:");
    sexCombo_ = new QComboBox;
    sexCombo_->addItem("М");
    sexCombo_->addItem("Ж");

    QLabel* fioLabel = new QLabel("ФИО:");
    fioEdit_ = new QLineEdit;

    QLabel* ageLabel = new QLabel("Возраст:");
    ageEdit_ = new QLineEdit;
    ageEdit_->setValidator(new QIntValidator(0, 200, this));

    QLabel* heightLabel = new QLabel("Рост:");
    heightEdit_ = new QLineEdit;
    heightEdit_->setValidator(new QIntValidator(0, 300, this));

    QLabel* weightLabel = new QLabel("Вес:");
    weightEdit_ = new QLineEdit;
    weightEdit_->setValidator(new QIntValidator(0, 300, this));

    QLabel* minAgeLabel = new QLabel("Min возраст:");
    minAgeEdit_ = new QLineEdit;
    minAgeEdit_->setValidator(new QIntValidator(0, 200, this));

    QLabel* maxAgeLabel = new QLabel("Max возраст:");
    maxAgeEdit_ = new QLineEdit;
    maxAgeEdit_->setValidator(new QIntValidator(0, 200, this));

    QLabel* minHeightLabel = new QLabel("Min рост:");
    minHeightEdit_ = new QLineEdit;
    minHeightEdit_->setValidator(new QIntValidator(0, 300, this));

    QLabel* maxHeightLabel = new QLabel("Max рост:");
    maxHeightEdit_ = new QLineEdit;
    maxHeightEdit_->setValidator(new QIntValidator(0, 300, this));

    QLabel* minWeightLabel = new QLabel("Min вес:");
    minWeightEdit_ = new QLineEdit;
    minWeightEdit_->setValidator(new QIntValidator(0, 300, this));

    QLabel* maxWeightLabel = new QLabel("Max вес:");
    maxWeightEdit_ = new QLineEdit;
    maxWeightEdit_->setValidator(new QIntValidator(0, 300, this));

    // Кнопки
    loadButton_ = new QPushButton("Загрузить из файла");
    saveButton_ = new QPushButton("Сохранить в файл");
    addButton_ = new QPushButton("Добавить");
    removeButton_ = new QPushButton("Удалить (по индексу)");
    editButton_ = new QPushButton("Изменить (по индексу)");
    viewAllButton_ = new QPushButton("Показать всех");
    findPairsButton_ = new QPushButton("Найти все пары");
    sortMalesButton_ =
        new QPushButton("Отсортировать женихов по убыванию возраста");
    sortFemalesButton_ =
        new QPushButton("Отсортировать невест по убыванию возраста");
    searchMatchesButton_ = new QPushButton("Поиск кандидатов для (index)");

    // Поле вывода
    outputText_ = new QTextEdit;
    outputText_->setReadOnly(true);

    // Привязываем слоты
    connect(loadButton_, &QPushButton::clicked, this,
            &MainWindow::onLoadClicked);
    connect(saveButton_, &QPushButton::clicked, this,
            &MainWindow::onSaveClicked);
    connect(addButton_, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(removeButton_, &QPushButton::clicked, this,
            &MainWindow::onRemoveClicked);
    connect(editButton_, &QPushButton::clicked, this,
            &MainWindow::onEditClicked);
    connect(viewAllButton_, &QPushButton::clicked, this,
            &MainWindow::onViewAllClicked);
    connect(findPairsButton_, &QPushButton::clicked, this,
            &MainWindow::onFindPairsClicked);
    connect(sortMalesButton_, &QPushButton::clicked, this,
            &MainWindow::onSortMalesByAgeClicked);
    connect(sortFemalesButton_, &QPushButton::clicked, this,
            &MainWindow::onSortFemalesByAgeClicked);
    connect(searchMatchesButton_, &QPushButton::clicked, this,
            &MainWindow::onSearchMatchesClicked);

    // Компоновка
    QGridLayout* grid = new QGridLayout;
    grid->addWidget(idLabel, 0, 0);
    grid->addWidget(idEdit_, 0, 1);
    grid->addWidget(sexLabel, 1, 0);
    grid->addWidget(sexCombo_, 1, 1);
    grid->addWidget(fioLabel, 2, 0);
    grid->addWidget(fioEdit_, 2, 1);
    grid->addWidget(ageLabel, 3, 0);
    grid->addWidget(ageEdit_, 3, 1);
    grid->addWidget(heightLabel, 4, 0);
    grid->addWidget(heightEdit_, 4, 1);
    grid->addWidget(weightLabel, 5, 0);
    grid->addWidget(weightEdit_, 5, 1);

    grid->addWidget(minAgeLabel, 6, 0);
    grid->addWidget(minAgeEdit_, 6, 1);
    grid->addWidget(maxAgeLabel, 7, 0);
    grid->addWidget(maxAgeEdit_, 7, 1);
    grid->addWidget(minHeightLabel, 8, 0);
    grid->addWidget(minHeightEdit_, 8, 1);
    grid->addWidget(maxHeightLabel, 9, 0);
    grid->addWidget(maxHeightEdit_, 9, 1);
    grid->addWidget(minWeightLabel, 10, 0);
    grid->addWidget(minWeightEdit_, 10, 1);
    grid->addWidget(maxWeightLabel, 11, 0);
    grid->addWidget(maxWeightEdit_, 11, 1);

    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(loadButton_);
    buttonsLayout->addWidget(saveButton_);
    buttonsLayout->addWidget(addButton_);
    buttonsLayout->addWidget(removeButton_);
    buttonsLayout->addWidget(editButton_);
    buttonsLayout->addWidget(viewAllButton_);
    buttonsLayout->addWidget(findPairsButton_);
    buttonsLayout->addWidget(sortMalesButton_);
    buttonsLayout->addWidget(sortFemalesButton_);
    buttonsLayout->addWidget(searchMatchesButton_);
    buttonsLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->addLayout(grid);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(outputText_);

    setWindowTitle("Электронная Сваха - Пример");
    resize(1000, 400);
}

MainWindow::~MainWindow() {}

void MainWindow::onLoadClicked() {
    QString fileName =
        QFileDialog::getOpenFileName(this, "Выберите файл для загрузки");
    if (fileName.isEmpty())
        return;

    try {
        manager_.loadFromFile(fileName);
        QMessageBox::information(this, "Загрузка",
                                 "Данные успешно загружены из файла.");
    } catch (const QString& err) {
        QMessageBox::warning(this, "Ошибка", err);
    }
}

void MainWindow::onSaveClicked() {
    QString fileName =
        QFileDialog::getSaveFileName(this, "Выберите файл для сохранения");
    if (fileName.isEmpty())
        return;

    try {
        manager_.saveToFile(fileName);
        QMessageBox::information(this, "Сохранение",
                                 "Данные успешно сохранены в файл.");
    } catch (const QString& err) {
        QMessageBox::warning(this, "Ошибка", err);
    }
}

void MainWindow::onAddClicked() {
    try {
        int newId = parseInt(idEdit_->text());
        QString newSex = sexCombo_->currentText();
        QString newFio = fioEdit_->text();
        int newAge = parseInt(ageEdit_->text());
        int newHeight = parseInt(heightEdit_->text());
        int newWeight = parseInt(weightEdit_->text());
        int newMinAge = parseInt(minAgeEdit_->text());
        int newMaxAge = parseInt(maxAgeEdit_->text());
        int newMinHeight = parseInt(minHeightEdit_->text());
        int newMaxHeight = parseInt(maxHeightEdit_->text());
        int newMinWeight = parseInt(minWeightEdit_->text());
        int newMaxWeight = parseInt(maxWeightEdit_->text());

        Candidate cand(newId, newSex, newFio, newAge, newHeight, newWeight,
                       newMinAge, newMaxAge, newMinHeight, newMaxHeight,
                       newMinWeight, newMaxWeight);

        manager_.addCandidate(cand);
        QMessageBox::information(this, "Добавление",
                                 "Кандидат успешно добавлен.");

    } catch (const QString& err) {
        QMessageBox::warning(this, "Ошибка", err);
    }
}

void MainWindow::onRemoveClicked() {
    try {
        int index = parseInt(idEdit_->text());
        manager_.removeCandidate(index);
        QMessageBox::information(this, "Удаление",
                                 "Кандидат удалён по индексу.");
    } catch (const QString& err) {
        QMessageBox::warning(this, "Ошибка", err);
    }
}

void MainWindow::onEditClicked() {
    try {
        int index = parseInt(idEdit_->text());
        QString newSex = sexCombo_->currentText();
        QString newFio = fioEdit_->text();
        int newAge = parseInt(ageEdit_->text());
        int newHeight = parseInt(heightEdit_->text());
        int newWeight = parseInt(weightEdit_->text());
        int newMinAge = parseInt(minAgeEdit_->text());
        int newMaxAge = parseInt(maxAgeEdit_->text());
        int newMinHeight = parseInt(minHeightEdit_->text());
        int newMaxHeight = parseInt(maxHeightEdit_->text());
        int newMinWeight = parseInt(minWeightEdit_->text());
        int newMaxWeight = parseInt(maxWeightEdit_->text());

        Candidate cand(index, newSex, newFio, newAge, newHeight, newWeight,
                       newMinAge, newMaxAge, newMinHeight, newMaxHeight,
                       newMinWeight, newMaxWeight);

        manager_.editCandidate(index, cand);
        QMessageBox::information(this, "Редактирование",
                                 "Кандидат успешно изменён.");

    } catch (const QString& err) {
        QMessageBox::warning(this, "Ошибка", err);
    }
}

void MainWindow::onViewAllClicked() {
    outputText_->clear();

    const QVector<Candidate>& list = manager_.getCandidates();
    for (int i = 0; i < list.size(); i++) {
        const Candidate& c = list[i];
        QString line = QString(
                           "Index: %1 | ID: %2 | Пол: %3 | ФИО: %4 | Возраст: "
                           "%5 | Рост: %6 | Вес: %7 | "
                           "Диапазон партнёра: возраст[%8-%9], рост[%10-%11], "
                           "вес[%12-%13]")
                           .arg(i)
                           .arg(c.getId())
                           .arg(c.getSex())
                           .arg(c.getFio())
                           .arg(c.getAge())
                           .arg(c.getHeight())
                           .arg(c.getWeight())
                           .arg(c.getMinAge())
                           .arg(c.getMaxAge())
                           .arg(c.getMinHeight())
                           .arg(c.getMaxHeight())
                           .arg(c.getMinWeight())
                           .arg(c.getMaxWeight());

        outputText_->append(line);
    }
}

void MainWindow::onFindPairsClicked() {
    outputText_->clear();
    QList<QPair<int, int>> pairs = manager_.findAllPairs();


    for (const auto& p : pairs) {
        const Candidate& m = manager_.getCandidates()[p.first];
        const Candidate& f = manager_.getCandidates()[p.second];
        QString line = QString(
                           "Пара: (M_index=%1, F_index=%2) => [M: %3, %4 лет] "
                           "& [F: %5, %6 лет]")
                           .arg(p.first)
                           .arg(p.second)
                           .arg(m.getFio())
                           .arg(m.getAge())
                           .arg(f.getFio())
                           .arg(f.getAge());
        outputText_->append(line);
    }
}

void MainWindow::onSortMalesByAgeClicked() {
    QVector<Candidate> maleList;
    for (const Candidate& c : manager_.getCandidates()) {
        if (c.getSex() == "М") {
            maleList.append(c);
        }
    }

    std::sort(maleList.begin(), maleList.end(),
              [](const Candidate& a, const Candidate& b) {
                  return a.getAge() > b.getAge();
              });

    outputText_->clear();


    for (const Candidate& m : maleList) {
        QString line = QString("ID: %1 | %2 | Возраст: %3")
                           .arg(m.getId())
                           .arg(m.getFio())
                           .arg(m.getAge());
        outputText_->append(line);
    }
}

void MainWindow::onSortFemalesByAgeClicked() {
    QVector<Candidate> femaleList;
    for (const Candidate& c : manager_.getCandidates()) {
        if (c.getSex() == "Ж") {
            femaleList.append(c);
        }
    }

    std::sort(femaleList.begin(), femaleList.end(),
              [](const Candidate& a, const Candidate& b) {
                  return a.getAge() > b.getAge();
              });

    outputText_->clear();


    for (const Candidate& f : femaleList) {
        QString line = QString("ID: %1 | %2 | Возраст: %3")
                           .arg(f.getId())
                           .arg(f.getFio())
                           .arg(f.getAge());
        outputText_->append(line);
    }
}

void MainWindow::onSearchMatchesClicked() {
    try {
        int index = parseInt(idEdit_->text());
        QList<int> matches = manager_.findMatchesFor(index);

        outputText_->clear();
        outputText_->append(
            QString("Кандидат %1 совместим со следующими индексами:")
                .arg(index));


        for (int i : matches) {
            const Candidate& other = manager_.getCandidates()[i];
            QString line = QString("Index: %1 | ФИО: %2 | %3 лет")
                               .arg(i)
                               .arg(other.getFio())
                               .arg(other.getAge());
            outputText_->append(line);
        }

    } catch (const QString& err) {
        QMessageBox::warning(this, "Ошибка", err);
    }
}

int MainWindow::parseInt(const QString& text) {
    bool ok;
    int value = text.toInt(&ok);


    if (!ok) {
        throw QString("Ошибка: не удалось преобразовать '%1' в число")
            .arg(text);
    }
    return value;
}
