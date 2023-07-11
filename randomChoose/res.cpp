#include "res.h"
#include "ui_res.h"
int defType=3;
void res::reori(){
    if(ui->radioButton->isChecked()) defType=1;
    else if(ui->radioButton_2->isChecked()) defType=2;
    else if(ui->radioButton_3->isChecked()) defType=3;
    int tt=defType; QString str("");
    if(tp){
        for(int i=0;i<n;i++){
            switch(tt){
                case 1:str+=QString::number(ord[i]+1)+" ";break;
                case 2:str+=aee[ord[i]].toString()+" ";break;
                default:str+=QString::number(ord[i]+1)+" "+aee[ord[i]].toString()+"\n";break;
            }
        }
    }else{
        int m=ord.size(),u=m/n,v=m%n;
        for(int i=0,j=0;i<n&&j<m;i++){
            for(int p=0;p<(u+int(v>0))&&j<m;p++,j++){
                switch(tt){
                    case 1:str+=QString::number(ord[j]+1)+" ";break;
                    case 2:str+=aee[ord[j]].toString()+" ";break;
                    default:str+=QString::number(ord[j]+1)+","+aee[ord[j]].toString()+" ";break;
                }
            }
            str+="\n"; v--;
        }
    }
    ui->label->setText(str);
    this->resize(QSize(200,130));
}
res::res(QWidget *parent,bool tp, int n) :
    QWidget(parent),
    ui(new Ui::res),
    n(n),tp(tp){
    getSett();
    ui->setupUi(this);
    switch(defType){
        case 1: ui->radioButton->setChecked(true); break;
        case 2: ui->radioButton_2->setChecked(true); break;
        case 3: ui->radioButton_3->setChecked(true); break;
        default: ui->radioButton_3->setChecked(true); break;
    }
    aee=settObj["name"].toArray();
    QJsonArray arr=settObj["stat"].toArray();
    for(int i=0;i<settObj["sum"].toInt();i++){
        if(arr[i].toBool()) ord.push_back(i);
    }
    std::shuffle(ord.begin(),ord.end(),mt_rand);
    reori();
}
res::~res(){
    delete ui;
}
void res::on_pushButton_clicked(){
    std::shuffle(ord.begin(),ord.end(),mt_rand);
    reori();
}
void res::on_radioButton_clicked(){reori();}
void res::on_radioButton_2_clicked(){reori();}
void res::on_radioButton_3_clicked(){reori();}
