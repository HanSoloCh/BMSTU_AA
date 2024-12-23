import csv
import matplotlib.pyplot as plt

MES_CSV_FILE = 'measure.csv'

def read_data_from_file(file_path):
    with open(file_path, mode='r', encoding='utf-8') as file:
        reader = csv.DictReader(file, delimiter='|')
        return list(reader)

def get_mes_data(mes_data):
    threads = []
    threads_1 = []

    for data in mes_data:
        threads.append(int(data['ants']))
        threads_1.append(int(data['delta']))

    return threads, threads_1

if __name__ == '__main__':
    mes_data = read_data_from_file(MES_CSV_FILE)
    threads, time_1 = get_mes_data(mes_data)
    
    plt.plot(threads, time_1)

    plt.xlabel('Количество муравьев')
    plt.ylabel('Отклонение')
    plt.savefig('Figure_2.png', format='png')

