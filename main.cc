#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "HashTable.h"

int main() {
    // Количество элементов
    size_t group_size = 20;
    // Количество экспериментов
    size_t num_experiments = 100;

    // Размеры хэш-таблиц
    std::vector<size_t> table_sizes = { 25, 75, 125, 175, 225, 275, 325, 375, 425, 475 };

    // Вектор для хранения средних коллизий для каждого размера таблицы
    std::vector<double> avg_collisions(table_sizes.size());

    // Вектор для хранения вероятностей коллизий для каждого размера таблицы
    std::vector<double> collision_probability(table_sizes.size());

    // Создаем генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    // Вычисляем среднее количество коллизий и вероятности коллизий для каждого размера таблицы
    for (size_t i = 0; i < table_sizes.size(); i++) {
        size_t table_size = table_sizes[i];
        size_t total_collisions = 0;

        for (size_t j = 0; j < num_experiments; j++) {
            HashTable<size_t, size_t> hash_table(table_size, gen);
            for (size_t k = 0; k < group_size; k++) {
                hash_table.insert(k, k);
            }
            total_collisions += hash_table.count(0);
        }

        avg_collisions[i] = static_cast<double>(total_collisions) / num_experiments;
        double p = 1.0 - std::exp(-static_cast<double>(group_size) * (group_size - 1) / (2.0 * table_size));
        collision_probability[i] = p;
    }

    // Определяем размер таблицы, при котором вероятность коллизии меньше 50%
    size_t best_table_size = 0;
    for (size_t i = 0; i < table_sizes.size(); i++) {
        if (collision_probability[i] < 0.5) {
            best_table_size = table_sizes[i];
            break;
        }
    }

    // Вывод результатов
    std::cout << "Table size where collision probability is less than 50%: " << best_table_size << std::endl;

    return 0;
}
