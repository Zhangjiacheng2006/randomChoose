#include "root.h"
#include "globVar.h"
#include "ui_root.h"
#include "sett.h"
#include "res.h"
#include "settlk.h"

#include <QString>
#include <QMessageBox>

root::root(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::root){
    ui->setupUi(this);
    ui->centralwidget->setContentsMargins(0,0,0,0);
}
root::~root(){
    delete ui;
}
void root::on_add_1_clicked(){
    int u=ui->snum->text().toInt(); if(u<N) u++;
    ui->snum->setText(QString::number(u));
}
void root::on_add_max_clicked(){
    ui->snum->setText(QString::number(N));
}
void root::on_dec_1_clicked(){
    int u=ui->snum->text().toInt(); if(u>1) u--;
    ui->snum->setText(QString::number(u));
}
void root::on_dec_min_clicked(){
    ui->snum->setText(QString::number(1));
}
void root::on_snum_editingFinished(){
    bool flag; int u=ui->snum->text().toInt(&flag);
    if((flag==false)||u<1||u>N){
        QMessageBox::warning(this,"警告","输入必须是[1,"+QString::number(N)+"]范围内的正整数");
        ui->snum->setText(QString::number(1)); return;
    }
}
void root::on_gpRb_clicked(){
    ui->runChoose->setText(ui->csRb->isChecked()?QString("选取若干个"):QString("分成若干组"));
}
void root::on_csRb_clicked(){
    ui->runChoose->setText(ui->csRb->isChecked()?QString("选取若干个"):QString("分成若干组"));
}
void root::on_runSett_clicked(){
    if(locked==false){
        sett *setw=new sett(nullptr);
        setw->show();
    }else{
        settlk *setw=new settlk(nullptr);
        setw->show();
    }
}
void root::on_runChoose_clicked(){
    bool flag; int u=ui->snum->text().toInt(&flag);
    if(N==0){
        QMessageBox::warning(this,"警告","没有元素可以选择");
        return ;
    }
    if((flag==false)||u<1||u>N){
        QMessageBox::warning(this,"警告","输入必须是[1,"+QString::number(N)+"]范围内的正整数");
        return ;
    }
    res *resw=new res(nullptr,(ui->csRb->isChecked()),u);
    resw->show();
}

