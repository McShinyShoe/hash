#ifndef SHINY_BASE_LIB
#define SHINY_BASE_LIB

#include <unordered_map>

#include <iostream>
#define LOG(x) std::cout << x << std::endl

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <string>

namespace shiny
{
    class Base
    {
    private:
        const char* m_chars;
        size_t m_radix;
        
    public:
        const size_t& radix()
        {
            return m_radix;
        }
        size_t encode(const char& chr)
        {
            int i = m_radix;
            while(--i >= 0)
                if(m_chars[i] == chr) return i;
            return -1;
        }
        size_t encode(std::string str)
        {
            size_t multiplier = 1;
            size_t r = 0;
            size_t t;
            for(auto it = str.rbegin(); it != str.rend(); it++)
            {
                if ((t = encode(*it)) == -1) return -1;
                r += t * multiplier;
                multiplier *= m_radix;
            }
            return r;
        }
        const char& find(const size_t& index)
        {
            return m_chars[index];
        }
        std::string decode(size_t num)
        {
            if(num == 0) return std::string(1, m_chars[0]);
            std::string r;
            while(num)
            {
                r.push_back(m_chars[num % m_radix]);
                num /= m_radix;
            }
            //std::reverse(r.begin(), r.end());
            size_t rSize = r.size();
            char t;
            for(size_t i = 0; i < rSize/2; i++)
            {
                t = r[i];
                r[i] = r[rSize - 1 - i];
                r[rSize - 1 - i] = t;
            }
            return r;
        }
        std::string decodeN(size_t num, size_t N)
        {
            std::string r;
            while(N--)
            {
                r.push_back(m_chars[num % m_radix]);
                num /= m_radix;
            }
            //std::reverse(r.begin(), r.end());
            size_t rSize = r.size();
            char t;
            for(size_t i = 0; i < rSize/2; i++)
            {
                t = r[i];
                r[i] = r[rSize - 1 - i];
                r[rSize - 1 - i] = t;
            }
            return r;
        }

        Base() = delete;
        Base(const Base& other) : m_radix(other.m_radix) 
        {
            size_t radix = other.m_radix;
            char* temp = new char[radix];
            while(radix--)
                temp[radix] = other.m_chars[radix];
            m_chars = temp;
        };
        Base(const char* chars, size_t radix) : m_radix(radix) 
        {
            char* temp = new char[radix];
            while(radix--)
                temp[radix] = chars[radix];
            m_chars = temp;
        };
        Base(std::initializer_list<char> list)
        {
            char* temp = new char[list.size()];
            int i = 0;
            for(const char& chr : list)
                temp[i++] = chr;
            m_chars = temp;
            m_radix = list.size();
        };
        ~Base()
        {
            delete m_chars;
        }
    }
    base2({'0', '1'}),
    base8({'0', '1', '2', '3', '4', '5', '6', '7'}),
    base10({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}),
    base16({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}),
    &binary = base2,
    &octal = base8,
    &decimal = base10,
    &hexadecimal = base16;
}


#endif