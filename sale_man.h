#ifndef SALE_MAN_H
#define SALE_MAN_H
#include "graph.h"
#include <QDebug>
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
    int calculateLowerBound(const Graph<int>& graph, const vector<int>& tour) {
        int minCost = 0;
        int n = graph.GetAmountVerts();

        // Consider minimum spanning tree cost for remaining cities
        vector<bool> visited(n, false);
        for (int i = 0; i < tour.size(); ++i) {
            visited[tour[i]] = true;
        }

        // Use Prim's algorithm to find minimum spanning tree cost
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                pq.push({0, i});
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
                    pq.push({graph.GetWeight(u, v), v});
                }
            }
        }

        // Add cost of returning to starting city from the last city in the tour
        if (tour.size() > 1) {
            minCost += graph.GetWeight(tour[tour.size() - 1], tour[0]);
        }

        return minCost;
    }


    // Recursive Branch-and-Bound function
    void tspBranchAndBound(const Graph<int>& graph, vector<int>& tour, int currPos, int bound, vector<int>& bestTour, int& bestCost) {
        // If all cities are visited
        if (currPos == graph.GetAmountVerts()) {
            int tourCost = 0;
            for (int i = 0; i < tour.size() - 1; ++i) {
                tourCost += graph.GetWeight(tour[i], tour[i + 1]);
            }
            tourCost += graph.GetWeight(tour[tour.size() - 1], tour[0]);

            // Update best tour and total distance if a better solution is found
            if (tourCost < bestCost) {
                bestCost = tourCost;
                bestTour = tour;
                totalDistance = tourCost; // Update total distance here
            }
            return;
        }

        // Loop through unvisited cities
        for (int i = 0; i < graph.GetAmountVerts(); ++i) {
            if (!count(tour.begin(), tour.end(), i)) {
                // Add city to the tour
                tour.push_back(i);

                // Calculate lower bound for the extended tour
                int newBound = calculateLowerBound(graph, tour);

                // Prune branch if lower bound is greater than current best cost
                if (newBound < bestCost) {
                    tspBranchAndBound(graph, tour, currPos + 1, newBound, bestTour, bestCost);
                }

                // Remove city from the tour for backtracking
                tour.pop_back();
            }
        }
    }

    // Function to solve TSP using Branch-and-Bound
    vector<int> solveTSP(const Graph<int>& graph) {
        int n = graph.GetAmountVerts();
        vector<int> tour;
        tour.push_back(0); // Start from the first city

        int bound = calculateLowerBound(graph, tour);
        int bestCost = INT_MAX;
        vector<int> bestTour;

        tspBranchAndBound(graph, tour, 1, bound, bestTour, bestCost);

        // Calculate total distance after finding the best tour
        totalDistance = 0;
        for (int i = 0; i < bestTour.size() - 1; ++i) {
            totalDistance += graph.GetWeight(bestTour[i], bestTour[i + 1]);
        }
        totalDistance += graph.GetWeight(bestTour[bestTour.size() - 1], bestTour[0]); // Add distance from last to first city

        // Return the best tour (consider returning both tour and totalDistance if needed)
        return bestTour;
    }

};
#endif // SALE_MAN_H
