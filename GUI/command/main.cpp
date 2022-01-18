#include <QApplication>

#include "Commandwindow.h"
#include "test/TestApp.h"

#define UNIT_TEST 0

int main(int argc, char *argv[])
{


#if UNIT_TEST == 1
    TestApp test;
    if(!test.test())
    {
        return -5;
    }
#endif

    QApplication a(argc, argv);
    CommandWindow w;
    w.show();
    return a.exec();
}

