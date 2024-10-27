from AlgorithmicMeasurement import *
from ComparisonCounter import *
import functions


def count_compilations(func):
    def wrapper(*args, **kwargs):
        ComparisonCounter.start()
        func(*args, **kwargs)
        count = ComparisonCounter.get_count()
        ComparisonCounter.stop()
        return count

    return wrapper

N = 8106
LENGTH = N // 8 + ((N >> 2) % 10 == 0 if N % 1000 else ((N >> 2) % 10 * (N % 10) + (N >> 1) % 10))

if __name__ == '__main__':
    print(LENGTH)
    algorithmicMeasurement = [
        AlgorithmicMeasurement(functions.linear_search, count_compilations, 'Линейный поиск'),
        AlgorithmicMeasurement(functions.binary_search, count_compilations, 'Бинарный поиск')
    ]

    for alg in algorithmicMeasurement:
        alg.make_measure(LENGTH)
        alg.make_graphs()

    algorithmicMeasurement[1].make_sorted_graphs()
