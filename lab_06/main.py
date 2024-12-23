import matplotlib.pyplot as plt


# Функция для чтения данных из файла
def read_data(filename):
    ants = []
    deviations = []

    with open(filename, 'r') as f:
        for line in f:
            # Пропускаем строки с \\ и \hline
            if '\\' in line or '\\hline' in line:
                continue

            # Разделяем строку на два числа
            parts = line.split('&')
            if len(parts) == 2:
                try:
                    ants.append(int(parts[0].strip()))  # Количество муравьев
                    deviations.append(float(parts[1].strip()))  # Отклонение
                except ValueError:
                    continue  # Пропускаем строки с неправильными данными

    return ants, deviations


# Функция для построения графика
def plot_graph(ants, deviations):
    plt.figure(figsize=(8, 6))
    plt.plot(ants, deviations, marker='o', linestyle='-', color='b', label='Отклонение')

    plt.title('Зависимость отклонения от количества муравьев')
    plt.xlabel('Количество муравьев')
    plt.ylabel('Отклонение')
    plt.grid(True)
    plt.legend()
    plt.show()


# Главная функция
def main():
    filename = 'measure.csv'  # Укажите путь к вашему файлу

    # Чтение данных
    ants, deviations = read_data(filename)

    # Построение графика
    plot_graph(ants, deviations)


if __name__ == '__main__':
    main()
