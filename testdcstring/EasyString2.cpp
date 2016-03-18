//
//  EasyString2.cpp
//  TestInt
//
//  Created by john on 16/1/17.
//  Copyright © 2016年 john. All rights reserved.
//

#include "EasyString2.hpp"

class $imp : $ { public: static $ $; };
class $ $imp::$;
const class $& $ = $imp::$;

std::string $::format(const char* format, ...) const
{
#define $$_MAX_STRING_LENGTH (1024*100)
    va_list ap;
    va_start(ap, format);
    
    std::string ret;
    
    char* buf = (char*)malloc($$_MAX_STRING_LENGTH);
    if (buf != nullptr)
    {
        vsnprintf(buf, $$_MAX_STRING_LENGTH, format, ap);
        ret = buf;
        free(buf);
    }
    
    va_end(ap);
    
    return ret;
}

std::string& $::replace(std::string& base, string_r src, string_r dst) const
{
    std::string::size_type pos = 0;
    std::string::size_type srcLen = src.size();
    std::string::size_type desLen = dst.size();
    pos = base.find(src, pos);
    while ((pos != std::string::npos))
    {
        base.replace(pos, srcLen, dst);
        pos = base.find(src, (pos+desLen));
    }
    return base;
}

std::string $::replace(string_r base, string_r src, string_r dst) const
{
    std::string strbase = base;
    replace(strbase, src, dst);
    return strbase;
}

std::string $::replace(string_r src, string_r dst)
{
    std::string strbase(std::move(ss.str()));
    replace(strbase, src, dst);
    return strbase;
}

class $ $::operator()(const std::initializer_list<$>& li) const
{
    $ ss;
    ss << "{"; ss.__join(li, ":,") << "}";
    return ss;
}

class $ $::operator[](const std::initializer_list<$>& li) const
{
    $ ss;
    ss << "["; ss.__join(li, ",") << "]";
    return ss;
}

$::$(string_r t)
{
    ss << "\"" << ::$.replace(::$.replace(t, "\\", "\\\\"), "\"", "\\\"") << "\"";
}



