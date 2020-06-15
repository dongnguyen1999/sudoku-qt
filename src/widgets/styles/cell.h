#ifndef STYLES_CELL
#define STYLES_CELL
class CellStyles {
public:
    static const QString common;
    static const QString hoverBorder;
    static QString highLight(QColor);
    static QString valueText(int, QColor);
    static QWidget* loadQuestionIcon();
};

const QString CellStyles::common = QString(
    "border-style: solid;" \
    "border-color: black;" \
    "border-width: 2px;" \
    "border-radius: 5px;"
  );

const QString CellStyles::hoverBorder  = QString(
    "border-style: solid;" \
    "border-color: #131d60;" \
    "border-width: 3px;" \
    "border-radius: 5px;"
  );

QString CellStyles::highLight(QColor color){
    return QString(
        "border-style: solid;" \
        "border-color: black;" \
        "border-width: 2px;" \
        "border-radius: 5px;" \
        "background-color: "
    ) + color.name() + QString(";");
}

QString CellStyles::valueText(int size, QColor color) {
    return QString("color: ") + color.name() + QString(";" \
       "border-width: 0;" \
       "margin: 3px;" \
       "qproperty-alignment: AlignCenter;" \
       "font-size: ") + QString::number(size) + QString("px;");
}

QWidget* CellStyles::loadQuestionIcon() {
    QWidget* icon = new QWidget;
    icon->setStyleSheet(
        "border-image: url(:/main/src/assets/images/question_mark.png);"
    );
    return icon;
}

#endif
