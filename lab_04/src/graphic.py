import csv
import matplotlib.pyplot as plt

MES_CSV_FILE = 'data.csv'

def read_data_from_file(file_path):
    with open(file_path, mode='r', encoding='utf-8') as file:
        reader = csv.DictReader(file, delimiter='|')
        return list(reader)

def get_mes_data(mes_data):
    threads = []
    time = []

    for data in mes_data:
        threads.append(int(data['threads']))
        time.append(float(data['time']))

    return threads, time

if __name__ == '__main__':
    mes_data = read_data_from_file(MES_CSV_FILE)
    threads, time = get_mes_data(mes_data)
    
    plt.plot(threads, time, marker='o')
    
    plt.title('Зависимость времени работы от количества потоков')
    plt.xlabel('Количество потоков')
    plt.ylabel('Время (мс)')
    plt.xticks(threads)
    plt.yticks(time)
    plt.savefig('Figure.eps', format='eps')

