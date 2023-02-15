#ifndef SHINY_SHA_LIB
#define SHINY_SHA_LIB

#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace shiny
{
    template<typename T>
    T ROTL(T x, size_t n)
    {
        size_t w = sizeof(n) * 8;
        return (x << n) | (x >> (w - n));
    };
    template<typename T>
    T ROTR(T x, size_t n)
    {
        size_t w = sizeof(n) * 8;
        return (x >> n) | (x << (w - n));
    };
    template<typename T>
    T CHOICE(T x, T y, T z)
    {
        return (x & y) ^ (~x & z);
    };
    template<typename T>
    T PARITY(T x, T y, T z)
    {
        return x ^ y ^ z;
    };
    template<typename T>
    T MAJOR(T x, T y, T z)
    {
        return (x & y) ^ (x & z) ^ (y & z);
    };
    
    class SHA0
    {
    public:
        static constexpr uint32_t stateInitial[5] = {
            0x67452301,
            0xefcdab89,
            0x98badcfe,
            0x10325476,
            0xc3d2e1f0
        };
        struct
        {
            uint32_t operator[](const size_t index) const
            {
                switch (index / 20)
                {
                case 0:
                    return 0x5a827999;
                case 1:
                    return 0x6ed9eba1;
                case 2:
                    return 0x8f1bbcdc;
                case 3:
                    return 0xca62c1d6;
                default:
                    return 0;
                }
            }
        }
        static constexpr constant = {};
    
    public:
        template<typename T>
        T F(T x, T y, T z, size_t t)
        {
            switch (t / 20)
            {
            case 0:
                return CHOICE(x, y ,z);
            case 1:
                return PARITY(x, y, z);
            case 2:
                return MAJOR(x, y, z);
            case 3:
                return PARITY(x, y, z);
            default:
                return T();
            }
        }    
    
    private:
        std::vector<std::array<uint32_t, 80>> blocks;
        std::vector<std::array<uint32_t, 5>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 64);
            const size_t paddingSize = (512 - (totalSize % 512)) % 512;
            const size_t blockSize = (totalSize + paddingSize) / 512;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 64][(i % 64) / 4] |= ((uint32_t)str[i]) << (8 * (3 - (i % 4)));
            blocks[i / 64][(i % 64) / 4] |= ((uint32_t)(1 << 7)) << (8 * (3 - (i % 4)));

            blocks[blockSize - 1][14] = strSize >> 32;
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = blocks[i][j - 3] ^ blocks[i][j - 8] ^ blocks[i][j - 14] ^ blocks[i][j - 16];

                for(j = 0; j < 5; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint32_t temp = 0;
                for(j = 0; j < 80; j++)
                {
                    temp = ROTL(hashes[i][0], 5) + F(hashes[i][1], hashes[i][2], hashes[i][3], j) + hashes[i][4] + constant[j] + blocks[i][j];
                    hashes[i][4] = hashes[i][3];
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = ROTL(hashes[i][1], 30);
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp;
                }
                for(j = 0; j < 5; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 5> getDisgest()
        {
            std::array<uint32_t, 5> r;
            for(int i = 0; i < 5; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
    };
    class SHA1
    {
    public:
        static constexpr uint32_t stateInitial[5] = {
            0x67452301,
            0xefcdab89,
            0x98badcfe,
            0x10325476,
            0xc3d2e1f0
        };
        struct
        {
            uint32_t operator[](const size_t index) const
            {
                switch (index / 20)
                {
                case 0:
                    return 0x5a827999;
                case 1:
                    return 0x6ed9eba1;
                case 2:
                    return 0x8f1bbcdc;
                case 3:
                    return 0xca62c1d6;
                default:
                    return 0;
                }
            }
        }
        static constexpr constant = {};
    
    public:
        template<typename T>
        T F(T x, T y, T z, size_t t)
        {
            switch (t / 20)
            {
            case 0:
                return CHOICE(x, y ,z);
            case 1:
                return PARITY(x, y, z);
            case 2:
                return MAJOR(x, y, z);
            case 3:
                return PARITY(x, y, z);
            default:
                return T();
            }
        }    
    
    private:
        std::vector<std::array<uint32_t, 80>> blocks;
        std::vector<std::array<uint32_t, 5>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 64);
            const size_t paddingSize = (512 - (totalSize % 512)) % 512;
            const size_t blockSize = (totalSize + paddingSize) / 512;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 64][(i % 64) / 4] |= ((uint32_t)str[i]) << (8 * (3 - (i % 4)));
            blocks[i / 64][(i % 64) / 4] |= ((uint32_t)(1 << 7)) << (8 * (3 - (i % 4)));

            blocks[blockSize - 1][14] = strSize >> 32;
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = ROTL(blocks[i][j - 3] ^ blocks[i][j - 8] ^ blocks[i][j - 14] ^ blocks[i][j - 16], 1);

                for(j = 0; j < 5; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint32_t temp = 0;
                for(j = 0; j < 80; j++)
                {
                    temp = ROTL(hashes[i][0], 5) + F(hashes[i][1], hashes[i][2], hashes[i][3], j) + hashes[i][4] + constant[j] + blocks[i][j];
                    hashes[i][4] = hashes[i][3];
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = ROTL(hashes[i][1], 30);
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp;
                }
                for(j = 0; j < 5; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 5> getDisgest()
        {
            std::array<uint32_t, 5> r;
            for(int i = 0; i < 5; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
    };
    class SHA224
    { 
    public:
        static constexpr uint32_t stateInitial[8] = {
            0xc1059ed8,
            0x367cd507,
            0x3070dd17,
            0xf70e5939,
            0xffc00b31,
            0x68581511,
            0x64f98fa7,
            0xbefa4fa4
        };
        static constexpr uint32_t constant[] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
            0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };
        
    public:
        template<typename T>
        T SIGMA0(T x)
        {
            return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
        }
        template<typename T>
        T SIGMA1(T x)
        {
            return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
        }
        template<typename T>
        T LOWERCASE_SIGMA0(T x)
        {
            return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3);
        }
        template<typename T>
        T LOWERCASE_SIGMA1(T x)
        {
            return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10);
        }
    
    private:
        std::vector<std::array<uint32_t, 64>> blocks;
        std::vector<std::array<uint32_t, 8>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 64);
            const size_t paddingSize = (512 - (totalSize % 512)) % 512;
            const size_t blockSize = (totalSize + paddingSize) / 512;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 64][(i % 64) / 4] |= ((uint32_t)str[i]) << (8 * (3 - (i % 4)));
            blocks[i / 64][(i % 64) / 4] |= ((uint32_t)(1 << 7)) << (8 * (3 - (i % 4)));

            blocks[blockSize - 1][14] = strSize >> 32;
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 64; j++)
                    blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

                for(j = 0; j < 8; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint32_t temp1 = 0, temp2 = 0;
                for(j = 0; j < 64; j++)
                {
                    temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                    temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                    hashes[i][7] = hashes[i][6];
                    hashes[i][6] = hashes[i][5];
                    hashes[i][5] = hashes[i][4];
                    hashes[i][4] = hashes[i][3] + temp1;
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = hashes[i][1];
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp1 + temp2;
                }
                for(j = 0; j < 8; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 7> getDisgest()
        {
            std::array<uint32_t, 7> r;
            for(int i = 0; i < 7; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
    };
    class SHA256
    {
    public:
        static constexpr uint32_t stateInitial[8] = {
            0x6a09e667,
            0xbb67ae85,
            0x3c6ef372,
            0xa54ff53a,
            0x510e527f,
            0x9b05688c,
            0x1f83d9ab,
            0x5be0cd19
        };
        static constexpr uint32_t constant[] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
            0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };
        
    public:
        template<typename T>
        T SIGMA0(T x)
        {
            return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
        }
        template<typename T>
        T SIGMA1(T x)
        {
            return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
        }
        template<typename T>
        T LOWERCASE_SIGMA0(T x)
        {
            return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3);
        }
        template<typename T>
        T LOWERCASE_SIGMA1(T x)
        {
            return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10);
        }
    
    private:
        std::vector<std::array<uint32_t, 64>> blocks;
        std::vector<std::array<uint32_t, 8>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 64);
            const size_t paddingSize = (512 - (totalSize % 512)) % 512;
            const size_t blockSize = (totalSize + paddingSize) / 512;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 64][(i % 64) / 4] |= ((uint32_t)str[i]) << (8 * (3 - (i % 4)));
            blocks[i / 64][(i % 64) / 4] |= ((uint32_t)(1 << 7)) << (8 * (3 - (i % 4)));

            blocks[blockSize - 1][14] = strSize >> 32;
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 64; j++)
                    blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

                for(j = 0; j < 8; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint32_t temp1 = 0, temp2 = 0;
                for(j = 0; j < 64; j++)
                {
                    temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                    temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                    hashes[i][7] = hashes[i][6];
                    hashes[i][6] = hashes[i][5];
                    hashes[i][5] = hashes[i][4];
                    hashes[i][4] = hashes[i][3] + temp1;
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = hashes[i][1];
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp1 + temp2;
                }
                for(j = 0; j < 8; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 8> getDisgest()
        {
            std::array<uint32_t, 8> r;
            for(int i = 0; i < 8; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
    };
    class SHA384
    {
    public:
        static constexpr uint64_t stateInitial[] = {
            0xcbbb9d5dc1059ed8,
            0x629a292a367cd507,
            0x9159015a3070dd17,
            0x152fecd8f70e5939,
            0x67332667ffc00b31,
            0x8eb44a8768581511,
            0xdb0c2e0d64f98fa7,
            0x47b5481dbefa4fa4
        };
        static constexpr uint64_t constant[] = {
            0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
            0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
            0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
            0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
            0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
            0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
            0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
            0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
            0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
            0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
            0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
            0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
            0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
            0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
            0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
            0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
            0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
            0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
            0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
            0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
        };
    
    public:
        template<typename T>
        T SIGMA0(T x)
        {
            return ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39);
        }
        template<typename T>
        T SIGMA1(T x)
        {
            return ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41);
        }
        template<typename T>
        T LOWERCASE_SIGMA0(T x)
        {
            return ROTR(x, 1) ^ ROTR(x, 8) ^ (x >> 7);
        }
        template<typename T>
        T LOWERCASE_SIGMA1(T x)
        {
            return ROTR(x, 19) ^ ROTR(x, 61) ^ (x >> 6);
        }

    private:
        std::vector<std::array<uint64_t, 80>> blocks;
        std::vector<std::array<uint64_t, 8>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 128);
            const size_t paddingSize = (1024 - (totalSize % 1024)) % 1024;
            const size_t blockSize = (totalSize + paddingSize) / 1024;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 128][(i % 128) / 8] |= ((uint64_t)str[i]) << (8 * (7 - (i % 8)));
            blocks[i / 128][(i % 128) / 8] |= ((uint64_t)(1 << 7)) << (8 * (7 - (i % 8)));

            //blocks[blockSize - 1][14];
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

                for(j = 0; j < 8; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint64_t temp1 = 0, temp2 = 0;
                for(j = 0; j < 80; j++)
                {
                    temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                    temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                    hashes[i][7] = hashes[i][6];
                    hashes[i][6] = hashes[i][5];
                    hashes[i][5] = hashes[i][4];
                    hashes[i][4] = hashes[i][3] + temp1;
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = hashes[i][1];
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp1 + temp2;
                }
                for(j = 0; j < 8; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint64_t, 6> getDisgest()
        {
            std::array<uint64_t, 6> r;
            for(int i = 0; i < 6; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
    };
    class SHA512
    {
    public:
        static constexpr uint64_t stateInitial[] = {
            0x6a09e667f3bcc908,
            0xbb67ae8584caa73b,
            0x3c6ef372fe94f82b,
            0xa54ff53a5f1d36f1,
            0x510e527fade682d1,
            0x9b05688c2b3e6c1f,
            0x1f83d9abfb41bd6b,
            0x5be0cd19137e2179
        };
        static constexpr uint64_t constant[] = {
            0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
            0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
            0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
            0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
            0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
            0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
            0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
            0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
            0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
            0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
            0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
            0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
            0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
            0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
            0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
            0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
            0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
            0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
            0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
            0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
        };
        
    public:
        template<typename T>
        T SIGMA0(T x)
        {
            return ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39);
        }
        template<typename T>
        T SIGMA1(T x)
        {
            return ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41);
        }
        template<typename T>
        T LOWERCASE_SIGMA0(T x)
        {
            return ROTR(x, 1) ^ ROTR(x, 8) ^ (x >> 7);
        }
        template<typename T>
        T LOWERCASE_SIGMA1(T x)
        {
            return ROTR(x, 19) ^ ROTR(x, 61) ^ (x >> 6);
        }
        
    private:
        std::vector<std::array<uint64_t, 80>> blocks;
        std::vector<std::array<uint64_t, 8>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 128);
            const size_t paddingSize = (1024 - (totalSize % 1024)) % 1024;
            const size_t blockSize = (totalSize + paddingSize) / 1024;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 128][(i % 128) / 8] |= ((uint64_t)str[i]) << (8 * (7 - (i % 8)));
            blocks[i / 128][(i % 128) / 8] |= ((uint64_t)(1 << 7)) << (8 * (7 - (i % 8)));

            //blocks[blockSize - 1][14];
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

                for(j = 0; j < 8; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint64_t temp1 = 0, temp2 = 0;
                for(j = 0; j < 80; j++)
                {
                    temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                    temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                    hashes[i][7] = hashes[i][6];
                    hashes[i][6] = hashes[i][5];
                    hashes[i][5] = hashes[i][4];
                    hashes[i][4] = hashes[i][3] + temp1;
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = hashes[i][1];
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp1 + temp2;
                }
                for(j = 0; j < 8; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint64_t, 8> getDisgest()
        {
            std::array<uint64_t, 8> r;
            for(int i = 0; i < 8; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
    };
    class SHA512_t
    {

    };
    class SHA512_224
    {
    public:
        static constexpr uint64_t stateInitial[] = {
            0x8C3D37C819544DA2,
            0x73E1996689DCD4D6,
            0x1DFAB7AE32FF9C82,
            0x679DD514582F9FCF,
            0x0F6D2B697BD44DA8,
            0x77E36F7304C48942,
            0x3F9D85A86A1D36C8,
            0x1112E6AD91D692A1
        };
        static constexpr uint64_t constant[] = {
            0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
            0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
            0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
            0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
            0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
            0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
            0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
            0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
            0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
            0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
            0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
            0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
            0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
            0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
            0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
            0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
            0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
            0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
            0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
            0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
        };
        
    public:
        template<typename T>
        T SIGMA0(T x)
        {
            return ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39);
        }
        template<typename T>
        T SIGMA1(T x)
        {
            return ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41);
        }
        template<typename T>
        T LOWERCASE_SIGMA0(T x)
        {
            return ROTR(x, 1) ^ ROTR(x, 8) ^ (x >> 7);
        }
        template<typename T>
        T LOWERCASE_SIGMA1(T x)
        {
            return ROTR(x, 19) ^ ROTR(x, 61) ^ (x >> 6);
        }

    private:
        std::vector<std::array<uint64_t, 80>> blocks;
        std::vector<std::array<uint64_t, 8>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 128);
            const size_t paddingSize = (1024 - (totalSize % 1024)) % 1024;
            const size_t blockSize = (totalSize + paddingSize) / 1024;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 128][(i % 128) / 8] |= ((uint64_t)str[i]) << (8 * (7 - (i % 8)));
            blocks[i / 128][(i % 128) / 8] |= ((uint64_t)(1 << 7)) << (8 * (7 - (i % 8)));

            //blocks[blockSize - 1][14];
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

                for(j = 0; j < 8; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint64_t temp1 = 0, temp2 = 0;
                for(j = 0; j < 80; j++)
                {
                    temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                    temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                    hashes[i][7] = hashes[i][6];
                    hashes[i][6] = hashes[i][5];
                    hashes[i][5] = hashes[i][4];
                    hashes[i][4] = hashes[i][3] + temp1;
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = hashes[i][1];
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp1 + temp2;
                }
                for(j = 0; j < 8; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 7> getDisgest()
        {
            std::array<uint32_t, 7> r;
            for(int i = 0; i < 7; i++)
                r[i] = hashes[hashes.size() - 1][i/2] >> (i % 2 ? 0 : 32);
            return r;
        }
    };
    class SHA512_256
    {
    public:
        static constexpr uint64_t stateInitial[8] = {
            0x22312194FC2BF72C,
            0x9F555FA3C84C64C2,
            0x2393B86B6F53B151,
            0x963877195940EABD,
            0x96283EE2A88EFFE3,
            0xBE5E1E2553863992,
            0x2B0199FC2C85B8AA,
            0x0EB72DDC81C52CA2
        };
        static constexpr uint64_t constant[] = {
            0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
            0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
            0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
            0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
            0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
            0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
            0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
            0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
            0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
            0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
            0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
            0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
            0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
            0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
            0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
            0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
            0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
            0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
            0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
            0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
        };
        
    public:
        template<typename T>
        T SIGMA0(T x)
        {
            return ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39);
        }
        template<typename T>
        T SIGMA1(T x)
        {
            return ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41);
        }
        template<typename T>
        T LOWERCASE_SIGMA0(T x)
        {
            return ROTR(x, 1) ^ ROTR(x, 8) ^ (x >> 7);
        }
        template<typename T>
        T LOWERCASE_SIGMA1(T x)
        {
            return ROTR(x, 19) ^ ROTR(x, 61) ^ (x >> 6);
        }

    private:
        std::vector<std::array<uint64_t, 80>> blocks;
        std::vector<std::array<uint64_t, 8>> hashes;

    public:
        void init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 128);
            const size_t paddingSize = (1024 - (totalSize % 1024)) % 1024;
            const size_t blockSize = (totalSize + paddingSize) / 1024;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 128][(i % 128) / 8] |= ((uint64_t)str[i]) << (8 * (7 - (i % 8)));
            blocks[i / 128][(i % 128) / 8] |= ((uint64_t)(1 << 7)) << (8 * (7 - (i % 8)));

            //blocks[blockSize - 1][14];
            blocks[blockSize - 1][15] = strSize;
        };
        void compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

                for(j = 0; j < 8; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint64_t temp1 = 0, temp2 = 0;
                for(j = 0; j < 80; j++)
                {
                    temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                    temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                    hashes[i][7] = hashes[i][6];
                    hashes[i][6] = hashes[i][5];
                    hashes[i][5] = hashes[i][4];
                    hashes[i][4] = hashes[i][3] + temp1;
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = hashes[i][1];
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp1 + temp2;
                }
                for(j = 0; j < 8; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 8> getDisgest()
        {
            std::array<uint32_t, 8> r;
            for(int i = 0; i < 8; i++)
                r[i] = hashes[hashes.size() - 1][i/2] >> (i % 2 ? 0 : 32);
            return r;
        }
    };
}

#endif 
