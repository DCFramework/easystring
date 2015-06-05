//
//  easystringinl.h
//  easystring
//
//  Created by zhou gang on 15/6/3.
//  Copyright (c) 2015年 zhou gang. All rights reserved.
//

#ifndef __easystring__easystringinl__
#define __easystring__easystringinl__

//屏蔽调试时，$等变量出现在watch窗口中
#ifndef $
#define $           $
#define $int        $int
#define $double     $double
#define $float      $float
#define $bool       $bool
#endif

#ifdef DEBUG
#define $assert(cond, fmt, ...)  do { if( ! ( cond ) ) {\
    $.log("Assertion faild:(%s), function %s, file %s, line: %d\n\tmessage: " fmt, #cond, __func__, __FILE__, __LINE__, ##__VA_ARGS__);    \
    throw new std::exception(); \
}}while(0)
#else
#define $assert(cond, fmt, ...) 
#endif

// = easystream 实现 ====================
//
inline $::easystream::easystream(easystream&& rhs) : ss(std::move(rhs.ss)){}
inline std::string $::easystream::str() const { return ss.str(); }
inline const char* $::easystream::c_str() const { return ss.str().c_str(); }
inline $::easystream::operator std::string() const { return ss.str(); }
inline $::easystream::operator in::chars() const { return ss.str().c_str(); }

$T class $::easystream& $::easystream::operator + (const T& arg)
{
    return (*this << arg);
}

$T class $::easystream& $::easystream::operator << (const T& arg)
{
    ss << arg;
    return *this;
}

inline class $::easystream& $::easystream::operator << (bool arg)
{
    ss << (arg ? "true" : "false");
    return *this;
}

inline $::easystream& $::easystream::operator << (const easyvalue& arg)
{
    ss << arg.str();
    return *this;
}

template<class T1, class T2> $::easystream&  $::easystream::operator << (const std::pair<T1, T2>& arg)
{
    ss << arg.first << ":" << arg.second;
    return *this;
}

// = easystream 结尾 ====================
//

// 以token连接vector中的每个元素为一个新的字符串
$T $::easystream $::join(const T& src, in::string token) const
{
    easystream ss;
    join(ss, src, token);
    return ss;
}

$T $::easystream $::join(const std::initializer_list<T>& src, in::string token) const
{
    easystream ss;
    join(ss, src, token);
    return ss;
}

inline $::easystream $::join(const std::initializer_list<easyvalue>& src, in::string token) const
{
    easystream ss;
    join(ss, src, token);
    return ss;
}

$T $::easystream& $::join(easystream& ss, const T& src, in::string token) const
{
    auto sec_last = src.end();
    --sec_last;

    int i = 0;
    for (auto it=src.begin(); it!=sec_last && it!=src.end(); ++it) {
        ss << ((const typename T::value_type&)*it);
        if (!token.empty()) {
            ss << token[i++%token.length()];
        }
    }
    if (src.size() > 0) {
        ss << ((const typename T::value_type&)*sec_last);
    }
    return ss;
}

// 声明+运算符，以$开头连接任意数据为string
// eg: std::string s = $ + "hello" + 10 + false
$T $::easystream $::operator + (const T& arg) const
{
    easystream es;
    return std::move(es + arg);
}

// 仿函数toString(T)：将任意数据类型转换成string
$T std::string $::operator()(const T& arg) const
{
    easystream ss;
    return (ss << arg).str();
}

inline $::easyvalue $::operator()(const std::initializer_list<easyvalue>& li) const
{
    easystream ss;
    ss << "{"; ::$.join(ss, li, ":,") << "}";
    return ss;
}

inline $::easyvalue $::operator[](const std::initializer_list<easyvalue>& li) const
{
    easystream ss;
    ss << "["; ::$.join(ss, li, ",") << "]";
    return ss;
}

#endif /* defined(__easystring__easystringinl__) */


