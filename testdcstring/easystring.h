//
//  $.h
//  test$
//
//  Created by John on 15/6/1.
//  Copyright (c) 2015年 John. All rights reserved.
//

#ifndef __test_S______
#define __test_S______

#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <map>

/**
 *  
 *  例子：
 *  //= $ =====================================
 *  std::string s1 = $("hello world!");
 *  std::string s2 = $("hello world %s %d!", "zg", 10);
 *  std::string s3 = $(10.01f);
 *  std::string s4 = $(false);
 *  std::string s5 = $ + "hello" + " world" + " zg " + 10;
 *
 *  //= $ parse ============================
 *  auto a = $int.parse("100");
 *  auto b = $float.parse("100.1");
 *  auto c = $double.parse("100.1");
 *  auto d = $bool.parse("false"); //"0"及"false"以外都是true
 *
 *  //= $ split ============================
 *  auto v0 = $.split("hello world zg", " ");
 *  auto v1 = $int.split("1,200;2,400", ",;");
 *  auto v2 = $float.split("1,200.01;2,400.02", ",;");
 *  auto v3 = $double.split("1,200.01;2,400.02", ",;");
 *  auto v4 = $bool.split("0,false;1,true", ",;");
 *
 *  //= $ 公开方法 =============================
 *  $.log("format: %d", 10);
 *  auto v5 = $.split("hello world zg", " ");
 *  auto s6 = $.join(v4, ",");
 *
 */

class $
{
#define $T template <class T>
    // 禁止构建对象
private:
    $(const $&);
    $($&&);
    $& operator = (const $&);
    
protected:
    $(){};
    virtual ~$(){};

    // 声明class: in   定义传入参数
public: class in
    {
    public:
        typedef const std::string&          string;
        typedef const char*                 chars;
        typedef std::vector<std::string>    array;
    };

    // 声明class: IParse   解析parse及分割split字符串为目标类型（数组）
    $T class easyparse
    {
    public:
        virtual ~easyparse() {}
        virtual T parse(in::string) const = 0;
        virtual std::vector<T> split(in::string src, in::string token) const = 0;
    };

    // 声明class: easystream    内置 $ 连(+)运算返回值
private:
    class easyvalue;
    class easystream
    {
        std::stringstream ss;
        easystream(){}
        easystream(easystream&& rhs);
        easystream& operator = (easystream&& rhs);
        friend class $;
    public:
        std::string str() const;
        const char* c_str() const;
        // 隐式转转
        operator std::string() const;
        operator in::chars() const;
        // (+)运算
        $T easystream& operator + (const T& arg);
        // (<<)运算
        $T easystream& operator << (const T& arg);
        $::easystream& operator << (bool arg);
        $::easystream& operator << (const easyvalue& arg);
        template<class T1, class T2> easystream& operator << (const std::pair<T1, T2>& arg);
    };
    
private:
    static std::string StringReplace(in::string strBase, in::string strSrc, in::string strDes)
    {
        std::string base = strBase;
        std::string::size_type pos = 0;
        std::string::size_type srcLen = strSrc.size();
        std::string::size_type desLen = strDes.size();
        pos = base.find(strSrc, pos);
        while ((pos != std::string::npos))
        {
            base.replace(pos, srcLen, strDes);
            pos = base.find(strSrc, (pos+desLen));
        }
        return base;
    }
    
    class easyvalue
    {
        easystream ss;
    public:
        $T easyvalue(const T& t) { ss << t; }
        easyvalue(in::string t) { ss << "\"" << StringReplace(StringReplace(t, "\\", "\\\\"), "\"", "\\\"") << "\""; }
        easyvalue(in::chars t) { ss << "\"" << StringReplace(StringReplace(t, "\\", "\\\\"), "\"", "\\\"") << "\""; }
        easyvalue(const easyvalue& t) { ss << t.str(); }
        easyvalue(const easystream& t) { ss << t.str(); }
        easyvalue(const std::initializer_list<easyvalue>& t);
        
        std::string str() const { return ss.str(); }
        operator std::string() const { return str(); }
    };

    // 声明公共函数
public:
    // 打印日志
    int log(in::chars __restrict format, ...) const __printflike(2, 3);

    // 格式化string
    std::string format(in::string format, ...) const;
    std::string format(in::chars format, ...) const __printflike(2, 3);
    std::string format(in::chars format, va_list ap) const;
    
    // 以token分割字符串，token可以多个字符，则每一个字符都为有效分割符
    in::array split(in::string src, in::string token) const;
    
    // 以次用token的每个字符，连接vector中的每个元素为一个新的字符串
    $T easystream join(const T& src, in::string token = ",") const;
    $T easystream join(const std::initializer_list<T>& src, in::string token = ",") const;
    $::easystream join(const std::initializer_list<easyvalue>& src, in::string token = ",") const;
    $T easystream& join(easystream&, const T& src, in::string token = ",") const;

    // 公共运算符函数
public:
    // 声明+运算符，以$开头连接任意数据为string
    // eg: std::string s = $ + "hello" + 10 + false
    $T easystream operator + (const T& arg) const;

    // 声明仿函数，方便$(arg, ...)方式调用
    // 仿函数toString(T)：将任意数据类型转换成string
    $T std::string operator()(const T& arg) const;
    
    // 转成json字符串，初步实现
    easyvalue operator()(const std::initializer_list<easyvalue>& li) const;    // json.object: $({key, value, ...})
    easyvalue operator[](const std::initializer_list<easyvalue>& li) const;    // json.array: $[{v1, v2, v3, ...}]

};

extern const $& $;
extern const class $::easyparse<int>& $int;
extern const class $::easyparse<double>& $double;
extern const class $::easyparse<float>& $float;
extern const class $::easyparse<bool>& $bool;

#include "easystring.inl"


#endif /* defined(__test_S______) */
