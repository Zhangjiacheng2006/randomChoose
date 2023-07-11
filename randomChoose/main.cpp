#include "root.h"
#include "globVar.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    getSett();
    root w;
    w.show();
    return a.exec();
}
