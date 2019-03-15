#include "gamesettingdialog.h"

GameSettingDialog::GameSettingDialog(): QDialog()
{
    QHBoxLayout *hbox1 = new QHBoxLayout(this);
    QPushButton *ok_pushbutton=new QPushButton(QString("Restart"));
    QLabel *enemy=new QLabel("#Enemy");
    QLabel *healthpack=new QLabel("#HealthPack");
    QLineEdit *enemynr=new QLineEdit();
    QLineEdit *healthpacknr=new QLineEdit();
    hbox1->addWidget(enemy);
    hbox1->addWidget(enemynr);
    hbox1->addWidget(healthpack);
    hbox1->addWidget(healthpacknr);
    hbox1->addWidget(ok_pushbutton);
    connect (ok_pushbutton, SIGNAL(clicked()), this, SLOT(accept()));
}
