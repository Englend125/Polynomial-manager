#include "polinomemenager.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    
    polinomemenager p;
    p.show();
    
    return a.exec();
}
