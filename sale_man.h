#ifndef SALE_MAN_H
#define SALE_MAN_H
#include "graph.h"

using namespace std;


template <class T>
class sale_man
{
private:
    Graph<T>& graph;


public:
    int totalDistance;
    sale_man(Graph<T>& graph) : graph(graph) {}
    // Функция для выделения нового узла поиска
    // 'i' - текущий вершинный индекс
    // 'j' - следующий вершинный индекс
    //Вычисление нижней границы стоимости маршрута
    int calculateLowerBound(const Graph<int>& graph, const vector<int>& tour) {
        int minCost = 0;
        int n = graph.GetAmountVerts();

        // Учитываем минимальную стоимость связующего дерева для остальных городов
        vector<bool> visited(n, false);
        for (int i = 0; i < tour.size(); ++i) {
            visited[tour[i]] = true;
        }

        // Используем алгоритм Прима, чтобы найти минимальную стоимость связующего дерева
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                pq.push({ 0, i });
                break;
            }
        }

        while (!pq.empty()) {
            int weight = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            minCost += weight;
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (!visited[v] && graph.GetWeight(u, v) > 0) {
                    pq.push({ graph.GetWeight(u, v), v });
                }
            }
        }

        // Добавляем стоимость возврата в начальный город из последнего города тура
        if (tour.size() > 1) {
            minCost += graph.GetWeight(tour[tour.size() - 1], tour[0]);
        }

        return minCost;
    }


    // Рекурсивная функция ветвей и границ
    void tspBranchAndBound(const Graph<int>& graph, vector<int>& tour, int currPos, int bound, vector<int>& bestTour, int& bestCost) {
        // Проверка посещения всех точек
        if (currPos == graph.GetAmountVerts()) {
            int tourCost = 0;
            for (int i = 0; i < tour.size() - 1; ++i) {
                tourCost += graph.GetWeight(tour[i], tour[i + 1]);
            }
            tourCost += graph.GetWeight(tour[tour.size() - 1], tour[0]);

            // Обновляем лучший маршрут и пройденный путь, если найдено лучшее решение
            if (tourCost < bestCost) {
                bestCost = tourCost;
                bestTour = tour;
                totalDistance = tourCost; // Обновление пройденного пути
            }
            return;
        }

        // Проход непосещенных точек
        for (int i = 0; i < graph.GetAmountVerts(); ++i) {
            if (!count(tour.begin(), tour.end(), i)) {
                // Добавитъ точку в маршрут
                tour.push_back(i);

                // Расчет нижней границы маршрута
                int newBound = calculateLowerBound(graph, tour);

                // Убираем ветвь, если нижняя граница больше текущего лучшего пути
                if (newBound < bestCost) {
                    tspBranchAndBound(graph, tour, currPos + 1, newBound, bestTour, bestCost);
                }

                // Удаление точки
                tour.pop_back();
            }
        }
    }

    // Функция нахождения пути
    vector<int> solveTSP(const Graph<int>& graph) {
        int n = graph.GetAmountVerts();
        vector<int> tour;
        tour.push_back(0); // Старт от 1 города

        int bound = calculateLowerBound(graph, tour);
        int bestCost = INT_MAX;
        vector<int> bestTour;

        tspBranchAndBound(graph, tour, 1, bound, bestTour, bestCost);

        // Расчет пройденного пути, после нахождения лучшего маршрута
        totalDistance = 0;
        for (int i = 0; i < bestTour.size() - 1; ++i) {
            totalDistance += graph.GetWeight(bestTour[i], bestTour[i + 1]);
        }
        totalDistance += graph.GetWeight(bestTour[bestTour.size() - 1], bestTour[0]);


        return bestTour;
    }

};
#endif // SALE_MAN_H
