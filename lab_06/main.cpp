#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include <numeric>
#include <fstream>

using namespace std;

// Константы
double ALPHA = 1.0; // Влияние феромонов
double BETA = 0.5;  // Влияние длины пути
double EVAPORATION_RATE = 0.8; // Коэффициент испарения феромонов
int ITERATIONS = 100;           // Количество итераций

double calculateDistance(const vector<int>& path, const vector<vector<int>>& graph) {
    double distance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        distance += graph[path[i]][path[i + 1]];
    }
    distance += graph[path.back()][path[0]]; // Замыкаем цикл
    return distance;
}

pair<vector<int>, double> bruteForceTSP(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i;

    vector<int> bestCycle;
    double minDistance = numeric_limits<double>::max();

    do {
        double currentDistance = calculateDistance(vertices, graph);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            bestCycle = vertices;
        }
    } while (next_permutation(vertices.begin() + 1, vertices.end()));

    return {bestCycle, minDistance};
}

// Функция для обновления феромонов
void updatePheromones(vector<vector<double>>& pheromones, const vector<int>& bestCycle, double bestDistance) {
    int n = pheromones.size();
    // Испарение феромонов
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            pheromones[i][j] *= (1.0 - EVAPORATION_RATE);
        }
    }

    // Усиление феромонов на ребрах лучшего пути
    for (size_t i = 0; i < bestCycle.size() - 1; ++i) {
        int u = bestCycle[i];
        int v = bestCycle[i + 1];
        pheromones[u][v] += 1.0 / bestDistance;
        pheromones[v][u] += 1.0 / bestDistance; // Граф неориентированный
    }
}

// Функция выбора следующей вершины
int chooseNextCity(int current, const vector<bool>& visited, const vector<vector<double>>& pheromones, const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<double> probabilities(n, 0.0);
    double sum = 0.0;

    // Вычисляем вероятность перехода в каждую вершину
    for (int next = 0; next < n; ++next) {
        if (!visited[next]) {
            probabilities[next] = pow(pheromones[current][next], ALPHA) * pow(1.0 / graph[current][next], BETA);
            sum += probabilities[next];
        }
    }

    // Генерируем случайное число и выбираем вершину
    double randomValue = ((double)rand() / RAND_MAX) * sum;
    double cumulative = 0.0;
    for (int next = 0; next < n; ++next) {
        if (!visited[next]) {
            cumulative += probabilities[next];
            if (cumulative >= randomValue) {
                return next;
            }
        }
    }

    return -1; // Должно быть выбрано раньше
}

// Основная функция муравьиного алгоритма
vector<int> antColonyOptimization(const vector<vector<int>>& graph) {
    size_t n = graph.size();
    vector<vector<double>> pheromones(n, vector<double>(n, 1.0)); // Начальные феромоны
    vector<int> bestCycle;      // Лучший цикл
    double bestDistance = numeric_limits<double>::max(); // Длина лучшего цикла

    srand(time(0));

    for (int iter = 0; iter < ITERATIONS; ++iter) {
        for (size_t start = 0; start < n; ++start) { // Каждый муравей начинает с разных городов
            vector<bool> visited(n, false);
            vector<int> cycle;
            int current = start;
            cycle.push_back(current);
            visited[current] = true;

            // Построение пути
            while (cycle.size() < n) {
                int next = chooseNextCity(current, visited, pheromones, graph);
                if (next == -1) break;
                cycle.push_back(next);
                visited[next] = true;
                current = next;
            }

            // Замыкаем цикл
            if (cycle.size() == n & graph[cycle.back()][cycle[0]] > 0) {
                cycle.push_back(cycle[0]);
                double distance = calculateDistance(cycle, graph);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestCycle = cycle;
                }
            }
        }

        // Обновление феромонов
        if (!bestCycle.empty()) {
            updatePheromones(pheromones, bestCycle, bestDistance);
        }
    }

    return bestCycle;
}

void runExperiment(const vector<vector<vector<int>>>& graphs) {
    ofstream f("measure.log");

    vector<int> answers;
    for (const auto &graph : graphs) {
        auto [_, exactDistance] = bruteForceTSP(graph);
        answers.push_back(exactDistance);
        cout << exactDistance << " s";
    }

    vector<double> alphas = {0.10, 0.25, 0.5, 0.75, 0.9};
    vector<double> evaporationRates = {0.1, 0.25, 0.5, 0.75, 0.9};
    vector<int> days = {10, 20, 50, 100, 200};

    for (double alpha : alphas) {
        for (double evaporation : evaporationRates) {
            for (int daysCount : days) {
                ALPHA = alpha;
                EVAPORATION_RATE = evaporation;
                ITERATIONS = daysCount;
                f << alpha << " & " << evaporation << " & " << daysCount << " & ";
                for (size_t i = 0; i < graphs.size(); ++i) {
                    auto graph = graphs[i];

                    vector<double> deviations;

                    for (int count = 0; count < 10; ++count) {
                        auto cycle = antColonyOptimization(graph);
                        double distance = calculateDistance(cycle, graph);
                        double deviation = distance - answers[i];
                        deviations.push_back(deviation);
                        // cout << deviation << " ";
                    }

                    double minDeviation = *min_element(deviations.begin(), deviations.end());
                    // f << minDeviation << "\n";
                    double maxDeviation = *max_element(deviations.begin(), deviations.end());
                    // cout << maxDeviation << "\n";
                    double avgDeviation = accumulate(deviations.begin(), deviations.end(), 0.0) / deviations.size();
                    if (i == graphs.size() - 1)
                        f << minDeviation << " & " << maxDeviation << " & " << avgDeviation;
                    else
                        f << minDeviation << " & " << maxDeviation << " & " << avgDeviation << " & ";
                }
                f << " \\\\ \n";
            }
            f << "\\hline \n";
        }
    }
    f.close();
}

int main() {
    // Матрица смежности графа (с весами рёбер)
    vector<vector<int>> graph1 = {
        {0, 23, 36, 67, 21, 20, 90, 48, 34, 53},
        {23, 0, 2, 17, 38, 67, 36, 42, 47, 48},
        {36, 2, 0, 16, 39, 46, 35, 41, 47, 72},
        {67, 17, 16, 0, 38, 41, 19, 29, 34, 56},
        {21, 38, 39, 38, 0, 5, 38, 17, 13, 31},
        {20, 67, 46, 41, 5, 0, 46, 24, 16, 33},
        {90, 36, 35, 19, 38, 46, 0, 24, 27, 40},
        {48, 42, 41, 29, 17, 24, 24, 0, 5, 31},
        {34, 31, 47, 34, 13, 16, 27, 5, 0, 18},
        {53, 48, 72, 56, 31, 33, 40, 31, 18, 0}
    };

    vector<vector<int>> graph2 = {
        {0, 4, 10, 10, 18, 14, 18, 15, 18, 20},
        {4, 0, 4, 8, 12, 14, 19, 13, 16, 18},
        {10, 4, 0, 8, 10, 14, 18, 12, 14, 16},
        {10, 8, 8, 0, 18, 7, 19, 12, 15, 18},
        {15, 12, 10, 18, 0, 18, 20, 10, 12, 15},
        {14, 14, 14, 7, 18, 0, 4, 6, 7, 8},
        {18, 19, 18, 10, 20, 4, 0, 8, 8, 8},
        {15, 13, 12, 12, 10, 6, 8, 0, 4, 6},
        {18, 16, 14, 15, 12, 7, 8, 4, 0, 4},
        {20, 18, 16, 18, 15, 8, 7, 6, 4, 0}
    };

    vector<vector<int>> graph3 = {
        {0, 21, 34, 45, 56, 67, 78, 89, 90, 101},
        {21, 0, 11, 22, 33, 44, 55, 66, 77, 88},
        {34, 11, 0, 13, 24, 35, 46, 57, 68, 79},
        {45, 22, 13, 0, 15, 26, 37, 48, 59, 70},
        {56, 33, 24, 15, 0, 17, 28, 39, 50, 61},
        {67, 44, 35, 26, 17, 0, 11, 22, 33, 44},
        {78, 55, 46, 37, 28, 11, 0, 13, 24, 35},
        {89, 66, 57, 48, 39, 22, 13, 0, 11, 22},
        {90, 77, 68, 59, 50, 33, 24, 11, 0, 13},
        {101, 88, 79, 70, 61, 44, 35, 22, 13, 0}
    };

    vector<vector<vector<int>>> graphs = {graph1, graph2, graph3};

    runExperiment(graphs);
    return 0;
}
