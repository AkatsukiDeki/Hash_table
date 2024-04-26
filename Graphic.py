import matplotlib.pyplot as plt

# Заданные значения
table_sizes = [25, 75, 125, 175, 225, 275, 325, 375, 425, 475]
collision_probabilities = [1.84467e+15, 1.84467e+15, 1.84467e+15, 0, 0, 0, 0, 0, 0, 0]

# Создание графика
plt.figure(figsize=(10, 6))
plt.plot(table_sizes, collision_probabilities, marker='o', color='b', linestyle='-', linewidth=2)

# Настройка графика
plt.title('Зависимость вероятности коллизии от размера таблицы')
plt.xlabel('Размер таблицы')
plt.ylabel('Вероятность коллизии')
plt.grid(True)
plt.yscale('log')  # Логарифмическая шкала по оси Y

# Отображение графика
plt.show()