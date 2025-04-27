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

// Task 1: Написать шаблонную функцию сортировки вектора
void task1() {
    std::cout << "\n--- Task 1 ---\n";
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
