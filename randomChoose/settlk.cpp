#include "settlk.h"
#include "ui_settlk.h"
#include "globVar.h"
#include <QMessageBox>

void settlk::addItem(QGridLayout *lout,int i,QString Tname,bool stat){
    QLabel *cnum=new QLabel(QString("no")+QString::number(i+1));
    QLabel *cnam=new QLabel(QString("nam")+QString::number(i+1));
    QCheckBox *cbox=new QCheckBox(QString("box")+QString::number(i+1));
    cnum->setAlignment(Qt::AlignmentFlag::AlignCenter);
    cnam->setAlignment(Qt::AlignmentFlag::AlignCenter);
    cnum->setMaximumWidth(20);cbox->setMaximumWidth(50);
    cnum->setText(QString::number(i+1));
    cnam->setText(Tname);
    cbox->setText(stat?QString("已选"):QString("未选"));
    cbox->setChecked(stat);
    connect(cbox,&QCheckBox::clicked,[&](bool checked){
        if(checked==true) ckSum++; else ckSum--;
        if(ui->checkBox->checkState()==Qt::CheckState::Checked&&ckSum<NBig)
            ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
        else if(ui->checkBox->checkState()==Qt::CheckState::Unchecked&&ckSum==NBig)
            ui->checkBox->setCheckState(Qt::CheckState::Checked);
    });
    lout->addWidget(cnum,i,0);
    lout->addWidget(cnam,i,1);
    lout->addWidget(cbox,i,2);
}
void settlk::buildUi(QJsonObject obj=settObj){
    QWidget *widg=ui->scrollAreaWidgetContents;
    QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
    for(int i=lout->count()-1;i>=0;i--){
        delete lout->itemAt(i)->widget();
        lout->removeItem(lout->itemAt(i));
    }
    NBig=obj["sum"].toInt(); ckSum=0;
    for(int i=0;i<NBig;i++){
        addItem(lout,i,(obj["name"].toArray())[i].toString(),(obj["stat"].toArray())[i].toBool());
        if((obj["stat"].toArray())[i].toBool()) ckSum++;
    }
    if(ckSum==NBig) ui->checkBox->setCheckState(Qt::CheckState::Checked);
}

settlk::settlk(QWidget *parent) :
    QWidget(parent),
    intC(0),
    ui(new Ui::settlk){
    getSett();
    ui->setupUi(this);
    buildUi();
}

settlk::~settlk(){
    delete ui;
}
void settlk::on_checkBox_clicked(){
    QWidget *widg=ui->scrollAreaWidgetContents;
    QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
    if(ui->checkBox->checkState()==Qt::CheckState::Checked){
        for(int i=0;i<NBig;i++){
            QCheckBox *tgt=static_cast<QCheckBox*>(lout->itemAtPosition(i,2)->widget());
            tgt->setChecked(true);
        } ckSum=NBig;
    }else{
        for(int i=0;i<NBig;i++){
            QCheckBox *tgt=static_cast<QCheckBox*>(lout->itemAtPosition(i,2)->widget());
            tgt->setChecked(false);
        } ckSum=0;
    }
}


void settlk::on_pushButton_clicked(){
    QJsonArray arr=settObj["stat"].toArray();
    QWidget *widg=ui->scrollAreaWidgetContents;
    QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
    N=0; for(int i=0;i<NBig;i++){
        if(static_cast<QCheckBox*>(lout->itemAtPosition(i,2)->widget())->isChecked()){
            arr[i]=true; N++;
        }else arr[i]=false;
    }
    settObj["stat"]=arr;
    writeSett();intC=1;this->close();
}


void settlk::on_pushButton_2_clicked(){
    if(QMessageBox::question(this,"取消","取消可能丢失当前更改。\n确定要这么做吗？")==QMessageBox::Yes)
    {intC=1;this->close();}
}
void settlk::closeEvent(QCloseEvent *event){
    if(intC){event->accept();return;}
    QMessageBox::StandardButton res=QMessageBox::question(this,"关闭","保存当前更改吗",QMessageBox::StandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel));
    switch(res){
        case QMessageBox::Save:{
            QJsonArray arr=settObj["stat"].toArray();
            QWidget *widg=ui->scrollAreaWidgetContents;
            QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
            N=0; for(int i=0;i<NBig;i++){
                if(static_cast<QCheckBox*>(lout->itemAtPosition(i,2)->widget())->isChecked()){
                    arr[i]=true; N++;
                }else arr[i]=false;
            }
            settObj["stat"]=arr;
            writeSett();event->accept();break;
        }
        case QMessageBox::Cancel:{
            event->ignore();break;
        }
        default:{event->accept();break;}
    }
}
