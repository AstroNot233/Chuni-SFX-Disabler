#include "optimizer.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Optimizer w;
    w.show();
    return a.exec();
}
