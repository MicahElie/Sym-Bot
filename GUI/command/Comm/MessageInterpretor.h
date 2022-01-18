#ifndef MESSAGEINTERPRETOR_H
#define MESSAGEINTERPRETOR_H


class MessageInterpretor
{
public:
    virtual bool messageReceved(char* rawDataFrame, unsigned int lenght) = 0;
};

#endif // MESSAGEINTERPRETOR_H
