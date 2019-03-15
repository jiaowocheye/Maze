#include "gameoverdialog.h"

GameOverDialog::GameOverDialog(): QDialog()
{
    QHBoxLayout *hbox1 = new QHBoxLayout(this);
    hbox1->addWidget(new QLabel("Game Over"));
}
