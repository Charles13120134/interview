#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码
    //len_ is set already
    inline void string::getNewData(const char* s){
        data_ = (char*)malloc(len_ + 1);
        size_t i = 0;
        for(; i < len_; i++)
            data_[i] = s[i];
        data_[i] = '\0';
    }

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
        : data_(NULL), len_(0)
    {
        if(NULL == s)
            return;
        for(size_t i = 0; s[i] != '\0'; i++)
            len_++;
        getNewData(s);
    }

    string::string( const char* s, size_t len )
        : data_(NULL), len_(0)
    {
        if(NULL == s)
            return;
        for(size_t i = 0; s[i] != '\0' && i < len; i++)
            len_++;
        getNewData(s);
    }

    string::string( const string& rhs )
        : data_(NULL), len_(0)
    {
        if(NULL == rhs.data_)
            return;
        len_ = rhs.len_;
        getNewData(rhs.data_);
    }

    string& string::operator=( const string& rhs )
    {
        free(data_);
        data_ = NULL;
        len_ = 0;
        if(NULL == rhs.data_)
            return *this;
        len_ = rhs.len_;
        getNewData(rhs.data_);
        return *this;
    }

    string::~string()
    {
        free(data_);
        data_ = NULL;
        len_ = 0;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        if(NULL != data_)
            data_[len_] = ' ';
        return data_;
    }

    const char* string::c_str() const
    {
        if(NULL != data_)
            data_[len_] = '\0';
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        return data_ + index;
    }
}
