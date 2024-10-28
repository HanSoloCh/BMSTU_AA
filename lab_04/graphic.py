import csv
import matplotlib.pyplot as plt

MES_CSV_FILE = 'data_2.csv'

def read_data_from_file(file_path):
    with open(file_path, mode='r', encoding='utf-8') as file:
        reader = csv.DictReader(file, delimiter='|')
        return list(reader)

def get_mes_data(mes_data):
    threads = []
    threads_1 = []
    threads_2 = []

    for data in mes_data:
        threads.append(int(data['pages']))
        threads_1.append(float(data['1_threads']) / 1000)
        threads_2.append(float(data['16_threads']) / 1000)

    return threads, threads_1, threads_2

if __name__ == '__main__':
    mes_data = read_data_from_file(MES_CSV_FILE)
    threads, time_1, time_2 = get_mes_data(mes_data)
    
    plt.plot(threads, time_1, marker='o', label='1 поток')
    plt.plot(threads, time_2, marker='^', label='16 потоков')
    
    plt.xlabel('Количество страниц')
    plt.ylabel('Время (мс)')
    plt.legend()
    plt.savefig('Figure_2.eps', format='eps')

