#ifndef ROOT_H
#define ROOT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class root; }
QT_END_NAMESPACE

class root : public QMainWindow
{
    Q_OBJECT

public:
    root(QWidget *parent = nullptr);
    ~root();

private slots:
    void on_add_1_clicked();

    void on_add_max_clicked();

    void on_dec_1_clicked();

    void on_dec_min_clicked();

    void on_snum_editingFinished();

    void on_gpRb_clicked();

    void on_csRb_clicked();

    void on_runSett_clicked();

    void on_runChoose_clicked();

private:
    Ui::root *ui;
};
#endif // ROOT_H
