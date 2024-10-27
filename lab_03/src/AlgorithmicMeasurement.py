import matplotlib.pyplot as plt


class AlgorithmicMeasurement:
    def __init__(self, func, decorated_function, name="Unknown function"):
        self.__func = decorated_function(func)
        self.__name = name
        self.__data = list()

    def make_measure(self, length):
        lst = list(range(length))
        for item in range(-1, length):
            count = self.__func(lst, item)
            self.__data.append(count)

    def make_graphs(self):
        indices = range(-1, len(self.__data) - 1)
        plt.bar(indices, self.__data)

        plt.xlabel('Искомый элемент')
        plt.ylabel('Количество сравнений')

        # Добавляем заголовок графика
        plt.title(f'{self.__name}')
        plt.savefig(f'{self.__name}.eps', format='eps')

        plt.show()

    def make_sorted_graphs(self):
        indices = range(-1, len(self.__data) - 1)

        sorted_values = sorted(self.__data)

        plt.bar(indices, sorted_values)

        plt.xlabel('Искомый элемент')
        plt.ylabel('Количество сравнений')

        # Добавляем заголовок графика
        plt.title(f'{self.__name} отсортированные гистограмма')
        plt.savefig(f'{self.__name}_sorted.eps', format='eps')

        plt.show()


