#include "globVar.h"
#include <QStandardPaths>
#include <QMessageBox>
#include <ctime>
#include <QDir>

int N=52;
bool locked=false;
std::random_device mt_seed;
std::mt19937_64 mt_rand((((unsigned int)(time(0)*998244353ull))<<8ull)+mt_seed());
QJsonObject settObj=QJsonObject();
QDir cfp(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation));

QJsonObject cstSett(){
    QJsonObject obj;
    obj.insert("sum",1);
    obj.insert("name",QJsonArray({QString("empty")}));
    obj.insert("stat",QJsonArray({true}));
    return obj;
}
void writeSett(){
    cfp=QDir(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation));
    cfp.mkpath(cfp.absolutePath()+"/randomChoose"); cfp.cd("randomChoose");
    QFile file(cfp.absolutePath()+"/sett.json");
    if(file.open(QIODevice::WriteOnly)){
        QJsonDocument doc(settObj);
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }else{
        QMessageBox::warning(nullptr,"警告","无法获取对 "+cfp.absolutePath()+" 的写入权限");
    }
}
QJsonObject getSettFrom(QString str){
    QJsonObject obj;
    QFile file(str);
    file.open(QIODevice::ReadOnly);
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll(),&err);
    file.close();
    if(doc.isNull()||(err.error!=QJsonParseError::NoError)){
        QMessageBox::warning(nullptr,"错误","看不懂json.");
        obj=cstSett();
    }
    else obj=doc.object();

    int n=obj["sum"].toInt();
    if(n==0){
        QMessageBox::warning(nullptr,"错误","格式不对啊，元素个数有问题啊");
        return cstSett();
    }
    QJsonArray arr=obj["stat"].toArray();
    if(obj["name"].toArray().size()!=n){
        QMessageBox::warning(nullptr,"错误","格式不对啊，元素个数与实际人数对不上啊");
        return cstSett();
    }
    if(arr.empty()){
        QMessageBox::warning(nullptr,"警告","格式不对啊，状态呢。\n帮你全勾选上了。");
        arr=QJsonArray(); for(int i=0;i<n;i++) arr.append(true);
        if(obj.contains("stat")) obj["stat"]=arr;
        else obj.insert("stat",arr);
    }
    if(arr.size()!=n){
        QMessageBox::warning(nullptr,"警告","格式不对啊，元素个数与状态个数对不上。\n帮你全勾选上了。");
        arr=QJsonArray(); for(int i=0;i<n;i++) arr.append(true); obj["stat"]=arr;
    }
    return obj;
}
void getSett(){
    cfp=QDir(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation));
    cfp.mkpath(cfp.absolutePath()+"/randomChoose"); cfp.cd("randomChoose");
    QStringList sl=cfp.entryList();
    if(!sl.contains("sett.json")){
        settObj=cstSett(); N=1; return;
    }
    settObj=getSettFrom(cfp.absolutePath()+"/sett.json");
    QJsonArray arr=settObj["stat"].toArray();
    N=0; for(auto it=arr.begin();it!=arr.end();++it){if(it->toBool())N++;}
    if(sl.contains("locked")){ locked=true; }
    else{ locked=false; }
}
