#ifndef MAINWINDOW_HPP__
#define MAINWINDOW_HPP__
#include <QMainWindow>
class QGraphicsView;
class QGraphicsScene;
class MainWindow:public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private:
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
private:
    void initScene();
};
#endif /*MAINWINDOW_HPP__*/