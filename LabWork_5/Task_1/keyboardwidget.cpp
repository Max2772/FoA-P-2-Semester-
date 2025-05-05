#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"

#include "utils.h"
#include <QDebug>

KeyboardWidget::KeyboardWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeyboardWidget)
{
    ui->setupUi(this);

    language_ = English;
    isCapsLockOn = false;

    QList<QPushButton *> buttons = {
        ui->topButton_0, ui->topButton_1, ui->topButton_2, ui->topButton_3,
        ui->topButton_4, ui->topButton_5, ui->topButton_6, ui->topButton_7,
        ui->topButton_8, ui->topButton_9, ui->topButton_10, ui->topButton_11,
        ui->topButton_12,
        ui->symbolButton_1, ui->symbolButton_2, ui->symbolButton_3, ui->symbolButton_4,
        ui->symbolButton_5, ui->symbolButton_6, ui->symbolButton_7, ui->symbolButton_8,
        ui->symbolButton_9, ui->symbolButton_10, ui->symbolButton_11, ui->symbolButton_12,
        ui->symbolButton_13, ui->symbolButton_14, ui->symbolButton_15, ui->symbolButton_16,
        ui->symbolButton_17, ui->symbolButton_18, ui->symbolButton_19, ui->symbolButton_20,
        ui->symbolButton_21, ui->symbolButton_22, ui->symbolButton_23, ui->symbolButton_24,
        ui->symbolButton_25, ui->symbolButton_26, ui->symbolButton_27, ui->symbolButton_28,
        ui->symbolButton_29, ui->symbolButton_30, ui->symbolButton_31, ui->symbolButton_32,
        ui->symbolButton_33, ui->symbolButton_34
    };

    for (QPushButton *button : buttons) {
        connect(button, &QPushButton::clicked, this, &KeyboardWidget::onButtonClicked);
    }
}

KeyboardWidget::~KeyboardWidget()
{
    delete ui;
}

void KeyboardWidget::UpdateKeyboard(Language language)
{
    int size = Keyboards[language][isCapsLockOn].size();
    if(size != 47){
        Utils::ShowErrorEvent(QString("Раскладка клавиатура выбранного языка неверного размера!\n%1 вместо 47").arg(size));
        return;
    }

    language_ = language;
    qDebug() << "Язык изменён на" << getLanguageName(language);

    ui->topButton_0->setText(QString(Keyboards[language][isCapsLockOn][0]));
    ui->topButton_1->setText(QString(Keyboards[language][isCapsLockOn][1]));
    ui->topButton_2->setText(QString(Keyboards[language][isCapsLockOn][2]));
    ui->topButton_3->setText(QString(Keyboards[language][isCapsLockOn][3]));
    ui->topButton_4->setText(QString(Keyboards[language][isCapsLockOn][4]));
    ui->topButton_5->setText(QString(Keyboards[language][isCapsLockOn][5]));
    ui->topButton_6->setText(QString(Keyboards[language][isCapsLockOn][6]));
    ui->topButton_7->setText(QString(Keyboards[language][isCapsLockOn][7]));
    ui->topButton_8->setText(QString(Keyboards[language][isCapsLockOn][8]));
    ui->topButton_9->setText(QString(Keyboards[language][isCapsLockOn][9]));
    ui->topButton_10->setText(QString(Keyboards[language][isCapsLockOn][10]));
    ui->topButton_11->setText(QString(Keyboards[language][isCapsLockOn][11]));
    ui->topButton_12->setText(QString(Keyboards[language][isCapsLockOn][12]));
    ui->symbolButton_1->setText(QString(Keyboards[language][isCapsLockOn][13]));
    ui->symbolButton_2->setText(QString(Keyboards[language][isCapsLockOn][14]));
    ui->symbolButton_3->setText(QString(Keyboards[language][isCapsLockOn][15]));
    ui->symbolButton_4->setText(QString(Keyboards[language][isCapsLockOn][16]));
    ui->symbolButton_5->setText(QString(Keyboards[language][isCapsLockOn][17]));
    ui->symbolButton_6->setText(QString(Keyboards[language][isCapsLockOn][18]));
    ui->symbolButton_7->setText(QString(Keyboards[language][isCapsLockOn][19]));
    ui->symbolButton_8->setText(QString(Keyboards[language][isCapsLockOn][20]));
    ui->symbolButton_9->setText(QString(Keyboards[language][isCapsLockOn][21]));
    ui->symbolButton_10->setText(QString(Keyboards[language][isCapsLockOn][22]));
    ui->symbolButton_11->setText(QString(Keyboards[language][isCapsLockOn][23]));
    ui->symbolButton_12->setText(QString(Keyboards[language][isCapsLockOn][24]));
    ui->symbolButton_13->setText(QString(Keyboards[language][isCapsLockOn][25]));
    ui->symbolButton_14->setText(QString(Keyboards[language][isCapsLockOn][26]));
    ui->symbolButton_15->setText(QString(Keyboards[language][isCapsLockOn][27]));
    ui->symbolButton_16->setText(QString(Keyboards[language][isCapsLockOn][28]));
    ui->symbolButton_17->setText(QString(Keyboards[language][isCapsLockOn][29]));
    ui->symbolButton_18->setText(QString(Keyboards[language][isCapsLockOn][30]));
    ui->symbolButton_19->setText(QString(Keyboards[language][isCapsLockOn][31]));
    ui->symbolButton_20->setText(QString(Keyboards[language][isCapsLockOn][32]));
    ui->symbolButton_21->setText(QString(Keyboards[language][isCapsLockOn][33]));
    ui->symbolButton_22->setText(QString(Keyboards[language][isCapsLockOn][34]));
    ui->symbolButton_23->setText(QString(Keyboards[language][isCapsLockOn][35]));
    ui->symbolButton_24->setText(QString(Keyboards[language][isCapsLockOn][36]));
    ui->symbolButton_25->setText(QString(Keyboards[language][isCapsLockOn][37]));
    ui->symbolButton_26->setText(QString(Keyboards[language][isCapsLockOn][38]));
    ui->symbolButton_27->setText(QString(Keyboards[language][isCapsLockOn][39]));
    ui->symbolButton_28->setText(QString(Keyboards[language][isCapsLockOn][40]));
    ui->symbolButton_29->setText(QString(Keyboards[language][isCapsLockOn][41]));
    ui->symbolButton_30->setText(QString(Keyboards[language][isCapsLockOn][42]));
    ui->symbolButton_31->setText(QString(Keyboards[language][isCapsLockOn][43]));
    ui->symbolButton_32->setText(QString(Keyboards[language][isCapsLockOn][44]));
    ui->symbolButton_33->setText(QString(Keyboards[language][isCapsLockOn][45]));
    ui->symbolButton_34->setText(QString(Keyboards[language][isCapsLockOn][46]));
}

void KeyboardWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {
        isCapsLockOn = true;
        UpdateKeyboard(language_);
    }

    QWidget::keyPressEvent(event);
}

void KeyboardWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift) {
        isCapsLockOn = false;
        UpdateKeyboard(language_);
    }
    QWidget::keyReleaseEvent(event);
}

void KeyboardWidget::onButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        emit keyPressed(button->text());
    }
}
