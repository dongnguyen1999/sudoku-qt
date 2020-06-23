#include <QWidget>
#include <QLabel>
#ifndef WIDGET_STYLES_CELL
#define WIDGET_STYLES_CELL
class CellStyles {
public:
    static QString common(){
        return border(Qt::black, 2);
    }
    static QString fixed(){
        return CellStyles::highLight(QColor("#131d60")) +
                    CellStyles::border(Qt::black, 2);
    }

    static QString hover(){
        return CellStyles::border(Qt::black, 2) +
                CellStyles::highLight(QColor("#E9F56F"));
    }

    static QString error(){
        return CellStyles::border(Qt::black, 2) +
                CellStyles::highLight(QColor("#c00000"));
    }

    static QString hoverError(){
        return CellStyles::border(Qt::black, 2) +
                CellStyles::highLight(QColor("#f28383"));
    }

    static QString valid(){
        return CellStyles::border(Qt::black, 2) +
                CellStyles::highLight(QColor("#8ef280"));
    }

    static QString border(QColor color = Qt::black, int width = 3, int radius = 5){
        return QString(
            "border-style: solid;" \
            "border-color: ") + color.name() + QString(";" \
            "border-width: ") + QString::number(width) + QString("px;" \
            "border-radius: ") + QString::number(radius) + QString("px;" \
          );
    }

    static QString highLight(QColor color){
        return QString(
            "background-color: "
        ) + color.name() + QString(";");
    }
    static QString valueText(int size, QColor color){
        return QString("color: ") + color.name() + QString(";" \
           "border-width: 0;" \
           "qproperty-alignment: AlignCenter;" \
           "font-size: ") + QString::number(size) + QString("px;");
    }

    static QWidget* loadQuestionIcon(){
        QWidget* icon = new QWidget;
        icon->setStyleSheet(
            "border-image: url(:/main/src/assets/images/question_mark.png);"
        );
        return icon;
    }

    static QLabel* makeNumberLabel(int n, QColor color = Qt::black, int size = 30){
        QLabel* label = new QLabel;
        label->setText(QString::number(n));
        label->setStyleSheet(valueText(size, color));
        return label;
    }

    static QLabel* makeNumberLabel(int n, QString textStyle){
        QLabel* label = new QLabel;
        label->setText(QString::number(n));
        label->setStyleSheet(textStyle);
        return label;
    }
};
#endif // WIDGET_STYLES_CELL

