#include "TestApp.h"

#include "test/TestDataFrame.h"
#include "test/TestAccumulator.h"
#include "test/Testcontrolmessage.h"


TestApp::TestApp()
{

}


bool TestApp::test()
{
    TestDataFrame::testAll();

    TestAccumulator::testAll();

    testControlMessage::testAll();

    return true;
}
