#include "candidate.h"

/*
 * Реализация методов Candidate.
 */

Candidate::Candidate()
    : id_(0),
      sex_(""),
      fio_(""),
      age_(0),
      height_(0),
      weight_(0),
      min_age_(kMinAge),
      max_age_(kMaxAge),
      min_height_(kMinHeight),
      max_height_(kMaxHeight),
      min_weight_(kMinWeight),
      max_weight_(kMaxWeight) {
    // Пустой конструктор по умолчанию
}

Candidate::Candidate(int id, const QString& sex, const QString& fio, int age,
                     int height, int weight, int min_age, int max_age,
                     int min_height, int max_height, int min_weight,
                     int max_weight)
    : id_(id),
      sex_(sex),
      fio_(fio),
      age_(age),
      height_(height),
      weight_(weight),
      min_age_(min_age),
      max_age_(max_age),
      min_height_(min_height),
      max_height_(max_height),
      min_weight_(min_weight),
      max_weight_(max_weight) {}

// Методы "get"
int Candidate::getId() const {
    return id_;
}
QString Candidate::getSex() const {
    return sex_;
}
QString Candidate::getFio() const {
    return fio_;
}
int Candidate::getAge() const {
    return age_;
}
int Candidate::getHeight() const {
    return height_;
}
int Candidate::getWeight() const {
    return weight_;
}
int Candidate::getMinAge() const {
    return min_age_;
}
int Candidate::getMaxAge() const {
    return max_age_;
}
int Candidate::getMinHeight() const {
    return min_height_;
}
int Candidate::getMaxHeight() const {
    return max_height_;
}
int Candidate::getMinWeight() const {
    return min_weight_;
}
int Candidate::getMaxWeight() const {
    return max_weight_;
}

// Методы "set"
void Candidate::setId(int value) {
    id_ = value;
}
void Candidate::setSex(const QString& value) {
    sex_ = value;
}
void Candidate::setFio(const QString& value) {
    fio_ = value;
}
void Candidate::setAge(int value) {
    age_ = value;
}
void Candidate::setHeight(int value) {
    height_ = value;
}
void Candidate::setWeight(int value) {
    weight_ = value;
}
void Candidate::setMinAge(int value) {
    min_age_ = value;
}
void Candidate::setMaxAge(int value) {
    max_age_ = value;
}
void Candidate::setMinHeight(int value) {
    min_height_ = value;
}
void Candidate::setMaxHeight(int value) {
    max_height_ = value;
}
void Candidate::setMinWeight(int value) {
    min_weight_ = value;
}
void Candidate::setMaxWeight(int value) {
    max_weight_ = value;
}
