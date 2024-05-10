#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
template <class T>
struct Vertex {
    T number; // Vertex number (unique identifier)
    float x, y; // Vertex position (in your coordinate system)
};
template <class T>
class Graph
{
private:
    // Vector of vertices
    vector<T> vertexList;
    vector<int> labelList;
    vector<vector<pair<T, int>>> adjList;
    // Adjacency matrix
    vector<vector<int>> adjMatrix;
    queue<T> VertsQueue;
    // Maximum size of the vertex vector and adjacency matrix
    int maxSize;

public:
    vector<vector<int>> getAdjMatrix() const {
        return adjMatrix;
    }
    vector<T> getVertexList() const {
        return vertexList;
    }
    // Constructor initializes the graph with a given size
    Graph(const int& size)
    {
        this->maxSize = size;
        this->adjMatrix = vector<vector<int>>(size, vector<int>(size));
        for (int i = 0; i < this->maxSize; ++i)
        {
            for (int j = 0; j < this->maxSize; ++j)
            {
                this->adjMatrix[i][j] = 0;
            }
        }
    }
    bool isFull() {
        return this->vertexList.size() == this->maxSize;
    }
    bool isEmpty() {
        return this->vertexList.size() == 0;
    }
    void insertVertex(const T& vertex)
    {
        if (this->isFull()) {
            cout << "Невозожно добавить" << endl;
            return;
        }
        this->vertexList.push_back(vertex);
    }
    int GetVertPos(const T& vertex) const
    {
        for (int i = 0; i < this->vertexList.size(); ++i)
        {
            if (this->vertexList[i] == vertex)
                return i;
        }
        return -1; // Vertex not found
    }
    int GetAmountVerts() const {
        return this->vertexList.size();
    }
    int GetWeight(const T& v1, const T& v2) const{
        int v1_p = this->GetVertPos(v1);
        int v2_p = this->GetVertPos(v2);

        if (v1_p == -1 || v2_p == -1) {
            std::cout << "Одного из узлов в графе не существует." << std::endl;
            return 0;
        }

        return this->adjMatrix[v1_p][v2_p];
    }
    void DeleteVertex(const T& vertex) {
        int pos = GetVertPos(vertex);
        if (pos != -1) {
            // Remove the vertex from the vertex list
            vertexList.erase(vertexList.begin() + pos);

            // Remove the corresponding row from the adjacency matrix
            adjMatrix.erase(adjMatrix.begin() + pos);

            // Remove the corresponding column from the adjacency matrix
            for (int i = 0; i < adjMatrix.size(); ++i) {
                adjMatrix[i].erase(adjMatrix[i].begin() + pos);
            }
        } else {
            cout << "Вершина не найдена в графе" << endl;
        }
    }

    void DeleteEdge(const T& vertex1, const T& vertex2) {
        int pos1 = GetVertPos(vertex1);
        int pos2 = GetVertPos(vertex2);
        if (pos1 != -1 && pos2 != -1) {
            // Remove the edge from the adjacency matrix
            adjMatrix[pos1][pos2] = 0;
            adjMatrix[pos2][pos1] = 0;
        } else {
            cout << "Одной или обеих вершин нет в графе" << endl;
        }
    }
    void UpdateEdgeWeight(const T& vertex1, const T& vertex2, int newWeight) {
        int pos1 = GetVertPos(vertex1);
        int pos2 = GetVertPos(vertex2);
        if (pos1 != -1 && pos2 != -1) {
            // Обновить вес грани в матрице смежности
            adjMatrix[pos1][pos2] = newWeight;
            adjMatrix[pos2][pos1] = newWeight;
        } else {
            cout << "Одной или обеих вершин нет в графе" << endl;
        }
    }
    vector<T> GetNbrs(const T& vertex) {
        std::vector<T> nbrsList;  // создание списка соседей
        int pos = this->GetVertPos(vertex);  /* вычисление позиции vertex в матрице смежности */
        if (pos != -1) {
            /* проверка, что vertex есть в матрице смежности */
            for (int i = 0; i < this->vertexList.size(); ++i) {
                if (this->adjMatrix[pos][i] != 0) {
                    nbrsList.push_back(this->vertexList[i]);
                }
            }
        }
        return nbrsList;  // возврат списка соседей
    };


    void InsertEdge(const T& vertex1, const T& vertex2, int weight = 1) {
        if (GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
            int vertPos1 = GetVertPos(vertex1);
            int vertPos2 = GetVertPos(vertex2);

            if (this->adjMatrix[vertPos1][vertPos2] != 0 && this->adjMatrix[vertPos2][vertPos1] != 0) {
                cout << "Ребро между вершинами уже есть" << endl;
                return;
            }
            else {
                this->adjMatrix[vertPos1][vertPos2] = weight;
                this->adjMatrix[vertPos2][vertPos1] = weight;
            }
        }
        else {
            cout << "Обеих вершин (или одной из них) нет в графе " << endl;
            return;
        }
    }

    void Print() {
        if (!this->isEmpty()) {
            cout << "Матрица смежности графа: " << endl;
            cout << "- ";
            for (int i = 0; i < vertexList.size(); ++i) {
                cout << vertexList[i] << " ";
            }
            cout << endl;

            for (int i = 0; i < this->vertexList.size(); ++i) {
                cout << this->vertexList[i] << " ";
                for (int j = 0; j < this->vertexList.size(); ++j) {
                    cout << " " << this->adjMatrix[i][j] << " ";
                }
                cout << endl;
            }
        }
        else {
            cout << "Граф пуст" << endl;
        }
    }

    int GetAmountEdges()
    {
        int amount = 0;
        if (!this->IsEmpty())
        {
            for (int i = 0; i < this->vertList.size(); ++i)
            {
                for (int j = 0; j < this->vertList.size(); ++j)
                {
                    if (this->adjMatrix[i][j] != 0)
                    {
                        amount++;
                    }
                }
            }
        }
        return amount / 2;
    }

    void DFS(T& startVertex, bool* visitedVerts)
    {
        cout << "Вершина " << startVertex << " посещена" << endl;
        visitedVerts[this->GetVertPos(startVertex)] = true;
        std::vector<T> neighbors = this->GetNbrs(startVertex);
        for (int i = 0; i < neighbors.size(); ++i)
        {
            if (!visitedVerts[this->GetVertPos(neighbors[i])])
            {
                this->DFS(neighbors[i], visitedVerts);
            }
        }
    }

    void BFS(T& startVertex, bool* visitedVerts) {
        if (visitedVerts[this->GetVertPos(startVertex)] == false) {
            this->VertsQueue.push(startVertex);
            cout << "Вершина " << startVertex << " обработана" << endl;
            visitedVerts[this->GetVertPos(startVertex)] = true;
        }

        std::vector<T> neighbors = this->GetNbrs(startVertex);

        for (int i = 0; i < neighbors.size(); ++i) {
            if (!visitedVerts[this->GetVertPos(neighbors[i])]) {
                this->VertsQueue.push(neighbors[i]);
                visitedVerts[this->GetVertPos(neighbors[i])] = true;
                cout << "Вершина " << neighbors[i] << " обработана" << endl;
            }
        }

        if (this->VertsQueue.empty())
            return;

        T nextVertex = VertsQueue.front();
        VertsQueue.pop();
        BFS(nextVertex, visitedVerts);
    };

    // для Дейкстры
    void Dijkstra(const T& startVertex) {
        int n = this->GetAmountVerts();
        vector<int> dist(n, INT_MAX); // Инициализация расстояний до всех вершин как бесконечности
        vector<bool> visited(n, false); // Инициализация всех вершин как непосещенных
        int startIdx = this->GetVertPos(startVertex); // Получение индекса начальной вершины
        dist[startIdx] = 0; // Расстояние до самого себя равно 0

        for (int i = 0; i < n - 1; ++i) {
            // Находим вершину с минимальным расстоянием от начальной вершины, из еще не посещенных вершин
            int minDist = INT_MAX, minIdx;
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && dist[j] <= minDist) {
                    minDist = dist[j];
                    minIdx = j;
                }
            }

            // Помечаем выбранную вершину как посещенную
            visited[minIdx] = true;

            // Обновляем значение расстояния для всех соседей выбранной вершины
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && this->adjMatrix[minIdx][j] && dist[minIdx] != INT_MAX
                    && dist[minIdx] + this->adjMatrix[minIdx][j] < dist[j]) {
                    dist[j] = dist[minIdx] + this->adjMatrix[minIdx][j];
                }
            }
        }

        // Выводим полученные расстояния от начальной вершины до всех остальных
        cout << "Вершина \tРасстояние от начальной вершины\n";
        for (int i = 0; i < n; ++i) {
            cout << this->vertexList[i] << "\t\t" << dist[i] << "\n";
        }
    }
};

#endif // GRAPH_H
