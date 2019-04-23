#include <flower.hpp>
#include <QPainter>
Flower::Flower(const QRectF& rect) 
    :m_rect(rect)
{

}

Flower::~Flower() {

}

QRectF Flower::boundingRect() const {
    return m_rect;
}
void Flower::setRect(const QRectF& rect) {
    if (rect == m_rect) {
        return;
    }
    m_rect = rect;
    //通知scene
    prepareGeometryChange();
    update();
}
void Flower::paint(QPainter* painter,const QStyleOptionGraphicsItem* style,QWidget* widget) {
    painter->setRenderHint(QPainter::Antialiasing,true);
    //200X200
    m_scale = m_rect.width() / 200.0;
    //画头
    QPainterPath headPath;
    headPath.addEllipse(-m_scale * 60,-m_scale * 60,2 * 60 * m_scale,2 * 60 * m_scale);
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QBrush(Qt::yellow));
    painter->drawPath(headPath);
    m_leftEyePos.setX(-15 * m_scale);
    m_leftEyePos.setY(-15 * m_scale);
    m_rightEyePos.setX(15 * m_scale);
    m_rightEyePos.setY(-15 * m_scale);
    m_eyeWidth = m_eyeHeight = 5 * m_scale;
    painter->setBrush(QBrush(Qt::black));
    painter->drawEllipse(m_leftEyePos,m_eyeWidth,m_eyeHeight);
    painter->drawEllipse(m_rightEyePos,m_eyeWidth,m_eyeHeight);
    //花瓣路径
    painter->setPen(QPen(QColor(Qt::NoPen)));
    painter->setBrush(QBrush(Qt::green));
    QRectF flowerBanRect{-10 * m_scale,-90 * m_scale,20 * m_scale,60 * m_scale};
    QPainterPath flowerPath;
    flowerPath.arcTo(flowerBanRect,0 * 16,360 * 16);
    QPainterPath diffPath = flowerPath - headPath;
    painter->fillPath(diffPath,QBrush(Qt::green));
    painter->save();
    for (int i = 0; i < 12; ++i) {
        painter->rotate(30);
        //防止挡住茎
        if (i == 5) {
            continue;
        }
        painter->fillPath(diffPath,QBrush(Qt::green));
    }
    painter->restore();
    //画嘴
    painter->setBrush(QColor(Qt::magenta));
    QRectF mouthRect{-20 * m_scale,10 * m_scale,40 * m_scale,20 * m_scale};
    painter->drawPie(mouthRect,0,-180 * 16);
    //画茎
    m_branchLength = 100 * m_scale;
    QPointF branchLeftStartPos{-8 * m_scale,58 * m_scale};
    QPainterPath arcPathLeft;
    arcPathLeft.arcTo(branchLeftStartPos.x(),branchLeftStartPos.y(),6 * m_scale,m_branchLength,-90 * 16,90 * 16);
    QPointF branchRightStartPos{2 * m_scale,58 * m_scale};
    QPainterPath arcPathRight;
    arcPathRight.arcTo(branchRightStartPos.x(),branchRightStartPos.y(),6 * m_scale,m_branchLength,-90 * 16,90 * 16);
    QPainterPath branchPath;
    branchPath.addRect(QRectF(QPointF(-5 * m_scale,58 * m_scale),QSizeF(10 * m_scale,m_branchLength)));
    branchPath = branchPath - arcPathLeft - arcPathRight - headPath;
    painter->setPen(QPen(Qt::NoPen));
    painter->setBrush(QBrush(QColor(Qt::green)));
    painter->drawPath(branchPath);
    //绘制叶子
    QPainterPath leafPath;
    leafPath.addEllipse(0,-15 * m_scale,30 * m_scale,60 * m_scale);
    painter->save();
    double branchCoord = 60 * m_scale + m_branchLength;
    painter->translate(15 * m_scale,branchCoord);
    painter->translate(0,-2 * m_branchLength / 3);
    painter->rotate(30);
    painter->drawPath(leafPath);
    painter->translate(-8 * m_scale,m_branchLength / 3);
    painter->rotate(90);
    painter->drawPath(leafPath);
    painter->restore();
}

double Flower::branchFarOrigin() {
    m_scale = m_rect.width() / 200;
    m_branchLength = 100 * m_scale;
    return m_branchLength + 60 * m_scale;
}

double Flower::horizontalWidth() {
    m_scale = m_rect.width() / 200;
    return (120 + 60) * m_scale;
}