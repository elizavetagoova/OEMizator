#ifndef AUTHFORM_H
#define AUTHFORM_H

#include "oemchecker.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AuthForm; }
QT_END_NAMESPACE

class AuthForm : public QMainWindow
{
    Q_OBJECT

public:
    AuthForm(QWidget *parent = nullptr);
    ~AuthForm();

private slots:
    void on_OKpushButton_clicked();

private:
    Ui::AuthForm *ui;
    Oemchecker m_auth;
};
#endif // AUTHFORM_H
