#ifndef ENCRYPTOR_HPP
#define ENCRYPTOR_HPP

#include <string>

class Encryptor {
public:
    static std::string StringToBinary(const std::string& message);
    static int Blowfish_Key_Gen();
    static int AES_Key_Gen();
    static int AESEncrypt();
    static int BlowfishEncrypt(const std::string &text);
    static int AESDecrypt();
    static int BlowfishDecrypt();
    static int Full_Encryption_Pipeline(std::string &text);
    static int Full_Decryption_Pipeline(std::string &text);
};

#endif // ENCRYPTOR_HPP