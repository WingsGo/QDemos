#include "vscrolllabel.h"

VScrollLabel::VScrollLabel(QWidget *parent) :
    QLabel(parent),
    m_iFontSize(11),
    m_iScrollPixel(0),
    m_iScrollSpeed(5),
    m_iTopMargin(2),
    m_iLeftMargin(2),
    m_iTimerId(-1),
    m_cMarginText(QString("    ")),
    m_eDirection(FROMRIGHTTOLEFT)
{
    setText("VScroll Label");
}

VScrollLabel::~VScrollLabel()
{

}

void VScrollLabel::setScrollSpeed(int speed)
{
    m_iScrollSpeed = speed;
    repaint();
}

void VScrollLabel::setScrollDirection(VScrollLabel::ScrollDirection direction)
{
    m_eDirection = direction;
    setText(text());
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

    QFont ft = font();
    ft.setPointSize(m_iFontSize);
    painter.setFont(ft);

    if (m_eDirection == FROMRIGHTTOLEFT) {
        labelRect.setLeft(labelRect.left() - m_iScrollPixel);
    }
    if (m_eDirection == FROMLEFTTORIGHT) {
        QFontMetrics fm(ft);
        int txtWidth = fm.width(text());
        int spaceWidth = fm.width(m_cMarginText);
        labelRect.setLeft(labelRect.left() - txtWidth - spaceWidth + m_iScrollPixel);
    }

    // 若计时器开始则滚动循环显示
    QString curText = text();
    if (m_iTimerId >= 0) {
        curText += m_cMarginText;
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
        ft.setPointSize(m_iFontSize);
        QFontMetrics fm(ft);
        int txtWidth = fm.width(text());
        int spaceWidth = fm.width(m_cMarginText);
        if((txtWidth + spaceWidth) < m_iScrollPixel) {
            m_iScrollPixel = 0;
        }
        repaint();
    }
    QLabel::timerEvent(event);
}

void VScrollLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    updateRollingState();
}

void VScrollLabel::updateRollingState()
{
    QFont ft = font();
    ft.setPointSize(m_iFontSize);
    QFontMetrics fm(ft);
    int textWidth = fm.width(text());

    m_iScrollPixel = 0;
    //  若文本内容大于label大小则开启文本框滚动
    if(textWidth > width())
    {
        m_iTimerId = startTimer(100);
    } else {
        if(m_iTimerId >= 0) {
            killTimer(m_iTimerId);
            m_iTimerId = -1;
        }
    }
}
