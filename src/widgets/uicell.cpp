#include "src/widgets/uicell.h"
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QEvent>
#include <QLabel>
#include <QHoverEvent>
#include <QDebug>
#include "src/widgets/styles/cell_styles.h"
int counter = 0;

UICell::UICell(Coord pos, UIBoard *papa, int value, bool fixed)
{
    parent = papa;
    position = pos;
    enable = !fixed;
    if (!enable) {
        bodyStyle = CellStyles::fixed();
        textStyle = CellStyles::valueText(30, Qt::white);
    }
    setAttribute(Qt::WA_Hover, true);
    setStyleSheet(bodyStyle);
    questionIcon = CellStyles::loadQuestionIcon();
    valueLabel = CellStyles::makeNumberLabel(value, textStyle);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->SetFixedSize;
    layout->setMargin(3);
    setLayout(layout);
    showValueLabel();
}

//https://stackoverflow.com/questions/55999683/qgridlayout-addwidgetcustomwidget-is-not-working
void UICell::paintEvent(QPaintEvent *) {
//    if (position.x == 0 && position.y == 0)
//    qDebug() << "paintEvent board " << counter++;
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    if (onEditing) {
        if (getValue() != EMPTY && onConflict) {
            setStyleSheet(CellStyles::hoverError());
            valueLabel->setStyleSheet(CellStyles::valueText(30, Qt::black));
        } else if (getValue() != EMPTY && !onConflict) {
            setStyleSheet(CellStyles::valid());
            valueLabel->setStyleSheet(CellStyles::valueText(30, Qt::black));
        }
        else setStyleSheet(CellStyles::hover());
        if (getValue() == EMPTY) showQuestionMark();
    }
}

bool UICell::event(QEvent *e) {
    switch(e->type()) {
        case QEvent::HoverEnter:
            if (!enable) return true;
            hoverEnter(static_cast<QHoverEvent*>(e));
            return true;
        case QEvent::HoverLeave:
            if (!enable) return true;
            hoverLeave(static_cast<QHoverEvent*>(e));
            return true;
        default:
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
    removeValueLabel();
    layout()->addWidget(questionIcon);
    layout()->setMargin(questionMarkMargin*size().width());
    if (timerId == NULL_ID) timerId = startTimer(400);
}

void UICell::hoverEnter(QHoverEvent *e) {
    if (parent && !parent->inEditMode()) {
        parent->highLightRCA(position, true);
    }
}

void UICell::hoverLeave(QHoverEvent *e) {
    if (parent && !parent->inEditMode()) {
        parent->highLightRCA(position, false);
    }
}

void UICell::highLight(bool flag, QString bodyStyle, QString textStyle) {
    if (onHighLight != flag) {
        if (onHighLight) {
            setStyleSheet(this->bodyStyle);
            valueLabel->setStyleSheet(this->textStyle);
        } else {
            setStyleSheet(bodyStyle.length() == 0 ? this->bodyStyle : bodyStyle);
            valueLabel->setStyleSheet(textStyle.length() == 0 ? this->textStyle : textStyle);
        }
        onHighLight = flag;
        repaint();
    }
}

void UICell::mousePressEvent(QMouseEvent *) {
    if (!enable) return;
    if (parent && !parent->inEditMode()) {
        onEditing = true;
        parent->turnToEditMode(position);
        repaint();
    } else if (parent) {
        parent->exitEditMode();
    }
 }

void UICell::exitEditMode() {
    if (onEditing) {
        onEditing = false;
        removeQuestionMark();
        showValueLabel();
        if (timerId != NULL_ID) {
            killTimer(timerId);
            timerId = NULL_ID;
        }
        repaint();
    }
}

int UICell::getValue() {
    if (!valueLabel) return 0;
    return valueLabel->text().toInt();
}

void UICell::setValue(int val) {
    if (getValue() != val) {
//        parent->refresh();
        removeQuestionMark();
        removeValueLabel();
        valueLabel = CellStyles::makeNumberLabel(val);
        showValueLabel();
        if (getValue() == 0) {
            onConflict = false;
            parent->removeConstrains(position);
            bodyStyle = CellStyles::common();
            textStyle = CellStyles::valueText(30, Qt::black);
        }
        else if (checkValue(val)) {
            onConflict = false;
            parent->addConstrains(position);
            bodyStyle = CellStyles::common();
            textStyle = CellStyles::valueText(30, Qt::black);
        }
        else {
            onConflict = true;
            bodyStyle = CellStyles::error();
            textStyle = CellStyles::valueText(30, Qt::white);
        }
//        qDebug() << onConflict;
        setStyleSheet(bodyStyle);
        valueLabel->setStyleSheet(textStyle);
        parent->refresh();
    }
}

void UICell::removeQuestionMark() {
    delete questionIcon;
    questionIcon = CellStyles::loadQuestionIcon();
    layout()->setMargin(3);
}

void UICell::removeValueLabel() {
    int value = getValue();
    delete valueLabel;
    valueLabel = CellStyles::makeNumberLabel(value, textStyle);
}

void UICell::showValueLabel() {
    if (getValue() != EMPTY) {
        layout()->addWidget(valueLabel);
    }
}

bool UICell::isOnConflict() {
    return onConflict;
}

bool UICell::checkValue(int value) {
    vector<int> availables = parent->getAvailables(position);
    for (int i = 0; i < availables.size(); i++) {
        if (availables[i] == value) return true;
    }
    return false;
}

void UICell::refresh() {
    int value = getValue();
    if (value == EMPTY) return;
    if (enable && checkValue(value)) {
        onConflict = false;
        parent->addConstrains(position);        
        bodyStyle = CellStyles::common();
        textStyle = CellStyles::valueText(30, Qt::black);
    }
    else if (enable) {
        onConflict = true;
        bodyStyle = CellStyles::error();
        textStyle = CellStyles::valueText(30, Qt::white);
    }
    if (!onHighLight) {
        setStyleSheet(bodyStyle);
        valueLabel->setStyleSheet(textStyle);
    }
    repaint();
}
