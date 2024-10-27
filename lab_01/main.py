import matplotlib.pyplot as plt
import func
from measure import measure_time


def plot_time_graph_scaled(lens, times, funcs, line_style=None):
    colors = ['red', 'green', 'blue'] if len(funcs) else ['green', 'blue']
    for i, func in enumerate(funcs):
        plt.plot(lens, times[i], label=func.__name__,
                 linestyle=line_style[i] if line_style is not None and i < len(line_style) else '-',
                 color=colors[i])

    plt.title("Время выполнения алгоритмов")
    plt.xlabel("Длина строки")
    plt.ylabel("Время (нс)")

    plt.legend()
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    lens = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    funcs = [func.levenstein_recursive, func.levenshtein_memoization, func.damerau_levenshtein]  # Алгоритмы

    times = measure_time(funcs, lens, 10)
    plot_time_graph_scaled(lens, times, funcs, ['-', '--', '-.'])
    plot_time_graph_scaled(lens, times[1:], funcs[1:], ['--', '-.'])

