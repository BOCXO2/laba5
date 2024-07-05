#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "validator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("flower.db");
    if (!db.open()) {
        qDebug() << "Error: " << db.lastError().text();
        // обработка ошибки
        return;}
    else{ qDebug()<<"Поехали!";}
    model= new QSqlTableModel(this,db);// create model
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("200, 160, 200"));
    setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();

}

void MainWindow::on_pushButton_clicked()
{
    QString a;
    if(ui->flowers->isChecked())
    {
        a="flower_table";
    }
    else
    {
        if(ui->composition->isChecked())
        {
            a="composition_table";
        }
        else
        {
            if(ui->fandc->isChecked())
            {
                a="composition_flower_table";
            }
            else
            {
                if(ui->order->isChecked())
                {
                    a="Order_table";
                }
                else
                {
                    if(ui->users->isChecked())
                    {
                        a="User_table";
                    }
                    else
                    {
                        QMessageBox::warning(this,"WARNING","Select table!!!");
                    }
                }
            }
        }
    }
    model->setTable(a);
    model->select();
    ui->tableView->setModel(model);
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery q;
    if(ui->radioButton->isChecked())
    {
        q.prepare("DELETE FROM flowers WHERE id=:id");
    }
    else
    {
        if(ui->radioButton_2->isChecked())
        {
            q.prepare("DELETE FROM Compos WHERE id=:id");
        }
        else
        {
            if(ui->radioButton_3->isChecked())
            {

                q.prepare("DELETE FROM Flower_Compos WHERE id=:id");
            }
            else
            {
                if(ui->radioButton_4->isChecked())
                {

                    q.prepare("DELETE FROM Order WHERE id=:id");
                }
                else
                {
                    if(ui->radioButton_5->isChecked())
                    {
                        q.prepare("DELETE FROM User WHERE id=:id");
                    }
                    else
                    {
                        QMessageBox::warning(this,"WARNING","Select table!!!");
                    }
                }
            }
        }
    }
    QString ent = ui->line_delete->text();
    int s = 0;
    bool ok;
    s = ent.toInt(&ok);
    if (ok) {
        q.bindValue(":id", s);
        if (!q.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << q.lastError();
        } else {
            qDebug() << "Данные успешно удалены из базы данных";
        }
    } else {
        QMessageBox::critical(this, "ОЙ", "PROBLEM");
    }
}


void MainWindow::on_pushButton_4_clicked()
{

    if(ui->radioButton_6->isChecked())
    {
        QLabel *label_3=ui->label_3;
        label_3->setText("Flower name");
        QLabel *label_4=ui->label_4;
        label_4->setText("Varioty");
        QLabel *label_5=ui->label_5;
        label_5->setText("Cost");
    }
    else
    {
        if(ui->radioButton_7->isChecked())
        {
            QLabel *label_3=ui->label_3;
            label_3->setText("Compos. name");
            QLabel *label_4=ui->label_4;
            label_4->setText("Leave is empty");
            QLabel *label_5=ui->label_5;
            label_5->setText("Cost");
        }
        else
        {
            QMessageBox::warning(this,"WARNING","Select table");
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery qu;
    QString nam=ui->line_in1->text();
    QString cos=ui->line_in3->text();
    bool ok;
    int a=0;
    a=cos.toInt(&ok);
    if(ok)
    {
    if(ui->radioButton_6->isChecked())
    {
        qu.prepare("INSERT INTO flowers(name,sort,cost) VALUES(:name,:sort,:cost)");
        QString sort=ui->line_in2->text();
        qu.bindValue(":sort",sort);

    }
    if(ui->radioButton_7->isChecked())
    {
         qu.prepare("INSERT INTO Compos(name, cost) VALUES(:name,:cost)");
    }
    qu.bindValue(":name",nam);
    qu.bindValue(":cost",a);
    if (!qu.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << qu.lastError();
    } else {
        qDebug() << "Данные успешно удалены из базы данных";
    }
    }
    else{ QMessageBox::warning(this,"!!!","Эхх, ввел не число");}
}


void MainWindow::on_pushButton_5_clicked()
{
    if(ui->radioButton_8->isChecked())
    {
        QCheckBox *CheckBox_2=ui->checkBox_2;
        CheckBox_2->setText("Flower name");
        QCheckBox *CheckBox=ui->checkBox;
        CheckBox->setText("Cost");
        QLabel *label_8=ui->label_8;
        label_8->setText("Flower name");
        QLabel *label_10=ui->label_10;
        label_10->setText("Cost");

    }
    else
    {
        if(ui->radioButton_9->isChecked())
        {
            QCheckBox *CheckBox_2=ui->checkBox_2;
            CheckBox_2->setText("Compos. name");
            QCheckBox *CheckBox=ui->checkBox;
            CheckBox->setText("Cost");
            QLabel *label_8=ui->label_8;
            label_8->setText("Compos. name");
            QLabel *label_10=ui->label_10;
            label_10->setText("Cost");
        }
        else{
            if(ui->radioButton_10->isChecked())
            {
                QCheckBox *CheckBox_2=ui->checkBox_2;
                CheckBox_2->setText("Login");
                QCheckBox *CheckBox=ui->checkBox;
                CheckBox->setText("Password");
                QLabel *label_8=ui->label_8;
                label_8->setText("Login");
                QLabel *label_10=ui->label_10;
                label_10->setText("Password");
            }

        else
        {
            QMessageBox::warning(this,"WARNING","Select table!!!");
        }}
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    QSqlQuery upd;
    int f2=0,idn=0;
    bool ok;
    QString id=ui->lineEdit_3->text();
    idn=id.toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(this,"Ты","Введи число");
    }
    if ((ui->checkBox_2->isChecked())&&(ui->checkBox->isChecked()))
    {
        QString nam=ui->line_up1->text();
        QString cos=ui->line_up2->text();
        if(ui->radioButton_8->isChecked())
        {
            f2=cos.toInt(&ok);
            upd.prepare("UPDATE flowers SET name=:name, cost=:cost WHERE id=:id");
            upd.bindValue(":name",nam);
            upd.bindValue(":cost",f2);
            upd.bindValue(":id",idn);

        }
        if(ui->radioButton_9->isChecked())
        {
            f2=cos.toInt(&ok);
            upd.prepare("UPDATE Compos SET name=:name, cost=:cost WHERE id=:id");
            upd.bindValue(":name",nam);
            upd.bindValue(":cost",f2);
             upd.bindValue(":id",idn);
        }
        if(ui->radioButton_10->isChecked())
        {
            upd.prepare("UPDATE User SET login=:login, password=:password WHERE id=:id");
            upd.bindValue(":login",nam);
            upd.bindValue(":password",cos);
            upd.bindValue(":id",idn);
        }
    }
    if ((ui->checkBox_2->isChecked())&&!(ui->checkBox->isChecked()))
    {
        QString nam=ui->line_up1->text();
        if(ui->radioButton_8->isChecked())
        {

            upd.prepare("UPDATE flowers SET name=:name WHERE id=:id");
            upd.bindValue(":name",nam);
            upd.bindValue(":id",idn);

        }
        if(ui->radioButton_9->isChecked())
        {

            upd.prepare("UPDATE Compos SET name=:name WHERE id=:id");
            upd.bindValue(":name",nam);
            upd.bindValue(":id",idn);
        }
        if(ui->radioButton_10->isChecked())
        {
            upd.prepare("UPDATE User SET login=:login WHERE id=:id");
            upd.bindValue(":login",nam);

            upd.bindValue(":id",idn);
        }
    }
    if (!(ui->checkBox_2->isChecked())&&(ui->checkBox->isChecked()))
    {
        QString cos=ui->line_up2->text();
        if(ui->radioButton_8->isChecked())
        {
            f2=cos.toInt(&ok);
            upd.prepare("UPDATE flowers SET cost=:cost WHERE id=:id");
            upd.bindValue(":cost",f2);
            upd.bindValue(":id",idn);

        }
        if(ui->radioButton_9->isChecked())
        {
            f2=cos.toInt(&ok);
            upd.prepare("UPDATE Compos SET cost=:cost WHERE id=:id");

            upd.bindValue(":cost",f2);
            upd.bindValue(":id",idn);
        }
        if(ui->radioButton_10->isChecked())
        {
            upd.prepare("UPDATE User SET password=:password WHERE id=:id");
            upd.bindValue(":password",cos);
            upd.bindValue(":id",idn);
        }
    }
    if (!(ui->checkBox_2->isChecked())&&!(ui->checkBox->isChecked()))
    {
        QMessageBox::warning(this,"Help","Choose field for update");
    }
    if (!upd.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << upd.lastError();
    } else {
        qDebug() << "Данные успешно удалены из базы данных";
    }

}



void MainWindow::on_pushButton_7_clicked()
{
    QLineEdit* lineEdit =ui->lineEdit;
    MyValidator* validator = new MyValidator();
    //lineEdit->setValidator(validator);
    QString vl=lineEdit->text();
    QLabel *label_3=ui->label_3;
    if(validator->validate(vl) == QValidator::Acceptable)
    {
        lineEdit->setStyleSheet("background-color: green;");
         label_3->clear();
    }
    else
    {
        label_3->setText("Логин может содержать строчные латин.\n буквы, цифры, нижнее подчеркивание,\n длина 5-15 символов");
        lineEdit->setStyleSheet("background-color: red;");
        ui->lineEdit->setFocus();
        ui->lineEdit->selectAll();
    }
    QLineEdit* lineEdit_2 =ui->lineEdit_2;
    QString vl2=lineEdit_2->text();
    QLabel *label_14=ui->label_14;
    if(validator->validate_pass(vl2) == QValidator::Acceptable)
    {
        lineEdit_2->setStyleSheet("background-color: green;");
        label_14->clear();
    }
    else
    {
        label_14->setText("Пароль должен содержать 8 символов,\n включая как минимум 1 прописную\n букву, 1 строчную букву и 1 цифру");
        lineEdit_2->setStyleSheet("background-color: red;");
        ui->lineEdit_2->setFocus();
        ui->lineEdit_2->selectAll();
    }
    if((validator->validate(vl) == QValidator::Acceptable)&&(validator->validate_pass(vl2) == QValidator::Acceptable))
    {
        QSqlQuery inu;
        inu.prepare("INSERT INTO User(login,password) VALUES(:login,:password)");
        inu.bindValue(":login",vl);
        inu.bindValue(":password",vl2);
        if (!inu.exec()) {
            qDebug() << "Ошибка выполнения запроса:" << inu.lastError();
            QMessageBox::critical(this,"Problem","There are problems, the user has not been added");
        } else {
            qDebug() << "Данные успешно удалены из базы данных";
            QMessageBox::information(this,"Yeee","User was added successfully");
        }
    }
    //lineEdit->show();
}

