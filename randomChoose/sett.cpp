#include "sett.h"
#include <QJsonArray>
#include "ui_sett.h"
#include "globVar.h"
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>

void sett::addItem(QGridLayout *lout,int i,QString Tname,bool stat){
    QPushButton *cbut=new QPushButton(QString("del")+QString::number(i+1));
    QLabel *cnum=new QLabel(QString("no")+QString::number(i+1));
    QLineEdit *cnam=new QLineEdit(QString("nam")+QString::number(i+1));
    QCheckBox *cbox=new QCheckBox(QString("box")+QString::number(i+1));
    cbut->setMaximumHeight(20);cbut->setMaximumWidth(45);
    cnum->setAlignment(Qt::AlignmentFlag::AlignCenter);
    cnam->setAlignment(Qt::AlignmentFlag::AlignCenter);
    cbut->setText("X");
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
    connect(cbut,SIGNAL(clicked()),this,SLOT(delbut()));
    lout->addWidget(cbut,i,0);
    lout->addWidget(cnum,i,1);
    lout->addWidget(cnam,i,2);
    lout->addWidget(cbox,i,3);
}
void sett::delbut(){
    QPushButton *but=static_cast<QPushButton*>(QObject::sender());
    if(but->text()==QString("X")) but->setText("已删除");
    else but->setText("X");
}
void sett::buildUi(QJsonObject obj=settObj){
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
sett::sett(QWidget *parent) :
    QWidget(parent),
    intC(0),
    ui(new Ui::sett){
    getSett();
    ui->setupUi(this);
    buildUi();
}
sett::~sett(){
    delete ui;
}
QJsonObject sett::gjobj(){
    QJsonObject obj;
    QJsonArray anam;
    QJsonArray astt;
    QWidget *widg=ui->scrollAreaWidgetContents;
    QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
    int cnt=0; for(int i=0;i<NBig;i++){
        if((static_cast<QPushButton*>(lout->itemAtPosition(i,0)->widget()))->text()!="X") continue;
        cnt++; anam.push_back((static_cast<QLineEdit*>(lout->itemAtPosition(i,2)->widget()))->text());
        astt.push_back((static_cast<QCheckBox*>(lout->itemAtPosition(i,3)->widget()))->isChecked());
    }
    obj.insert("sum",cnt); obj.insert("name",anam); obj.insert("stat",astt);
    return obj;
}
void sett::on_pushButton_2_clicked()
{
    int u=ui->spinBox->text().toInt();
    if(NBig+u>=10000){
        QMessageBox::warning(this,"错误","元素数量太多了，你真的需要这么多吗？（去联系程序原作者吧）");
        return;
    }
    if(NBig+u>=1000){
        QMessageBox::warning(this,"警告","请注意，元素数量越多，计算可能越慢。");
    }
    QWidget *widg=ui->scrollAreaWidgetContents;
    QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
    for(int i=0;i<u;i++) addItem(lout,NBig+i,QString("name")+QString::number(NBig+i+1),true);
    NBig+=u; ckSum+=u;
}

void sett::on_checkBox_clicked(){
    QWidget *widg=ui->scrollAreaWidgetContents;
    QGridLayout *lout=static_cast<QGridLayout*>(widg->layout());
    if(ui->checkBox->checkState()==Qt::CheckState::Checked){
        for(int i=0;i<NBig;i++){
            QCheckBox *tgt=static_cast<QCheckBox*>(lout->itemAtPosition(i,3)->widget());
            tgt->setChecked(true);
        } ckSum=NBig;
    }else{
        for(int i=0;i<NBig;i++){
            QCheckBox *tgt=static_cast<QCheckBox*>(lout->itemAtPosition(i,3)->widget());
            tgt->setChecked(false);
        } ckSum=0;
    }
}
void sett::on_pushButton_5_clicked(){
    QString loc=QFileDialog::getSaveFileName(this,tr("导出json"),".",tr("json file(*.json)"));
    if(loc=="") return;
    QFile file(loc);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this,"错误","打开文件失败"); return;
    }
    QJsonDocument doc(gjobj());
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}
void sett::on_pushButton_6_clicked(){
    if(QMessageBox::question(this,"重载","重载可能丢失当前更改。\n确定要这么做吗？")==QMessageBox::Yes){
        QString loc=QFileDialog::getOpenFileName(this,tr("导入json"),".",tr("json file(*.json)"));
        buildUi(getSettFrom(loc));
    }
}
void sett::on_pushButton_7_clicked(){
    if(QMessageBox::question(this,"刷新","刷新可能丢失当前更改。\n确定要这么做吗？")==QMessageBox::Yes)
        buildUi(settObj);
}
void sett::on_pushButton_clicked(){
    settObj=gjobj(); QJsonArray arr=settObj["stat"].toArray();
    N=0; for(auto it=arr.begin();it!=arr.end();++it){if(it->toBool())N++;}
    writeSett();intC=1; this->close();
}
void sett::on_pushButton_4_clicked(){
    if(QMessageBox::question(this,"取消","取消可能丢失当前更改。\n确定要这么做吗？")==QMessageBox::Yes)
    {intC=1;this->close();}
}
void sett::closeEvent(QCloseEvent *event){
    if(intC){event->accept();return;}
    QMessageBox::StandardButton res=QMessageBox::question(this,"关闭","保存当前更改吗",QMessageBox::StandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel));
    switch(res){
        case QMessageBox::Save:{
            settObj=gjobj(); QJsonArray arr=settObj["stat"].toArray();
            N=0; for(auto it=arr.begin();it!=arr.end();++it){if(it->toBool())N++;}
            writeSett();event->accept();break;
        }
        case QMessageBox::Cancel:{
            event->ignore();break;
        }
        default:{event->accept();break;}
    }
}
