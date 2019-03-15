#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>
#include <QObject>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class GameOverDialog: public QDialog
{
    Q_OBJECT
public:
    GameOverDialog();
};

#endif // GAMEOVERDIALOG_H
