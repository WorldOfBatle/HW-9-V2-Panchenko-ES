#include <iostream>
#include <vector>    // для std::vector
#include <cstddef>   // для size_t, ptrdiff_t
#include <fstream>    // + для std::ifstream, std::ofstream
#include <string>     // + для std::string
#include <iomanip>    // + для std::setprecision

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
    int variant = 2; // номер варианта. Метод выбираем как variant % 3

    // 1) читаем размер вектора
    std::cout << "Введите количество элементов: ";
    size_t n;
    std::cin >> n;

    // 2) читаем сами элементы
    std::vector<int> data(n);
    std::cout << "Введите " << n << " целых чисел через пробел:\n";
    for (size_t i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    // 3) выводим исходный вектор
    std::cout << "Исходный вектор: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";

    //4) Выбираем метод сортировки
    switch (variant % 3) {
        case 0: bubbleSort(data, isLess<int>); break;
        case 1: selectionSort(data, isLess<int>); break;
        case 2: insertionSort(data, isLess<int>); break;
    }

    // 5) выводим результат
    std::cout << "Отсортированный вектор: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

// Task 2: Переписать данные файла input.txt в файл output.txt, отсортировав их
void task2() {
    std::cout << "\n--- Task 2 ---\n";
    // 1) подключаем файловые потоки и открываем файлы
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Не удалось открыть input.txt\n";
        return;
    }

    std::ofstream output("output.txt");
    if (!output.is_open()) {
        std::cerr << "Не удалось открыть output.txt\n";
        return;
    }

    // 2) читаем число студентов
    size_t m;
    input >> m;
    if (!input || m == 0) {
        std::cerr << "Некорректное число студентов\n";
        return;
    }

    // 3) описываем структуру и создаём контейнер
    struct Student {
        std::string last, first, patronymic;
        int day, month, year;
        int grades[5];
        double avg;
    };
    std::vector<Student> group(m);

    // 4) считываем каждого студента и считаем средний балл
    for (size_t i = 0; i < m; ++i) {
        auto& s = group[i];
        input
        >> s.last >> s.first >> s.patronymic
        >> s.day >> s.month >> s.year;
        long sum = 0;
        for (int j = 0; j < 5; ++j) {
            input >> s.grades[j];
            sum += s.grades[j];
        }
        s.avg = static_cast<double>(sum) / 5.0;
    }

    // 5) сортируем по возрастанию среднего
    insertionSort(group, [](const Student& a, const Student& b) {
        return a.avg < b.avg;
    });

    // 6) выводим в output.txt: все поля + средний
    for (auto& s : group) {
        output
        << s.last << ' ' << s.first << ' ' << s.patronymic << ' '
        << s.day << ' ' << s.month << ' ' << s.year << ' ';
        for (int j = 0; j < 5; ++j)
        output << s.grades[j] << ' ';
        output << std::fixed << std::setprecision(2) << s.avg
        << "\n";
    }

    std::cout << "Результат записан в output.txt\n";
}

int main() {
    task1();
    task2();
    return 0;
}
