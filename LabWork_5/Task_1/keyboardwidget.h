#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>

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
    void ResetKeyboard();
    void SetShiftButtonFromMain();
    void SetCapsButtonFromMain();

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void keyPressed(const QString &text);
private slots:
    void onButtonClicked();
    QPushButton* findButtonByText(const QString &text);
private:
    void SetButton(QPushButton* button);
    void SetShiftButtons(QPushButton *leftShit, QPushButton *rightShift);

    Language language_;
    bool isCapsLockOn;

    QList<QPushButton*> buttons;
    Ui::KeyboardWidget *ui;
};

#endif // KEYBOARDWIDGET_H
