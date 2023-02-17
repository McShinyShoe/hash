#ifndef SHINY_MD_LIB
#define SHINY_MD_LIB

#include <iostream>
#define LOG(x) std::cout << x << std::endl

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <cstddef>

namespace shiny
{
    class MD2
    {
    public:
        static constexpr uint8_t piSubstitution[] = {
            41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
            19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
            76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
            138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
            245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
            148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
            39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
            181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
            150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
            112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
            96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
            85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
            234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
            129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
            8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
            203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
            166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
            31, 26, 219, 153, 141, 51, 159, 17, 131, 20
        };

    public:
        std::vector<std::array<uint8_t, 16>>blocks;
        std::array<uint8_t, 48> buffer;

        void init(std::string str)
        {
            size_t strSize = str.size();
            const size_t paddingSize = (16 - (strSize % 16));
            const size_t blockSize = (strSize + paddingSize) / 16;
            blocks.resize(blockSize + 1);

            for(uint8_t& chr : blocks[blockSize - 1])
                chr = paddingSize;

            for(int i = 0; i < str.size(); i++)
                blocks[i / 16][i % 16] = str[i];
        }
        void calculate()
        {
            uint8_t last = 0;
            for(int i = 0; i < blocks.size() - 1; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    uint8_t c = blocks[i][j];   
                    blocks[blocks.size() - 1][j] ^= piSubstitution[last ^ c];
                    last = blocks[blocks.size() - 1][j];   
                }
            }
            for(int i = 0; i < blocks.size(); i++)
            {
                for(int j = 0; j < 16; j++)
                    buffer[32 + j] = (buffer[16 + j] = blocks[i][j]) ^ buffer[j];
                uint8_t t = 0;
                for(int j = 0; j < 18; j++)
                {
                    for(int k = 0; k < 48; k++)
                        t = (buffer[k] = buffer[k] ^ piSubstitution[t]);
                    t = (t + j) % 256;
                }
            }
        }
        std::array<uint8_t, 16> getDisgest()
        {
            std::array<uint8_t, 16> r;
            for(int i = 0; i < 16; i++)
                r[i] = buffer[i];
            return r;
        }
    };
};

#endif