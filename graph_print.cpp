#include "graph_print.h"
#include <QPainter>
struct VertexInfo {
    float x;
    float y;
    int vertexLabel;
};

std::vector<VertexInfo> vertices;



graph_print::graph_print(QWidget *parent) : QOpenGLWidget(parent)
{

}
void graph_print::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(166.0f / 255.0f, 202.0f / 255.0f, 240.0f / 255.0f, 1.0f);

}

void graph_print::paintGL() {
    for (const VertexInfo& vertex : vertices) {
        drawVertex(vertex.x, vertex.y, vertex.vertexLabel);
    }
    for (const EdgeInfo& edge : edges) {
        drawEdge(edge);
    }
}


void graph_print::addVertexClicked(int vertexLabel, QPoint clickPos) {
    // Конвертирование в координаты виджета
    float x = (float)clickPos.x();
    float y = (float)clickPos.y();
    drawVertex(x, y, vertexLabel);

    // Создание вершины
    VertexInfo info;
    info.x = x;
    info.y = y;
    info.vertexLabel = vertexLabel;
    vertices.push_back(info);

    update();
}

void graph_print::drawVertex(float x, float y, int vertexLabel) {
    // Подготовка к отрисовке
    QPainter painter;
    painter.begin(this); // Указать виджет для рисования

    // Отрисовка круга
    painter.setPen(QPen(Qt::white)); // Белый цвет
    painter.setBrush(QBrush(Qt::white)); // Белый цвет заливки
    float radius = 30.0f; // Радиус круга
    QRectF rect(x - radius, y - radius, radius * 2, radius * 2);
    painter.drawEllipse(rect);

    // Отрисовка номера вершины
    painter.setPen(QPen(Qt::black)); // Черный цвет текста
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(rect, Qt::AlignCenter, QString::number(vertexLabel)); // Текст по центру

    // Завершение отрисовки
    painter.end();
}
void graph_print::addEdge(int vertexLabel1, int vertexLabel2, int weight) {
    // Новая грань
    EdgeInfo info;
    info.vertexLabel1 = vertexLabel1;
    info.vertexLabel2 = vertexLabel2;
    info.weight = weight;
    edges.push_back(info);

    update();
}

void graph_print::drawEdge(const EdgeInfo& info) {
    // Find the vertices in the vertices vector
    VertexInfo* vertex1 = nullptr;
    VertexInfo* vertex2 = nullptr;
    for (VertexInfo& vertex : vertices) {
        if (vertex.vertexLabel == info.vertexLabel1) {
            vertex1 = &vertex;
        }
        if (vertex.vertexLabel == info.vertexLabel2) {
            vertex2 = &vertex;
        }
    }
    // Если две вершины найдены
    if (vertex1 && vertex2) {
        // Подготовка к отрисовке
        QPainter painter;
        painter.begin(this); // Указать виджет для рисования

        // Отрисовка линии
        painter.setPen(QPen(Qt::black)); // Черный цвет
        painter.drawLine(vertex1->x, vertex1->y, vertex2->x, vertex2->y);

        // Отрисовка веса грани
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        float midX = (vertex1->x + vertex2->x) / 2;
        float midY = (vertex1->y + vertex2->y) / 2;
        painter.drawText(midX, midY, QString::number(info.weight)); // Текст по центру

        // Завершение отрисовки
        painter.end();
    }
}
void graph_print::deleteVertexSlot(int vertexLabel) {
    // Найти и удалить вершину из списка вершин
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->vertexLabel == vertexLabel) {
            vertices.erase(it);
            break;
        }
    }

    // Найти и удалить все грани, связанные с этой вершиной
    for (auto it = edges.begin(); it != edges.end(); ) {
        if (it->vertexLabel1 == vertexLabel || it->vertexLabel2 == vertexLabel) {
            it = edges.erase(it);
        } else {
            ++it;
        }
    }

    // Вызвать перерисовку
    repaint();
}

void graph_print::deleteEdgeSlot(int vertexLabel1, int vertexLabel2) {
    // Найти и удалить грань из списка граней
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if ((it->vertexLabel1 == vertexLabel1 && it->vertexLabel2 == vertexLabel2) ||
            (it->vertexLabel1 == vertexLabel2 && it->vertexLabel2 == vertexLabel1)) {
            edges.erase(it);
            break;
        }
    }

    // Вызвать перерисовку
    repaint();
}

void graph_print::changeEdgeWeightSlot(int vertexLabel1, int vertexLabel2, int newWeight) {
    // Найти и изменить вес грани
    for (auto& edge : edges) {
        if ((edge.vertexLabel1 == vertexLabel1 && edge.vertexLabel2 == vertexLabel2) ||
            (edge.vertexLabel1 == vertexLabel2 && edge.vertexLabel2 == vertexLabel1)) {
            edge.weight = newWeight;
            break;
        }
    }

    // Вызвать перерисовку
    repaint();
}



