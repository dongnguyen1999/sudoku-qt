#include "src/widgets/uicell.h"
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QLabel>
#include <QHoverEvent>
#include <QDebug>
#include "src/widgets/styles/cell.h"

int counter = 0;

UICell::UICell(Cell c, UIBoard *papa)
{
    parent = papa;
    cell = c;
    setAttribute(Qt::WA_Hover, true);
    setStyleSheet(CellStyles::common);
    questionIcon = CellStyles::loadQuestionIcon();
    value = new QLabel;
    value->setText(QString("1"));
    value->setStyleSheet(CellStyles::valueText(30, Qt::black));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(value);
    setLayout(layout);
}

//https://stackoverflow.com/questions/55999683/qgridlayout-addwidgetcustomwidget-is-not-working
void UICell::paintEvent(QPaintEvent *) {
//    if (cell.getPosition().x == 0 && cell.getPosition().y == 0)
//    qDebug() << "paintEvent board " << counter++;
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    if (onEditing) {
        setStyleSheet(CellStyles::common);
        showQuestionMark();
    }
}

bool UICell::event(QEvent *e) {
    switch(e->type()) {
        case QEvent::HoverEnter:
            hoverEnter(static_cast<QHoverEvent*>(e));
            return true;
        case QEvent::HoverLeave:
            hoverLeave(static_cast<QHoverEvent*>(e));
            return true;
        default:
//            qDebug() << e->type();
            break;
    }
    return QWidget::event(e);
}

void UICell::timerEvent(QTimerEvent *){
    if (blink) {
        questionMarkMargin = 0.1;
    } else questionMarkMargin = 0.2;
    blink = !blink;
    repaint();
}

void UICell::showQuestionMark() {
    layout()->removeWidget(questionIcon);
    layout()->addWidget(questionIcon);
    layout()->setMargin(questionMarkMargin*size().width());
    if (timerId == NULL_ID) timerId = startTimer(400);
}

void UICell::hoverEnter(QHoverEvent *e) {
    if (parent && !parent->inEditMode() && !onHover) {
        setHover(true);
        parent->highLightRCA(cell, true);
    }
}

void UICell::hoverLeave(QHoverEvent *e) {
    if (parent && !parent->inEditMode() && onHover) {
        setHover(false);
        parent->highLightRCA(cell, false);
    }
}

void UICell::highLight(bool flag) {
    if (!onEditing && onHighLight != flag && !onHover) {
        if (onHighLight) {
            setStyleSheet(CellStyles::common);
        } else setStyleSheet(CellStyles::highLight(hoverColor));
        onHighLight = flag;
        repaint();
    }
}

void UICell::setHover(bool flag) {
    if (!onEditing && onHover != flag) {
        if (onHover) {
            setStyleSheet(CellStyles::common);
        } else setStyleSheet(CellStyles::highLight(Qt::yellow) + CellStyles::hoverBorder);
        onHover = flag;
        repaint();
    }
}

void UICell::mousePressEvent(QMouseEvent *) {
    if (parent && !parent->inEditMode()) {
        parent->turnToEditMode(cell);
        onEditing = true;
        repaint();
    } else if (parent) {
        parent->exitEditMode();
    }
 }

void UICell::exitEditMode() {
    if (onEditing) {
        delete questionIcon;
        questionIcon = CellStyles::loadQuestionIcon();
        onEditing = false;
        killTimer(timerId);
        timerId = NULL_ID;
        repaint();
    }
}
