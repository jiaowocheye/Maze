#include "congratsdialog.h"

CongratsDialog::CongratsDialog()
{
    QHBoxLayout *hbox1 = new QHBoxLayout(this);
    hbox1->addWidget(new QLabel("Congrats!!!"));
}
