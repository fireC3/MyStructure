#pragma once
#include <initializer_list>



namespace lty::DataStruct
{

template<typename T, int multiple = 2>
class Lvector
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using refrence = value_type&;
    using const_refrence = const value_type&;

private:
    pointer m_content;
    size_type m_size;
    size_type m_capacity;
public:
    Lvector(): m_content(nullptr), m_size(0), m_capacity(0)
    {}

    Lvector(const size_type size)
    {
        m_content = new value_type[size];
        m_size = size;
        m_capacity = size;
    }

    Lvector(std::initializer_list<value_type> list)
    {
        m_content = new value_type[list.size()];
        m_size = list.size();
        m_capacity = list.size();

        int i = 0;
        for(auto item : list)
        {
            m_content[i++] = item;
        }
    }

    void push_back(value_type val)
    {
        if (m_size >= m_capacity)
            dilatation();

        m_content[m_size++] = val;
    }

    void insert(size_type num, value_type val)
    {
        if (m_size >= m_capacity)
            dilatation();

        num = num > m_size ? m_size : num;

        for (size_type i = m_size; i > num; --i)
        {
            m_content[i] = m_content[i-1];
        }

        m_content[num] = val;

        ++m_size;
    }

    value_type operator[](size_type num)
    {
        return m_content[num];
    }

    // add a simple range detection
    value_type at(size_type num)
    {
        if(num >= 0 && num < m_size)
            return m_content[num];
        else
            throw("out of range");
    }


    size_type capacity() noexcept
    {
        return m_capacity;
    }
    size_type size() noexcept
    {
        return m_size;
    }

    ~Lvector()
    {
        delete[] m_content;
    }

private:
    void dilatation()
    {
        m_capacity = m_capacity * multiple;
        
        pointer new_content = new value_type[m_capacity];

        memcpy(new_content, m_content, sizeof(value_type)*m_size);

        delete[] m_content;

        m_content = new_content;

    }
};

};