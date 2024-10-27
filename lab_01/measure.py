import string
import random
import time
import tracemalloc

from func import *


def generate_string(length):
    random_sting = ''.join((random.choice(string.ascii_lowercase)) for i in range(length))
    return random_sting


def get_one_measure_time(func):
    def wrapper(*args, **kwargs):
        start = time.process_time_ns()
        func(*args, **kwargs)
        end = time.process_time_ns()
        return end - start
    return wrapper


def get_time(str1, str2, func, measurements_number):
    avg_time = 0

    for i in range(measurements_number):
        avg_time += get_one_measure_time(func)(str1, str2)

    avg_time = avg_time / measurements_number
    print(avg_time)
    return int(avg_time)


def measure_time(funcs, lens, measurements_number=10):
    times = [[] for _ in range(len(funcs))]

    for length in lens:
        print("Measurements for length", length)
        str1, str2 = generate_string(length), generate_string(length)

        for i, func in enumerate(funcs):
            func_time = get_time(str1, str2, func, measurements_number)

            times[i].append(func_time)

    return times


def get_one_measure_memory(func):
    def wrapper(*args, **kwargs):
        tracemalloc.start()
        func(*args)
        _, peak_memory = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        return peak_memory
    return wrapper


def measure_memory(funcs, lens):
    memory_usage = [[] for _ in range(len(funcs))]

    for length in lens:
        print("Memory measurements for length", length)
        str1, str2 = generate_string(length), generate_string(length)

        for i, func in enumerate(funcs):
            peak_memory = get_one_measure_memory(func)(str1, str2)
            memory_usage[i].append(peak_memory)

    return memory_usage
