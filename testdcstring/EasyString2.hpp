//
//  EasyString2.hpp
//  TestInt
//
//  Created by john on 16/1/17.
//  Copyright © 2016年 john. All rights reserved.
//

#ifndef EasyString2_hpp
#define EasyString2_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

class $ {
#define $TT template <class T>
    std::stringstream ss;
    typedef const std::string& string_r;
    
    class $value
    {
        string_r src;
        $value(string_r s) : src(s) {}
        friend class $;
    public:
        operator int()      { return atoi(src.c_str()); }
        operator double()   { return atof(src.c_str()); }
    };
    
    class $split
    {
        string_r src, token;
        $split(string_r s, string_r tk) : src(s), token(tk) {}
        friend class $;
    public:
        $TT operator std::vector<T>() const;
    };
    
public:
    std::string         format(const char* format, ...) const __printflike(2, 3);
    $value              parse(string_r src) const                       { return $value(src); }
    $split              split(string_r src, string_r token = ",") const { return $split(src, token); }
    
    std::string&        replace(std::string& base, string_r src, string_r dst) const;
    std::string         replace(string_r base, string_r src, string_r dst) const;
    std::string         replace(string_r src, string_r dst);
    
    $TT std::string     join(const std::vector<T>& src, string_r token = ",") const             { return $().__join(src, token); }
    $TT std::string     join(const std::initializer_list<T>& src, string_r token = ",") const   { return $().__join(src, token); }
    
    operator            std::string() const     { return ss.str(); }
    std::string         str() const             { return ss.str(); }
    $TT T               cast() const            { return T(ss.str()); }
    
    $TT $ operator      + (T arg) const         { return $() << arg; }
    $TT $&operator      + (T arg)               { return *this << arg; }
    $TT $ operator      ()(T arg) const         { return $() << arg; }
    $TT $&operator      ()(T arg)               { return *this << arg; }
    
    $ operator          ()(const std::initializer_list<$>& li) const;    // json.object: $({key, value, ...})
    $ operator          [](const std::initializer_list<$>& li) const;    // json.array: $[{v1, v2, v3, ...}]
    
public:
    $TT $(T t){ *this << t; }
    $(string_r t);
    $($&& r)            : ss(std::move(r.ss)) {}
    
private:
    $() {};
    $(const $& r)       : ss(std::move((std::stringstream&)r.ss)) {}
    friend class        $imp;
    
private:
    $TT $& operator     << (T arg)              { ss << arg; return *this; }
    $&     operator     << (const $& arg)       { ss << arg.ss.str(); return *this; }
    $TT $&              __join(const T& src, string_r token);
};

$TT $& $::__join(const T& src, string_r token)
{
    auto sec_last = src.end();
    --sec_last;
    auto& sss = *this;
    
    int i = 0;
    for (auto it=src.begin(); it!=sec_last && it!=src.end(); ++it) {
        sss << ((const typename T::value_type&)*it);
        if (!token.empty()) {
            sss << token[i++%token.length()];
        }
    }
    if (src.size() > 0) {
        sss << ((const typename T::value_type&)*sec_last);
    }
    
    return *this;
}

$TT $::$split::operator std::vector<T>() const
{
    std::vector<T> ret;
    std::stringstream ss;
    
    auto _pIndex = src.begin();
    auto& _pData = src;
    std::string _value;
    T _v;
    
    while (_pIndex < _pData.end()) {
        auto p = _pIndex;
        while (p < _pData.end() && !strchr(token.c_str(), *p)){
            p++;
        }
        
        _value.assign((const char*)&(*_pIndex), (p-_pIndex));
        _pIndex = p+1;
        
        ss.clear();
        ss << _value;
        ss >> _v;
        
        ret.push_back(_v);
    }
    
    return ret;
}


extern const $& $;

#endif /* EasyString2_hpp */
