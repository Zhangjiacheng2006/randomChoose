#ifndef RES_H
#define RES_H

#include "globVar.h"
#include <vector>
#include <algorithm>
#include <QWidget>

namespace Ui {
class res;
}

class res : public QWidget
{
    Q_OBJECT

public:
    explicit res(QWidget *parent = nullptr,bool tp = true, int n = 1);
    ~res();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

private:
    Ui::res *ui;
    std::vector<int> ord;
    QJsonArray aee;
    int n; bool tp;
    void reori();
};

#endif // RES_H
