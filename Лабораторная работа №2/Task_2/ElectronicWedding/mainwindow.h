#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include "candidatemanager.h"

const int kMaxInputLength = 255;

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void onLoadClicked();
    void onSaveClicked();
    void onAddClicked();
    void onRemoveClicked();
    void onEditClicked();
    void onViewAllClicked();
    void onFindPairsClicked();
    void onSortMalesByAgeClicked();
    void onSortFemalesByAgeClicked();
    void onSearchMatchesClicked();

   private:
    QLineEdit* idEdit_;
    QComboBox* sexCombo_;
    QLineEdit* fioEdit_;
    QLineEdit* ageEdit_;
    QLineEdit* heightEdit_;
    QLineEdit* weightEdit_;
    QLineEdit* minAgeEdit_;
    QLineEdit* maxAgeEdit_;
    QLineEdit* minHeightEdit_;
    QLineEdit* maxHeightEdit_;
    QLineEdit* minWeightEdit_;
    QLineEdit* maxWeightEdit_;

    QTextEdit* outputText_;

    QPushButton* loadButton_;
    QPushButton* saveButton_;
    QPushButton* addButton_;
    QPushButton* removeButton_;
    QPushButton* editButton_;
    QPushButton* viewAllButton_;
    QPushButton* findPairsButton_;
    QPushButton* sortMalesButton_;
    QPushButton* sortFemalesButton_;
    QPushButton* searchMatchesButton_;

    CandidateManager manager_;

    int parseInt(const QString& text);
};

#endif	// MAINWINDOW_H
