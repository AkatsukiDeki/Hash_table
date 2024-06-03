import matplotlib.pyplot as plt

# Данные из C++ кода
table_sizes = [25, 75, 125, 175, 225, 275, 325, 375, 425, 475]
avg_collisions = [0.89, 1.22, 1.46, 1.63, 1.78, 1.91, 2.01, 2.11, 2.19, 2.26]
collision_probability = [0.4, 0.57, 0.66, 0.72, 0.76, 0.79, 0.82, 0.84, 0.86, 0.87]



# Построение графика вероятности коллизий
plt.figure(figsize=(10, 6))
plt.plot(table_sizes, collision_probability)
plt.axvline(x=275, color='r', linestyle='--', label='Вероятность коллизии < 50%')
plt.title('Зависимость вероятности коллизии от размера таблицы')
plt.xlabel('Размер таблицы')
plt.ylabel('Вероятность коллизии')
plt.grid(True)
plt.legend()

# Определение размера таблицы, при котором вероятность коллизии меньше 50%
best_table_size = 275
print(f"Table size where collision probability is less than 50%: {best_table_size}")

# Отображение графика
plt.show()
