#include <iostream>
#include "HashTable.h"



int main() {
    std::vector<size_t> table_sizes = { 25, 75, 125, 175, 225, 275, 325, 375, 425, 475 };
    size_t group_size = 100;

    std::vector<size_t> collisions_count(table_sizes.size(), 0);

    for (size_t i = 0; i < table_sizes.size(); i++) {
        for (size_t j = 0; j < 100; j++) {
            UnorderedMap<int, int> table(table_sizes[i]);
            for (int k = 0; k < group_size; k++) {
                table.insert(k, k);
            }
            collisions_count[i] += table.count() - group_size;
        }
    }

    std::vector<double> collision_probability(table_sizes.size());
    for (size_t i = 0; i < table_sizes.size(); i++) {
        collision_probability[i] = static_cast<double>(collisions_count[i]) / (100 * group_size);
    }

    size_t best_table_size = 0;
    for (size_t i = 0; i < table_sizes.size(); i++) {
        if (collision_probability[i] < 0.5) {
            best_table_size = table_sizes[i];
            break;
        }
    }
    //Размер таблицы, при котором вероятность коллизии меньше 50%
    std::cout << "The size of the table where the probability of a collision is less than 50% " << best_table_size << std::endl;
    for (size_t i = 0; i < table_sizes.size(); i++) {
        //Размер таблицы + Вероятность коллизии
        std::cout << "Table size: " << table_sizes[i] << ", The probability of a collision: " << collision_probability[i] << std::endl;
    }

    return 0;
}