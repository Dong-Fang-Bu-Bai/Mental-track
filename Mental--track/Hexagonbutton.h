#ifndef HEXAGONBUTTON_H
#define HEXAGONBUTTON_H

#include <QPushButton>
#include <QPainter>

class HexagonButton :public QPushButton
{
public:
    explicit HexagonButton(QWidget *parent = nullptr);
    void move(int x, int y);
    void move(const QPoint &pos);

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override;
    // 确保点击区域限制在六边形内
    bool hitButton(const QPoint &pos) const override;

    void enterEvent(QEvent*) override
    {
        m_isHovered = true;
        update(); // 触发重绘
    }
    void leaveEvent(QEvent*) override
    {
        m_isHovered = false;
        update();
    }
    void mousePressEvent(QMouseEvent*event) override
    {
        m_isPressed = true;
        update();
        QPushButton::mousePressEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent*event) override
    {
        m_isPressed = false;
        update();
        QPushButton::mouseReleaseEvent(event); // 确保父类处理信号发射
    }

private:
    bool m_isHovered = false;
    bool m_isPressed = false;

    // 生成六边形路径
    QPainterPath generateHexagonPath() const;
};

#endif // HEXAGONBUTTON_H
