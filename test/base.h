#pragma once
#include <cstdint>
#include <string>

namespace shiny {
    const char base2chars[] = {'0', '1'};
    const char base10chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const char base16chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    
    class Base {
    private:
        const char* m_characters; 
        uint64_t m_base;
    public:
        void setBase();
        uint64_t encode(std::string text) {
            uint64_t r = 0, num;
            text = setFormat(text);
            for (uint64_t i = 0, j; i < text.size(); i++)
            {
                for (j = 0; j < m_base; j++)
                {
                    if(text[text.size() - i - 1] == m_characters[j]) num = j;
                }
                for (j = 0; j < i; j++)
                {
                    num *= m_base;
                }
                r += num;
            }
            return r;
        };
        std::string setFormat(std::string text) {
            bool isForeign;
            for (uint64_t i = 0, j; i < text.size(); i++)
            {
                isForeign = 1;
                for (j = 0; j < m_base; j++)
                {
                    if(text[i] == m_characters[j]) isForeign = 0;
                }
                if(isForeign) {
                    text.erase(i, 1);
                    i--;
                }
                
            }
            return text;
        }
        std::string decode(uint64_t num)
        {
            std::string buff;
            if(num < m_base) 
            {
                buff.push_back(m_characters[num]);
            }
            else {
                buff.append(decode(num / m_base));
                buff.push_back(m_characters[num % m_base]);
            };
            return buff;
        }
        std::string decodeN(uint64_t num, uint64_t n)
        {
            std::string code = decode(num);
            std::string r;
            for (uint64_t i = 0; i < n; i++)
            {
                r.push_back(m_characters[0]);
            }
            for (uint64_t i = 0; i < n; i++)
            {
                if(!(code.size() - i - 1 >= code.size())) r[n - i - 1] = code[code.size() - i - 1];
            }
            return r;
            
        }
        Base(const char* characters, uint64_t base) : m_characters(characters), m_base(base) {};
        Base() {};
    } 
    base2(base2chars, 2), 
    &binary = base2,
    base10(base10chars, 10), 
    &decimal = base10,
    base16(base16chars, 16),
    &hexadecimal = base16;
}