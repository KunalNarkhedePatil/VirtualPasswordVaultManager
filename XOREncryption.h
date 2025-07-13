#ifndef XORENCRYPTION_H
#define XORENCRYPTION_H

#include <string>

class XOREncryption 
{
public:
    XOREncryption(const std::string& key);
    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);

private:
    std::string m_key;
};

#endif
