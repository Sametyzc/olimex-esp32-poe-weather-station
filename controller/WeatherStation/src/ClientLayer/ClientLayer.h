
#ifndef CLIENT_LAYER_H
#define CLIENT_LAYER_H

#include <ETH.h>
#include <Logger.h>
#include <List.hpp>

struct Variable
{
    String name;
    String value;
};

class ClientContentType
{
    protected:
        String contentTypeName_;

    public:
        ClientContentType();
        ~ClientContentType();
        
        virtual String GetContent() = 0;
        
        String GetContentTypeName();

        List<Variable> variableList;
};

class UrlEncoded : public ClientContentType
{
    public:
        UrlEncoded();
        ~UrlEncoded();
        String GetContent() override;
};

class ClientLayer
{
    public:
        ClientLayer(String hostname,unsigned short int port,ClientContentType* contentType);
        ~ClientLayer();
        String Post(String endPoint,bool printBody = false);

        ClientContentType* contentType;

    private:
        String hostname_;
        unsigned short int port_;
};

#endif