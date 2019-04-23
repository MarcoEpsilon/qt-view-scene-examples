#ifndef __FLOWER_HPP__
#define __FLOWER_HPP__
#include <QGraphicsItem>
class Flower :public QGraphicsItem {
public:
    Flower(const QRectF& rect = QRectF(-100,-100,200,200));
    ~Flower();
    double branchFarOrigin();
    double horizontalWidth();
private:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter,const QStyleOptionGraphicsItem* style,QWidget* widget) override;
    void setRect(const QRectF& rect);
private:
    double m_scale;
    QRectF m_rect;
    //eyes middle pos
    QPointF m_leftEyePos;
    QPointF m_rightEyePos;
    double m_eyeWidth;
    double m_eyeHeight;
    double m_branchLength;
};
#endif /*__FLOWER_HPP__*/