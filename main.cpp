#include <iostream>
#include <vector>    // для std::vector
#include <cstddef>   // для size_t, ptrdiff_t

// Вспомогательные шаблонные функции для сравнения
template <typename T>
bool isLess(const T& a, const T& b) {
    return a < b;
}

template <typename T>
bool isMore(const T& a, const T& b) {
    return a > b;
}

template <typename T, typename Compare>
bool compare(const T& a, const T& b, Compare cmp) {
    return cmp(a, b);
}

// 1. Пузырьковая сортировка
template <typename T, typename Compare>
void bubbleSort(std::vector<T>& v, Compare cmp) {
    size_t n = v.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (compare(v[j+1], v[j], cmp)) {
                std::swap(v[j], v[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 2. Сортировка выбором
template <typename T, typename Compare>
void selectionSort(std::vector<T>& v, Compare cmp) {
    size_t n = v.size();
    for (size_t i = 0; i < n; ++i) {
        size_t idx = i;
        for (size_t j = i+1; j < n; ++j) {
            if (compare(v[j], v[idx], cmp)) {
                idx = j;
            }
        }
        if (idx != i) std::swap(v[i], v[idx]);
    }
}

// 3. Сортировка вставками
template <typename T, typename Compare>
void insertionSort(std::vector<T>& v, Compare cmp) {
    size_t n = v.size();
    for (size_t i = 1; i < n; ++i) {
        T key = v[i];
        size_t j = i;
        while (j > 0 && compare(key, v[j-1], cmp)) {
            v[j] = v[j-1];
            --j;
        }
        v[j] = key;
    }
}

// Task 1: Написать шаблонную функцию сортировки вектора
void task1() {
    std::cout << "\n--- Task 1 ---\n";
    int variant = 2; // мой вариант

    // Пример данных для демонстрации
    std::vector<int> data = { 5, 2, 9, 1, 5, 6 };

    // Выбираем метод сортировки по правилу variant % 3
    switch (variant % 3) {
        case 0: bubbleSort(data, isLess<int>); break;
        case 1: selectionSort(data, isLess<int>); break;
        case 2: insertionSort(data, isLess<int>); break;
    }

    // Выводим результат
    std::cout << "Отсортированный вектор: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";
}

// Task 2: здесь будет решение второй задачи
void task2() {
    std::cout << "\n--- Task 2 ---\n";
}

int main() {
    task1();
    task2();
    return 0;
}
