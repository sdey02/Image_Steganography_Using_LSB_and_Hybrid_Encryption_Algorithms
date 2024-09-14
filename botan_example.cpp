#include <botan/block_cipher.h>
#include <botan/hex.h>

#include <iostream>
#include <string_view>
#include <vector>

std::string String_To_Binary(std::string message) {
    for (char c : message){
        binary += std::bitset<8>(c).to_string();
    }
}

int AES_Encryptor() {
    // TODO: Implement AES encryption
    return 0;
}

int Blowfish_Encryptor(std::string text) {
    std::unique_ptr<Botan::BlockCipher> blowfish_cipher= Botan::BlockCipher::create("Blowfish");
    

    return 0;
}

int main() {
    // TODO: Call encryption functions
    return 0;
}