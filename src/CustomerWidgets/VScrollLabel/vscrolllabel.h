#ifndef VSCROLLLABEL_H
#define VSCROLLLABEL_H

#include <QLabel>
#include <QTimer>
#include <QTimerEvent>
#include <QPainter>
#include <QDebug>

class VScrollLabel : public QLabel
{
    Q_OBJECT
public:
    explicit VScrollLabel(QWidget *parent = 0);
    virtual ~VScrollLabel();

    void setScrollSpeed(int speed);

protected:

public Q_SLOTS:
    void setText(const QString &curText);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void updateRollingState();

private:
    int m_iScrollPixel;
    int m_iScrollSpeed;
    int m_iTopMargin;
    int m_iLeftMargin;
    int m_iTimerId;
    const QString m_cTextMargin;
};

#endif // VSCROLLLABEL_H
