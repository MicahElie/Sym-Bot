#ifndef TESTDATAFRAME_H
#define TESTDATAFRAME_H

#include "Comm/dataframe.h"

class TestDataFrame
{
public:
    TestDataFrame();
    static void testAll();
private:
    static void testWriteIntToBuffer();
    static void testCreateDataFrame();
    static void testDataIntegity();
    static void testCreateFromRawData(DataFrame* demoFrame);
    static void testAllRaw();
    static void TestIsEqual();
    static DataFrame createTestDataFrame();

};

#endif // TESTDATAFRAME_H
