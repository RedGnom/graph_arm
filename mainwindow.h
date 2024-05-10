#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph_print.h"
#include <QMouseEvent>
#include "graph.h"
#include "sale_man.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void addVertexClicked(int vertexLabel, QPoint pos);
    void addEdge(int vertexLabel1, int vertexLabel2, int weight);
    void deleteVertexSlot(int vertexLabel);
    void deleteEdgeSlot(int vertexLabel1, int vertexLabel2);
    void changeEdgeWeightSlot(int vertexLabel1, int vertexLabel2, int newWeight);

private slots:
    void on_add_button_clicked();
    void mousePressEvent(QMouseEvent* event);

    void on_add_edge_clicked();

    void on_seller_button_clicked();
    void on_delete_vertex_clicked();
    void on_delete_edge_clicked();
    void on_change_edge_clicked();

private:
    Ui::MainWindow *ui;
    graph_print *graphPrint;
    Graph<int> graph;
    sale_man<int> salesman; //
    bool addVertexMode = false; // Флаг для добавления вершины
    int currentVertexLabel; // Метка текущей вершины
    std::vector<float> vertexPositions;
};
#endif // MAINWINDOW_H
