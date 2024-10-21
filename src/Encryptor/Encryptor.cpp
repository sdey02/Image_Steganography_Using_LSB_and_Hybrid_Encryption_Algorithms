#include <botan/block_cipher.h>
#include <botan/hex.h>
#include <iostream>
#include <string_view>
#include <vector>
#include <bitset>

class Encryptor {
    public:
        static std::string StringToBinary(const std::string& message) {
            std::string binary;
            for (char c : message) {
                binary += std::bitset<8>(c).to_string();
            }
            return binary;
        }

        static int Blowfish_Key_Gen() {
                
            return
        }

        static int AES_Key_Gen() {

            return
        }

        static int AESEncrypt() {


            std::unique_ptr<Botan::BlockCipher> AES_256_cipher = Botan::BlockCipher::create("AES-256");
            AES_256_cipher->set_key(key);
            AES_256_cipher->encrypt(text);

            return
        }

        static int BlowfishEncrypt(const std::string &text) {


            std::unique_ptr<Botan::BlockCipher> blowfish_cipher = Botan::BlockCipher::create("Blowfish");
            blowfish_cipher->set_key(key);
            blowfish_cipher->encrypt(text);

            return
        }

        static int AESDecrypt() {

            std::unique_ptr<Botan::BlockCipher> AES_256_cipher = Botan::BlockCipher::create("AES-256");
            AES_256_cipher->set_key(key);
            AES_256_cipher->decrypt();
            
            return
        }

        static int BlowfishDecrypt() {

            std::unique_ptr<Botan::BlockCipher> blowfish_cipher = Botan::BlockCipher::create("Blowfish");
            blowfish_cipher->set_key(key);
            blowfish_cipher->decrypt();

            return
        }

        static int Full_Encryption_Pipeline(std::string &text) {

        }

        static int Full_Decryption_Pipeline(std::string &text) {
            
        }
};