#include <QApplication>
#include "mainwindow.h"

// Точка входа в приложение.
// Создаём QApplication, затем главное окно и запускаем цикл обработки событий.
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
