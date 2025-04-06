#include "Hexagonbutton.h"
#include <cmath>

 HexagonButton::HexagonButton(QWidget *parent)
 : QPushButton(parent)
{
    setFixedSize(100, 100);


}
 void HexagonButton::move(int x, int y) {
     QPushButton::move(x, y);
     update(); // 触发重绘确保路径更新
 }

 void HexagonButton::move(const QPoint &pos) {
     move(pos.x(), pos.y());
 }

 void HexagonButton::paintEvent(QPaintEvent *event)
 {
     Q_UNUSED(event);
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);

     // 1. 统一坐标系基准：将原点移动到控件中心
     //painter.translate(width()/2.0, height()/2.0);


// 1. 绘制六边形背景
//     QColor baseColor(Qt::lightGray);
//     if(m_isPressed)
//     {
//         baseColor = baseColor.darker(120);
//     }
//     else if(m_isHovered)
//     {
//         baseColor = baseColor.lighter(110);
//     }

//     painter.fillPath(path, baseColor);

      //painter.fillPath(path, isDown() ? Qt::darkGray : Qt::lightGray);

     QPainterPath path = generateHexagonPath();
     // 2. 绘制图标（居中显示）
     if (!icon().isNull())
     {

        painter.save();
        painter.setClipPath(path);
        QPixmap pix = icon().pixmap(size()).scaled(
                    size(),
                    Qt::IgnoreAspectRatio, // 强制拉伸
                    Qt::SmoothTransformation
                );
        painter.drawPixmap(width()/2.0- pix.width()/2, height()/2.0- pix.height()/2, pix); // 中心对齐
        painter.restore();
     }

      if(m_isPressed)
      {
          painter.fillPath(path, QColor(0, 0, 0, 51)); // 等效rgba(0,0,0,0.2)
      }
      else if(m_isHovered)
      {
        painter.fillPath(path, QColor(255, 255, 255, 76)); // 等效rgba(255,255,255,0.3)
      }




     // 3. 可选文本
     if (!text().isEmpty())
     {
         painter.drawText(rect(), Qt::AlignCenter, text());
     }
  }


 bool HexagonButton::hitButton(const QPoint &pos) const
 {
     QPoint localPos = pos - rect().topLeft(); // 转换为局部坐标
     return generateHexagonPath().contains(localPos);
 }

 QPainterPath HexagonButton::generateHexagonPath() const
 {
     QPainterPath path;
     const int sides = 6;
     const QPointF center(width()/2.0, height()/2.0);
     const qreal radius = qMin(width(), height())/2.0 - 2;

     // 显式设置第一个顶点（正右方向，0弧度）
     path.moveTo(center.x() + radius, center.y());

     for (int i = 0; i < sides; ++i)
     {
         qreal angle = 2 * M_PI * i / sides;
         path.lineTo(center.x() + radius * cos(angle),
                      center.y() + radius * sin(angle));
     }
     path.closeSubpath();
     return path;
 }
