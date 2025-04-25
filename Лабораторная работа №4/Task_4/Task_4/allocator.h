#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>   // для size_t
#include <new>       // для оператора placement new
#include <utility>   // для std::forward

// Шаблонный аллокатор памяти для любого типа T
template<typename T>
class Allocator {
public:
    // Тип, с которым работает аллокатор
    using value_type = T;

    // Конструктор по умолчанию (ничего не делает, просто формальность)
    Allocator() = default;

    // Копирующий конструктор (также ничего не делает, просто стандарт)
    template<class U>
    Allocator(const Allocator<U>&) {}

    // Выделяет "кол-во" элементов типа T и возвращает указатель на первую ячейку
    T* allocate(std::size_t count) {
        // Проверка переполнения
        if (count > max_size()) {
            throw std::bad_alloc();
        }

        // Выделяем память нужного размера (без вызова конструктора!)
        // Используем operator new и приводим указатель к T*
        return reinterpret_cast<T*>(::operator new(count * sizeof(T)));
    }

    // Освобождает ранее выделенную память (без вызова деструктора!)
    void deallocate(T* ptr, std::size_t) {
        // Просто передаём указатель в оператор delete
        ::operator delete(ptr);
    }

    // Возвращает максимальное количество элементов, которые можно выделить
    std::size_t max_size() const noexcept {
        return static_cast<std::size_t>(-1) / sizeof(T);
    }

    // Создаёт объект типа T по адресу ptr с аргументами args...
    template<typename... Args>
    void construct(T* ptr, Args&&... args) {
        // Placement new: создаём объект на уже выделенной памяти
        new(ptr) T(std::forward<Args>(args)...);
    }

    // Вызывает деструктор объекта типа T по адресу ptr
    void destroy(T* ptr) {
        ptr->~T();
    }
};

// Аллокаторы считаются равными, если они одного типа
template<typename T, typename U>
bool operator==(const Allocator<T>&, const Allocator<U>&) {
    return true;
}

template<typename T, typename U>
bool operator!=(const Allocator<T>&, const Allocator<U>&) {
    return false;
}

#endif
