#include "vscrolllabel.h"

VScrollLabel::VScrollLabel(QWidget *parent) :
    QLabel(parent),
    m_iScrollPixel(0),
    m_iScrollSpeed(5),
    m_iTopMargin(5),
    m_iLeftMargin(5),
    m_iTimerId(-1),
    m_cTextMargin(QString("    "))
{
}

VScrollLabel::~VScrollLabel()
{

}

void VScrollLabel::setScrollSpeed(int speed)
{
    m_iScrollSpeed = speed;
    repaint();
}

void VScrollLabel::setText(const QString &curText)
{
    QLabel::setText(curText);
    updateRollingState();
}

void VScrollLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect labelRect = rect();
    labelRect.setHeight(labelRect.height() - m_iTopMargin);
    labelRect.setWidth(labelRect.width() - m_iLeftMargin);

    labelRect.setLeft(labelRect.left() - m_iScrollPixel);

    // 若计时器开始则滚动循环显示
    QString curText = text();
    if (m_iTimerId >= 0) {
        curText += m_cTextMargin;
        curText += text();
    }
    painter.drawText(labelRect, Qt::AlignVCenter, curText);
}

void VScrollLabel::timerEvent(QTimerEvent *event)
{
     //  判断是否已经完成一遍循环，完成则恢复起始位置，重新开始循环
    if (event->timerId() == m_iTimerId && isVisible()) {
        m_iScrollPixel += m_iScrollSpeed;

        QFont ft = font();
        QFontMetrics fm(ft);
        int txtWidth = fm.width(text());
        int spaceWidth = fm.width(m_cTextMargin);
        if((txtWidth + spaceWidth) < m_iScrollPixel) {
            m_iScrollPixel = 0;
        }
        repaint();
    }
}

void VScrollLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    updateRollingState();
}

void VScrollLabel::updateRollingState()
{
    QFont ft = font();
    QFontMetrics fm(ft);
    int textWidth = fm.width(text());

    //  若文本内容大于label大小则开启文本框滚动
    if(textWidth > width())
    {
        m_iTimerId = startTimer(100);
    } else {
        if(m_iTimerId >= 0)
        {
            killTimer(m_iTimerId);
            m_iTimerId = -1;
        }
    }
}
