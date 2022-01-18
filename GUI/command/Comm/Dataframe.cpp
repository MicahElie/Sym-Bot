#include "DataFrame.h"


/****************************************************************************
 *
 * |Start Bytes|MessageId|dataSize|data|
 *
*****************************************************************************/


DataFrame::DataFrame(int const& messageId,char* buffer,unsigned int const& size)
{

    frameData = new char[HEADER_SIZE+size];

    //write the header into the buffer
    write_int_to_buffer(frameData+START_BYTE_OFFSET,START_BYTE);
    write_int_to_buffer(frameData+MESSAGE_ID_OFFSET,messageId);
    write_int_to_buffer(frameData+BUFFER_SIZE_OFFSET,size);

    //write data
    char* dataPtr = frameData+BUFFER_OFFSET;
    for(unsigned int x=0; x < size;x++)
    {
        dataPtr[x] = buffer[x];
    }
}

DataFrame::~DataFrame()
{
    delete[] frameData;
}


void DataFrame::write_int_to_buffer(char* buffer, int const& nbr)
{
    buffer[0] = (nbr & 0xFF000000) >> 24;
    buffer[1] = (nbr & 0x00FF0000) >> 16;
    buffer[2] = (nbr & 0x0000FF00) >> 8;
    buffer[3] = nbr & 0x000000FF;
}

int  DataFrame::convert_buffer_to_int(char* buffer)
{
    int nbr = 0;

    nbr |= (buffer[0] & 0xFF) << 24;
    nbr |= (buffer[1] & 0xFF) << 16;
    nbr |= (buffer[2] & 0xFF) << 8;
    nbr |= buffer[3] & 0xFF;

    return nbr;
}
DataFrame DataFrame::fromRawData(char* buffer)
{
    unsigned int messageId = convert_buffer_to_int(buffer+MESSAGE_ID_OFFSET);
    unsigned int buf_size = convert_buffer_to_int(buffer+BUFFER_SIZE_OFFSET);

    return DataFrame(messageId,buffer+BUFFER_OFFSET,buf_size);
}

unsigned int DataFrame::fromRawDataGetMessageId(char *buffer)
{
    return convert_buffer_to_int(buffer+MESSAGE_ID_OFFSET);
}


unsigned int DataFrame::fromRawDataGetBufferSize(char *buffer)
{
    return convert_buffer_to_int(buffer+BUFFER_SIZE_OFFSET);
}

char* DataFrame::fromRawDataGetBuffer(char *buffer)
{
    return buffer+BUFFER_OFFSET;
}



unsigned int DataFrame::getLength()
{
    return HEADER_SIZE + getBufferSize();
}

char* DataFrame::toRawData()
{
    return frameData;
}

int  DataFrame::getMessageId()
{
    return convert_buffer_to_int(frameData+MESSAGE_ID_OFFSET);
}


unsigned int DataFrame::getBufferSize()
{
    return convert_buffer_to_int(frameData+BUFFER_SIZE_OFFSET);
}

char* DataFrame::getBuffer()
{
    return frameData+BUFFER_OFFSET;
}

bool DataFrame::equal(DataFrame& frame)
{
    if(this->getLength() != frame.getLength())
        return false;

    for(unsigned int x =0; x < getBufferSize(); x++)
    {
        if(frameData[x] != frame.toRawData()[x])
            return false;
    }
    return true;
}


