#include "keyboardwidget.h"
#include "ui_keyboardwidget.h"

KeyboardWidget::KeyboardWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeyboardWidget)
{
    ui->setupUi(this);
}

KeyboardWidget::~KeyboardWidget()
{
    delete ui;
}
