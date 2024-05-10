#ifndef GRAPH_PRINT_H
#define GRAPH_PRINT_H

#include <QOpenGLWidget>
#include <QFont>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QtOpenGL> // For OpenGL function declarations
#include <QOpenGLFunctions>

#include <QGridLayout>

struct EdgeInfo {
    int vertexLabel1;
    int vertexLabel2;
    int weight;
};
class graph_print : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    graph_print(QWidget *parent = nullptr);
    ~graph_print() override{};

    void setGraph(const std::vector<std::string>& vertices, const std::vector<std::vector<int>>& adjMatrix);
    void clearGraph();

protected slots:
    void initializeGL() override;
    void paintGL() override;
    void drawVertex(float x, float y, int vertexLabel);
    void drawEdge(const EdgeInfo& info);


public slots:
    void addVertexClicked(int vertexLabel, QPoint pos);
    void addEdge(int vertexLabel1, int vertexLabel2, int weight);
    void deleteVertexSlot(int vertexLabel);
    void deleteEdgeSlot(int vertexLabel1, int vertexLabel2);
    void changeEdgeWeightSlot(int vertexLabel1, int vertexLabel2, int newWeight);
private:
    std::vector<std::string> vertexLabels;
    std::vector<std::vector<int>> adjacencyMatrix;
    std::vector<EdgeInfo> edges;
};

#endif // GRAPH_PRINT_H
