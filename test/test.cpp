#include <iostream>
#include "../src/sha.h"
#include "base.h"

using namespace std;
using namespace shiny;

template<typename T>
std::string toBinary(T num)
{
    std::string temp;
    for(int i = 0; i < sizeof(num) * 8; i++)
    {
        temp.push_back('0' + num % 2);
        num /= 2;
    }
    std::string ret;
    for(auto it = temp.rbegin(); it != temp.rend(); it++)
    {
        ret.push_back(*it);
    }
    return ret;
}

int main(int argc, const char* argv[])
{

    std::string str = (argc > 1 ? argv[1] : "");

    SHA0 sha0;
    sha0.init(str);
    sha0.compute();
    cout << "SHA0: ";
    for(uint32_t h : sha0.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA1 sha1;
    sha1.init(str);
    sha1.compute();
    cout << "SHA1: ";
    for(uint32_t h : sha1.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA224 sha224;
    sha224.init(str);
    sha224.compute();
    cout << "SHA224: ";
    for(uint32_t h : sha224.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA256 sha256;
    sha256.init(str);
    sha256.compute();
    cout << "SHA256: ";
    for(uint32_t h : sha256.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA384 sha384;
    sha384.init(str);
    sha384.compute();
    cout << "SHA384: ";
    for(uint64_t h : sha384.getDisgest())
        cout << hexadecimal.decodeN(h, 16);
    cout << endl;

    SHA512 sha512;
    sha512.init(str);
    sha512.compute();
    cout << "SHA512: ";
    for(uint64_t h : sha512.getDisgest())
        cout << hexadecimal.decodeN(h, 16);
    cout << endl;

    SHA512_224 sha512_224;
    sha512_224.init(str);
    sha512_224.compute();
    cout << "SHA512_224: ";
    for(uint64_t h : sha512_224.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA512_256 sha512_256;
    sha512_256.init(str);
    sha512_256.compute();
    cout << "SHA512_256: ";
    for(uint64_t h : sha512_256.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    // for(int i = 0; i < sha384.blocks.size(); i++)
    // {
    //     cout << "BLOCK " << i << ": " << endl;
    //     for(int j = 0; j < 64; j++)
    //         //cout << j << ": " << toBinary(sha384.blocks[i][j]) << endl;
    //         cout << j << ": " << binary.decodeN(sha384.blocks[i][j], 64) << endl;
    //     cout << endl;
    // }
    // for(int i = 0; i < sha224.hashes.size(); i++)
    // {
    //     cout << "HASH " << i << ": " << endl;
    //     for(int j = 0; j < 6; j++)
    //         //cout << j << ": " << toBinary(sha224.hashes[i][j]) << endl;
    //         cout << j << ": " << binary.decodeN(sha224.hashes[i][j], 32) << endl;
    //     cout << endl;
    // }
    // cout << toBinary((uint32_t)4) << endl;
    // cout << toBinary((uint32_t)'c' << 8 * (2)) << endl;
    return 0;
}