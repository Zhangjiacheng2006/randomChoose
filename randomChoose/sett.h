#ifndef SETT_H
#define SETT_H

#include <QWidget>
#include <QCloseEvent>
#include <QGridLayout>
#include <QJsonObject>

namespace Ui {
class sett;
}

class sett : public QWidget
{
    Q_OBJECT

public:
    explicit sett(QWidget *parent = nullptr);
    ~sett();
public slots:
    void delbut();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_2_clicked();
    void on_checkBox_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
private:
    int NBig,ckSum,intC;
    Ui::sett *ui;
    void buildUi(QJsonObject obj);
    void addItem(QGridLayout *lout,int i,QString Tname,bool stat);
    QJsonObject gjobj();
};

#endif // SETT_H
