#include <QDebug>
#include <QDir>
#include <QString>
#ifndef FILECOUNTER_H
#define FILECOUNTER_H

class FileCounter {
   public:
    FileCounter();
    void reset();
    int fileCount() const { return m_files_; }
    int dirCount() const { return m_dirs_; }
    void count(const QString& path);

   private:
    int m_files_ = 0;
    int m_dirs_ = 0;
    void countRecursive(const QString& path);
};

#endif	// FILECOUNTER_H
