#ifndef SHINY_STRNUM_H
#define SHINY_STRNUM_H

#include <string>
#include <ostream>
#include <cstdint>
#include "base.h"

namespace shiny
{
    class StrNum
    {
    private:
        Base& m_base;
        std::string m_num;
        
    public:
        void rComplement()
        {
            for(char& chr : m_num)
                chr = m_base.find(m_base.radix() - m_base.encode(chr) - 1);
        };
        void r_1Complement()
        {
            rComplement();
        };

        StrNum() : m_base(base10) {};
        StrNum(const StrNum& other) : m_base(other.m_base), m_num(other.m_num) {};
        StrNum(Base& base) : m_base(base) {}

        operator std::string()
        {
            return m_num;
        }
        StrNum& operator=(int64_t num)
        {
            m_num = m_base.decode(num);
            return *this;
        }
        friend StrNum operator+(const StrNum& a, const StrNum& b)
        {
            StrNum r;
            return r;
        };
        friend StrNum operator-(const StrNum& a, const StrNum& b)
        {
            StrNum r;
            return r;
        };
        // [int, strnum]
        // [strnum, int]
        friend std::ostream& operator<<(std::ostream& stream, const StrNum& strNum)
        {
            stream << '(' << strNum.m_num << ")_" << strNum.m_base.radix();
            return stream;
        }
    };
};

#endif