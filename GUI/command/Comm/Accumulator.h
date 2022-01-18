#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "MessageInterpretor.h"
#include "Dataframe.h"


enum Accumulator_state
{
    DECODING_START_BYTES,
    DECODING_MESSAGEID,
    DECODING_FRAMEID,
    DECODING_BUFFER_SIZE,
    DECODING_BUFFER
};


class Accumulator
{
public:
    Accumulator(MessageInterpretor* interpretor);
    ~Accumulator();
    void addData(char* data, unsigned size);
    char* getAccumulatedData();
    unsigned int getAccumulatedDataSize();
    Accumulator_state getState();
    void reset();

private:
    bool accumulate(char& byte);
    void write(char& byte);
    MessageInterpretor* interpretor;
    char* buffer;
    unsigned int currentBufferSize;
    Accumulator_state state;
    unsigned int targerBufferSize;
};

#endif // ACCUMULATOR_H
