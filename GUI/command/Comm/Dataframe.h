#ifndef DATAFRAME_H
#define DATAFRAME_H

#define START_BYTE 0x00FF00FF


#define START_BYTE_SIZE 4
#define MESSAGE_ID_SIZE 4
#define BUFFER_SIZE_SIZE 4
#define HEADER_SIZE START_BYTE_SIZE + MESSAGE_ID_SIZE + BUFFER_SIZE_SIZE

#define START_BYTE_OFFSET 0
#define MESSAGE_ID_OFFSET START_BYTE_SIZE + START_BYTE_OFFSET
#define BUFFER_SIZE_OFFSET  MESSAGE_ID_OFFSET + MESSAGE_ID_SIZE
#define BUFFER_OFFSET   BUFFER_SIZE_OFFSET + BUFFER_SIZE_SIZE

class DataFrame
{
public:
    static DataFrame fromRawData(char* buffer);
    static unsigned int fromRawDataGetMessageId(char* buffer);
    static unsigned int fromRawDataGetBufferSize(char* buffer);
    static char* fromRawDataGetBuffer(char* buffer);
    static void write_int_to_buffer(char* buffer, int const& nbr);
    static int  convert_buffer_to_int(char* buffer);

    DataFrame(int const& messageId,char* buffer,unsigned int const& size);
    ~DataFrame();

    unsigned int getLength();
    char* toRawData();

    int getStartBytes();
    int getMessageId();
    unsigned int getBufferSize();
    char* getBuffer();

    bool equal(DataFrame& frame);




private:
    char* frameData;
};




#endif // DATAFRAME_H
