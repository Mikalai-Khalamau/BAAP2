#include "candidatemanager.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

CandidateManager::CandidateManager() {}

void CandidateManager::loadFromFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw kFileError + ": Не удалось открыть файл для чтения: " + fileName;
    }

    candidates_.clear();  // Очищаем текущий список

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;  // пропускаем пустые строки

        QStringList parts = line.split(";");
        if (parts.size() < 12) {
            continue;  // Пропускаем строки с ошибками
        }

        bool ok1, ok2, ok3, ok4, ok5, ok6, ok7, ok8, ok9, ok10;
        int id = parts[0].toInt(&ok1);
        QString sex = parts[1];
        QString fio = parts[2];
        int age = parts[3].toInt(&ok2);
        int height = parts[4].toInt(&ok3);
        int weight = parts[5].toInt(&ok4);
        int min_age = parts[6].toInt(&ok5);
        int max_age = parts[7].toInt(&ok6);
        int min_height = parts[8].toInt(&ok7);
        int max_height = parts[9].toInt(&ok8);
        int min_weight = parts[10].toInt(&ok9);
        int max_weight = parts[11].toInt(&ok10);


        if (!ok1 || !ok2 || !ok3 || !ok4 || !ok5 || !ok6 || !ok7 || !ok8 ||
            !ok9 || !ok10) {
            continue;  // Пропускаем строки с ошибками
        }

        Candidate cand(id, sex, fio, age, height, weight, min_age, max_age,
                       min_height, max_height, min_weight, max_weight);
        candidates_.push_back(cand);
    }

    file.close();
}

void CandidateManager::saveToFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw kFileError + ": Не удалось открыть файл для записи: " + fileName;
    }

    QTextStream out(&file);


    for (const Candidate& cand : candidates_) {
        out << cand.getId() << ";" << cand.getSex() << ";" << cand.getFio()
            << ";" << cand.getAge() << ";" << cand.getHeight() << ";"
            << cand.getWeight() << ";" << cand.getMinAge() << ";"
            << cand.getMaxAge() << ";" << cand.getMinHeight() << ";"
            << cand.getMaxHeight() << ";" << cand.getMinWeight() << ";"
            << cand.getMaxWeight() << "\n";
    }

    file.close();
}

void CandidateManager::addCandidate(const Candidate& cand) {
    candidates_.push_back(cand);
}

void CandidateManager::removeCandidate(int index) {
    if (index < 0 || index >= candidates_.size()) {
        throw "Неверный индекс при удалении кандидата";
    }
    candidates_.remove(index);
}

void CandidateManager::editCandidate(int index, const Candidate& newData) {
    if (index < 0 || index >= candidates_.size()) {
        throw "Неверный индекс при редактировании кандидата";
    }
    candidates_[index] = newData;
}

const QVector<Candidate>& CandidateManager::getCandidates() const {
    return candidates_;
}

int CandidateManager::size() const {
    return candidates_.size();
}

void CandidateManager::sortByAgeDescending() {
    std::sort(candidates_.begin(), candidates_.end(),
              [](const Candidate& a, const Candidate& b) {
                  return a.getAge() > b.getAge();
              });
}

QList<QPair<int, int>> CandidateManager::findAllPairs() const {
    QList<QPair<int, int>> result;

    for (int i = 0; i < candidates_.size(); i++) {
        if (candidates_[i].getSex() == "М") {
            for (int j = 0; j < candidates_.size(); j++) {
                if (candidates_[j].getSex() == "Ж") {
                    const Candidate& m = candidates_[i];
                    const Candidate& f = candidates_[j];

                    bool mToF = (m.getAge() >= f.getMinAge() &&
                                 m.getAge() <= f.getMaxAge()) &&
                                (m.getHeight() >= f.getMinHeight() &&
                                 m.getHeight() <= f.getMaxHeight()) &&
                                (m.getWeight() >= f.getMinWeight() &&
                                 m.getWeight() <= f.getMaxWeight());

                    bool fToM = (f.getAge() >= m.getMinAge() &&
                                 f.getAge() <= m.getMaxAge()) &&
                                (f.getHeight() >= m.getMinHeight() &&
                                 f.getHeight() <= m.getMaxHeight()) &&
                                (f.getWeight() >= m.getMinWeight() &&
                                 f.getWeight() <= m.getMaxWeight());


                    if (mToF && fToM) {
                        result.append(qMakePair(i, j));
                    }
                }
            }
        }
    }

    return result;
}

QList<int> CandidateManager::findMatchesFor(int index) const {
    QList<int> result;

    if (index < 0 || index >= candidates_.size()) {
        return result;
    }

    const Candidate& cand = candidates_[index];

    for (int i = 0; i < candidates_.size(); i++) {
        if (i == index)
            continue;

        const Candidate& other = candidates_[i];

        bool candToOther = (cand.getAge() >= other.getMinAge() &&
                            cand.getAge() <= other.getMaxAge()) &&
                           (cand.getHeight() >= other.getMinHeight() &&
                            cand.getHeight() <= other.getMaxHeight()) &&
                           (cand.getWeight() >= other.getMinWeight() &&
                            cand.getWeight() <= other.getMaxWeight());

        bool otherToCand = (other.getAge() >= cand.getMinAge() &&
                            other.getAge() <= cand.getMaxAge()) &&
                           (other.getHeight() >= cand.getMinHeight() &&
                            other.getHeight() <= cand.getMaxHeight()) &&
                           (other.getWeight() >= cand.getMinWeight() &&
                            other.getWeight() <= cand.getMaxWeight());


        if (candToOther && otherToCand) {
            result.append(i);
        }
    }

    return result;
}
