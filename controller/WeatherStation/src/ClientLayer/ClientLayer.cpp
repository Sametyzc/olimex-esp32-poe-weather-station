#include "ClientLayer.h"


ClientContentType::ClientContentType() { }

ClientContentType::~ClientContentType() { }

String ClientContentType::GetContentTypeName()
{
    return contentTypeName_;
}

UrlEncoded::UrlEncoded()
{
    contentTypeName_ = String("application/x-www-form-urlencoded");
}

UrlEncoded::~UrlEncoded() { }

String UrlEncoded::GetContent()
{
    String content;
    int variableListSize = variableList.getSize();
    for (int i = 0; i < variableListSize; i++)
    {
        content += variableList[i].name + "=" + variableList[i].value;
        if (i < variableListSize - 1)
        {
            content += "&";
        }
    }
    return content;
}

ClientLayer::ClientLayer(String hostname,unsigned short int port,ClientContentType* contentType)
{
    hostname_ = hostname;
    port_ = port;
    this->contentType = contentType;
}

ClientLayer::~ClientLayer()
{
    delete contentType;
}

String ClientLayer::Post(String endPoint,bool printBody /* false */)
{
    String content = contentType->GetContent();
    String contentTypeName = contentType->GetContentTypeName();

    Logger::verbose("ClientLayer::Post()",String("connecting to " + hostname_ + ":" + port_).c_str());
    WiFiClient client;
    if (!client.connect(hostname_.c_str(), port_)) {
        String error("connection to " + hostname_ + ":" + port_ + " failed");
        Logger::error("ClientLayer::Post()",error.c_str());
        return error;
    }
    if(printBody)
    {
        Serial.println("----------Post Body-----------");
        Serial.printf("POST %s HTTP/1.1\r\n", endPoint);
        Serial.printf("Host: %s:%i\r\n", hostname_, port_);
        Serial.printf("Content-Type: %s\r\n", contentTypeName);
        Serial.printf("Content-Length: %i\r\n\r\n", content.length());
        Serial.println(content);
        Serial.println("------------------------------");
    }

    client.printf("POST %s HTTP/1.1\r\n", endPoint);
    client.printf("Host: %s:%i\r\n", hostname_, port_);
    client.printf("Content-Type: %s\r\n", contentTypeName);
    client.printf("Content-Length: %i\r\n\r\n", content.length());
    client.println(content);

    while (client.connected() && !client.available());

    String response = "";
    while (client.available()) {
        response += client.readStringUntil('\r');
    };

    Logger::verbose("ClientLayer::Post()","Connection closed");
    client.stop();
    return response;
}
