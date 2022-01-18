#ifndef TESTACCUMULATOR_H
#define TESTACCUMULATOR_H

#include "Comm/Accumulator.h"
#include "Comm/dataframe.h"
#include "Comm/MessageInterpretor.h"

class TestAccumulator : public MessageInterpretor
{
public:
    TestAccumulator();
    static void testAll();
    static void testCreation();
    static void testAddData();
    static void testStateMachine();
    static void isRecevedMessageOk(Accumulator* acum,DataFrame* frame, TestAccumulator* interpretor);
    virtual bool messageReceved(char* rawDataFrame,unsigned int lenght);

    DataFrame* getDataFrame();
private:
    static bool isAccumulatorStateCorrect(Accumulator* acum,DataFrame* frame,unsigned int nbrRead,Accumulator_state expected_state);
    static void isDataCorrectlyAccumulated();
    DataFrame* m_dataFrame;

};

#endif // TESTACCUMULATOR_H
