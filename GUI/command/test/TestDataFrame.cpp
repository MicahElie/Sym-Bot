#include "TestDataFrame.h"

#include <cassert>

#define TEST_FRAME_SIZE 36
#define TEST_FRAME_ID 0x00152699
#define TEST_FRAME_BUFFER_SIZE 24
#define TEST_FRAME_BUFFER "this is a test message"


TestDataFrame::TestDataFrame()
{

}

void TestDataFrame::testAll()
{

    testWriteIntToBuffer();
    testCreateDataFrame();
    testDataIntegity();
    testAllRaw();
    TestIsEqual();
}

void TestDataFrame::testAllRaw()
{
    DataFrame frame = createTestDataFrame();
    char* rawData = frame.toRawData();

    assert(DataFrame::fromRawDataGetMessageId(rawData) == frame.getMessageId());
    assert(DataFrame::fromRawDataGetBufferSize(rawData) == frame.getBufferSize());
    assert(DataFrame::fromRawDataGetBuffer(rawData) == frame.getBuffer());

    testCreateFromRawData(&frame);
}

void TestDataFrame::testCreateDataFrame()
{
    DataFrame frame = createTestDataFrame();
}

void TestDataFrame::testWriteIntToBuffer()
{
    char buffer[4];
    int nbr = 0xFF003656;

    DataFrame::write_int_to_buffer(buffer,nbr);
    int read = DataFrame::convert_buffer_to_int(buffer);

    assert(read == nbr);
}

void TestDataFrame::testCreateFromRawData(DataFrame* demoFrame)
{
    DataFrame frame = DataFrame::fromRawData(demoFrame->toRawData());


    assert(frame.getLength() == demoFrame->getLength());
    assert(frame.getMessageId() == demoFrame->getMessageId());
    assert(frame.getBufferSize() == demoFrame->getBufferSize());
}


DataFrame TestDataFrame::createTestDataFrame()
{
    return DataFrame(TEST_FRAME_ID,TEST_FRAME_BUFFER,TEST_FRAME_BUFFER_SIZE);
}

void TestDataFrame::testDataIntegity()
{
    DataFrame frame = createTestDataFrame();

    assert(frame.getMessageId() == TEST_FRAME_ID);
    assert(frame.getBufferSize() == TEST_FRAME_BUFFER_SIZE);
    char* testBuffer = TEST_FRAME_BUFFER;
    char* retBuf = frame.getBuffer();

    for(int x=0;x < TEST_FRAME_BUFFER_SIZE;x++)
    {
        assert(testBuffer[x] == retBuf[x]);
    }

    assert(frame.getLength() == TEST_FRAME_SIZE);
}

void TestDataFrame::TestIsEqual()
{
     char message1[] = "guess we are equal" ;
     int messageId1 = 0x00152699;

     DataFrame a(messageId1,message1,19);
     DataFrame b(messageId1+1,message1,19);

     assert(a.equal(a));
     assert(!b.equal(a));
     assert(a.equal(a));
     assert(b.equal(b));
}


