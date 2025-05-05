#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include "constants.h"

namespace Ui {
class KeyboardWidget;
}

class KeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KeyboardWidget(QWidget *parent = nullptr);
    ~KeyboardWidget();

    void UpdateKeyboard(Language language);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Language language_;
    bool isCapsLockOn;

    Ui::KeyboardWidget *ui;
};

#endif // KEYBOARDWIDGET_H
