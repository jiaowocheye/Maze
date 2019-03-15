#include "noenemydialog.h"

NoEnemyDialog::NoEnemyDialog(): QDialog()
{
    QHBoxLayout *hbox1 = new QHBoxLayout();
    hbox1->addWidget(new QLabel("Cannot find enemies!!!"));
}
