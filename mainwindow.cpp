#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "sale_man.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    graph(20),
    salesman(graph)


{
    ui->setupUi(this);

    graphPrint = new graph_print(this);
    connect(ui->add_button, &QPushButton::clicked, this, &MainWindow::on_add_button_clicked);
    connect(this, &MainWindow::addVertexClicked, graphPrint, &graph_print::addVertexClicked);
    connect(this, &MainWindow::addEdge, graphPrint, &graph_print::addEdge);
    connect(this, &MainWindow::deleteVertexSlot, graphPrint, &graph_print::deleteVertexSlot);
    connect(this, &MainWindow::deleteEdgeSlot, graphPrint, &graph_print::deleteEdgeSlot);
    connect(this, &MainWindow::changeEdgeWeightSlot, graphPrint, &graph_print::changeEdgeWeightSlot);

    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);

    // Add UI elements to the layout (adjust positions as needed)
    layout->addWidget(ui->add_button, 0, 0);
    layout->addWidget(ui->vert_insert, 0, 1);
    layout->addWidget(ui->delete_vertex, 0, 2);
    layout->addWidget(ui->delete_edge, 0, 3);
    layout->addWidget(ui->change_edge, 0, 4);

    layout->addWidget(ui->vert_text1, 1, 0);
    layout->addWidget(ui->vertex1, 1, 1);
    layout->addWidget(ui->vert_text2, 1, 2);
    layout->addWidget(ui->vertex2, 1, 3);
    layout->addWidget(ui->weight_text, 1, 4);
    layout->addWidget(ui->weight, 1, 5);
    layout->addWidget(ui->add_edge, 1, 6);
    layout->addWidget(ui->seller_button, 1, 7);




    // Add graph visualization widget (graphPrint) to the layout
    layout->addWidget(graphPrint, 2, 0, 1, -1);  // Spans all columns in the second row

    // Set the central widget of the main window
    this->setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphPrint;
}
void MainWindow::on_add_button_clicked() {
    int vertexLabel = ui->vert_insert->text().toInt();

    addVertexMode = true;
    currentVertexLabel = vertexLabel;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (addVertexMode) {
        QPoint pos = event->pos();

        emit addVertexClicked(currentVertexLabel, pos);
        addVertexMode = false;
        graph.insertVertex(currentVertexLabel);

    }
}

void MainWindow::on_add_edge_clicked()
{
    int vertexLabel1 = ui->vertex1->text().toInt();
    int vertexLabel2 = ui->vertex2->text().toInt();
    int weight = ui->weight->text().toInt();
    graph.InsertEdge(vertexLabel1, vertexLabel2, weight);
    emit addEdge(vertexLabel1, vertexLabel2, weight);
}


void MainWindow::on_seller_button_clicked() {
    // ... (existing code for solving TSP) ...

    vector<int> tour = salesman.solveTSP(graph); // Get the best tour

    // Print the tour to debug output
    qDebug() << "Задача коммивояжера:";
    QString output = "";
    for (int i = 0; i < tour.size(); ++i) {
        output += QString::number(tour[i]);
        if (i != tour.size() - 1) {
            output += " -> ";
        }
    }
    if (!tour.empty()) {
        output += " -> " + QString::number(tour[0]);
    }
    qDebug() << output;


    // Access and display total distance from salesman object
    qDebug() << "Пройденный путь:";
    qDebug() << salesman.totalDistance;
    graph.Print();
}

void MainWindow::on_delete_vertex_clicked() {
    int vertexLabel = ui->vert_insert->text().toInt(); // Получить метку вершины от пользователя
    graph.DeleteVertex(vertexLabel);
    emit deleteVertexSlot(vertexLabel);
}

void MainWindow::on_delete_edge_clicked() {
    int vertexLabel1 = ui->vertex1->text().toInt();
    int vertexLabel2 = ui->vertex2->text().toInt();
    graph.DeleteEdge(vertexLabel1, vertexLabel2);
    emit deleteEdgeSlot(vertexLabel1, vertexLabel2);
}

void MainWindow::on_change_edge_clicked() {
    int vertexLabel1 = ui->vertex1->text().toInt();
    int vertexLabel2 = ui->vertex2->text().toInt();
    int newWeight = ui->weight->text().toInt();
    graph.UpdateEdgeWeight(vertexLabel1, vertexLabel2, newWeight);
    emit changeEdgeWeightSlot(vertexLabel1, vertexLabel2, newWeight);
}



