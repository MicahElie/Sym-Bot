#include "Accumulator.h"

#define ACCUMULATOR_BUFFER_SIZE 2500

Accumulator::Accumulator(MessageInterpretor* interpretor)
{
    this->interpretor = interpretor;
    this->buffer = new char[ACCUMULATOR_BUFFER_SIZE];
    currentBufferSize = 0;
    targerBufferSize = 0;
    state = DECODING_START_BYTES;
}

Accumulator::~Accumulator()
{
    delete[] buffer;
}

void Accumulator::addData(char* data, unsigned size)
{
    for(int x=0;x<size;x++)
    {
        accumulate(data[x]);
    }
}

char* Accumulator::getAccumulatedData()
{
    return buffer;
}

unsigned int Accumulator::getAccumulatedDataSize()
{
    return currentBufferSize;
}

void Accumulator::reset()
{
    currentBufferSize = 0;
    state = DECODING_START_BYTES;
}

bool Accumulator::accumulate(char& byte)
{

    if(state == DECODING_START_BYTES)
    {
        write(byte);
        if(currentBufferSize == START_BYTE_SIZE)
        {

            if(DataFrame::convert_buffer_to_int(buffer) == START_BYTE)
            {
                state =  DECODING_MESSAGEID;
                return true;
            }
            else
                return false;
        }
    }
    else if(state == DECODING_MESSAGEID)
    {
        write(byte);
        if(currentBufferSize == BUFFER_SIZE_OFFSET)
            state = DECODING_BUFFER_SIZE;
        return true;
    }
    else if(state == DECODING_BUFFER_SIZE)
    {
        write(byte);
        if(currentBufferSize == BUFFER_OFFSET)
        {
            state = DECODING_BUFFER;
            targerBufferSize = DataFrame::fromRawDataGetBufferSize(buffer)+HEADER_SIZE;
        }
        return true;
    }
    else if(state == DECODING_BUFFER)
    {
          write(byte);
          if(currentBufferSize == targerBufferSize)
          {
            interpretor->messageReceved(buffer,currentBufferSize);
            reset();
          }
    }





    return true;
}

void Accumulator::write(char& byte)
{

    buffer[currentBufferSize++] = byte;
}


Accumulator_state Accumulator::getState()
{
    return state;
}


