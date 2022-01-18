#include "TestAccumulator.h"
#include <cassert>

TestAccumulator::TestAccumulator()
{

}


 void TestAccumulator::testAll()
{
   testCreation();
   testAddData();
   testStateMachine();
   isDataCorrectlyAccumulated();
}

void TestAccumulator::testCreation()
{
    MessageInterpretor* interpretor = new TestAccumulator();
    Accumulator acc = Accumulator(interpretor);
}

void TestAccumulator::testAddData()
{
    MessageInterpretor* interpretor = new TestAccumulator();
    Accumulator acc = Accumulator(interpretor);

    char message[] = "this is a test msg";
    acc.addData(message,19);

    char* data = acc.getAccumulatedData();
    unsigned int size = acc.getAccumulatedDataSize();

    assert(19 == size);
}

void TestAccumulator::testStateMachine()
{
    char message[] = "test_data_is_live";
    unsigned int messageId = 2 ;

    DataFrame frame = DataFrame(messageId,message,18);

    MessageInterpretor* interpretor = new TestAccumulator();
    Accumulator acc = Accumulator(interpretor);

    //check for decoding start bytes
    assert(isAccumulatorStateCorrect(&acc,&frame,3,DECODING_START_BYTES));
    acc.reset();

    //check for decoding message id
    assert(isAccumulatorStateCorrect(&acc,&frame,MESSAGE_ID_OFFSET,DECODING_MESSAGEID));
    acc.reset();

    //check for buffer size
    assert(isAccumulatorStateCorrect(&acc,&frame,BUFFER_SIZE_OFFSET,DECODING_BUFFER_SIZE));
    acc.reset();

    //check for decoding buffer
    assert(isAccumulatorStateCorrect(&acc,&frame,BUFFER_OFFSET,DECODING_BUFFER));
    acc.reset();

    //check for decoding correcte loop
    assert(isAccumulatorStateCorrect(&acc,&frame,frame.getLength(),DECODING_START_BYTES));
}

void TestAccumulator::isRecevedMessageOk(Accumulator* acum,DataFrame* frame,TestAccumulator* interpretor)
{

    //check for decoding correcte loop
    assert(isAccumulatorStateCorrect(acum,frame,frame->getLength(),DECODING_START_BYTES));

    assert(interpretor->getDataFrame()->equal(*frame));
}


void TestAccumulator::isDataCorrectlyAccumulated()
{
    char message[] = "test_data_is_live";
    unsigned int messageId =2;

    DataFrame FirstFrame = DataFrame(messageId,message,18);
    DataFrame SecondFrame = DataFrame(messageId,message,15);
    TestAccumulator interpretor;
    Accumulator acc = Accumulator(&interpretor);

    isRecevedMessageOk(&acc,&FirstFrame,&interpretor);
    isRecevedMessageOk(&acc,&SecondFrame,&interpretor);
}


bool TestAccumulator::messageReceved(char* rawDataFrame,unsigned int lenght)
{

    m_dataFrame = new DataFrame(DataFrame::fromRawDataGetMessageId(rawDataFrame)
                            ,DataFrame::fromRawDataGetBuffer(rawDataFrame)
                            ,DataFrame::fromRawDataGetBufferSize(rawDataFrame));
    return true;
}

DataFrame* TestAccumulator::getDataFrame()
{
    return m_dataFrame;
}


bool TestAccumulator::isAccumulatorStateCorrect(Accumulator* acum,DataFrame* frame,unsigned nbrRead ,Accumulator_state expected_state)
{
    acum->addData(frame->toRawData(),nbrRead);
    assert(acum->getState() == expected_state);
    return true;
}

