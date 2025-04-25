#include "filecounter.h"
#include <QDirIterator>
FileCounter::FileCounter() {}

void FileCounter::reset() {
    m_files_ = 0;
    m_dirs_ = 0;
}

void FileCounter::count(const QString& path) {
    reset();
    countRecursive(path);
}


void FileCounter::countRecursive(const QString& path) {
    QDir dir(path);

    // Проверка: существует ли директория и можно ли её прочитать
    if (!dir.exists() || !dir.isReadable()) {
        qWarning() << "Недоступен каталог:" << path;
        return;
    }

    QFileInfoList entries = dir.entryInfoList(
    QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden, QDir::NoSort);

    for (const QFileInfo& entry : entries) {
        if (entry.isDir()) {
            m_dirs_++;
            countRecursive(entry.absoluteFilePath());
        } else if (entry.isFile()) {
            m_files_++;
        }
        // Прочие типы (symbolic links и пр.) можно добавить при необходимости
    }
}

