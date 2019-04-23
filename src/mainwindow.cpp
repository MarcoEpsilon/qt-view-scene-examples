#include <mainwindow.hpp>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <flower.hpp>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent)
{
    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(m_scene,this);
    this->setCentralWidget(m_view);
    this->resize(600,600);
    initScene();
    QRectF rectArray[] = {
        QRectF{0,0,50,50},
        QRectF{0,0,100,100},
        QRectF{0,0,80,80},
        QRectF{0,0,30,30},
        QRectF{0,0,200,200},
        QRectF{0,0,20,20},
        QRectF{0,0,40,40},
        QRectF{0,0,60,60},
        QRectF{0,0,75,75},
        QRectF{0,0,85,85}
    };
    double startX = 0;
    double lastStartX = 0;
    for (int i = 0; i < 9; ++i) {
        Flower* flower = new Flower(rectArray[i]);
        startX += lastStartX + flower->horizontalWidth() / 2;
        lastStartX = flower->horizontalWidth() / 2;
        double y = -flower->branchFarOrigin();
        flower->setPos(startX,y);
        m_scene->addItem(flower);
    }
}

MainWindow::~MainWindow() {

}

void MainWindow::initScene() {
    m_scene->setSceneRect(0,-598,598,598);
}