#ifndef SETTLK_H
#define SETTLK_H

#include <QLabel>
#include <QWidget>
#include <QCheckBox>
#include <QCloseEvent>
#include <QGridLayout>

namespace Ui {
class settlk;
}

class settlk : public QWidget
{
    Q_OBJECT

public:
    explicit settlk(QWidget *parent = nullptr);
    ~settlk();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_checkBox_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    int NBig,ckSum,intC;
    void buildUi(QJsonObject obj);
    void addItem(QGridLayout *lout,int i,QString Tname,bool stat);
    Ui::settlk *ui;
};

#endif // SETTLK_H
