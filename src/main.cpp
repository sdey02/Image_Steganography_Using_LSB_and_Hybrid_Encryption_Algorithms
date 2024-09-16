#include <botan/block_cipher.h>
#include <botan/hex.h>
#include <iostream>
#include <string_view>
#include <vector>
#include <bitset>
#include <string>

int main() {
   std::string plaintext = "I love work";
   std::vector<uint8_t> key = Botan::hex_decode("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F");
   
   // Convert string to vector<uint8_t>
   std::vector<uint8_t> data(plaintext.begin(), plaintext.end());
   
   // Pad the data to a multiple of the block size (16 bytes for AES)
   while (data.size() % 16 != 0) {
       data.push_back(0);
   }

   const auto cipher = Botan::BlockCipher::create_or_throw("AES-256");
   cipher->set_key(key);

   // Encrypt the entire data vector
   cipher->encrypt(data);

   std::cout << "\n" << cipher->name() << " encrypted: " << Botan::hex_encode(data);

 // Decrypt the data
   cipher->decrypt(data);

   // Remove padding and convert back to string
   while (!data.empty() && data.back() == 0) {
       data.pop_back();
   }
   std::string decrypted(data.begin(), data.end());

   std::cout << "\nDecrypted: " << decrypted;

   return 0;
}