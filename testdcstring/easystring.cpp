//
//  $.cpp
//  test$
//
//  Created by John on 15/6/1.
//  Copyright (c) 2015年 John. All rights reserved.
//

#include "easystring.h"
#include <stdlib.h>


extern const class $::easyparse<std::string>& $string;


std::string $::format(in::chars format, va_list ap) const
{
#define CC_MAX_STRING_LENGTH (1024*100)
    std::string ret;

    char* buf = (char*)malloc(CC_MAX_STRING_LENGTH);
    if (buf != nullptr)
    {
        vsnprintf(buf, CC_MAX_STRING_LENGTH, format, ap);
        ret = buf;
        free(buf);
    }

    return ret;
}

// 忽略va_start的以引用开始的警告
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvarargs"

int $::log(in::chars format, ...) const
{
#ifdef DEBUG
    
    va_list ap;
    va_start(ap, format);
    
    std::string ret = ::$.format(format, ap);
   
    va_end(ap);
    
    printf("$: %s\n", ret.c_str());
    
#endif
    
    return 0;
}

std::string $::format(in::chars format, ...) const
{
    va_list ap;
    va_start(ap, format);

    std::string ret = ::$.format(format, ap);

    va_end(ap);

    return ret;
}

std::string $::format(in::string format, ...) const
{
    va_list ap;
    va_start(ap, format);

    std::string ret = ::$.format(format.c_str(), ap);

    va_end(ap);

    return ret;
}

#pragma clang diagnostic pop

$::easyvalue::easyvalue(const std::initializer_list<easyvalue>& t)
{
    ss << ::$(t).str();
}

$::in::array $::split(in::string src, in::string token) const
{
    return $string.split(src, token);
}


/**
 *  //// extern class imp //
 */

namespace __easyHelper
{
    // $ 实现类
    class __$ : public ${} __$;

    // 分割string辅助方法
    template<class T, class Fun>
    static std::vector<T>& _next(std::vector<T>& target, const std::string& src, const char* split, Fun func)
    {
        auto _pIndex = src.begin();
        auto& _pData = src;
        std::string _value;

        while (_pIndex < _pData.end()) {
            auto p = _pIndex;
            while (p < _pData.end() && !strchr(split, *p)){
                ++p;
            }

            _value.assign((const char*)&(*_pIndex), (p-_pIndex));
            _pIndex = p+1;
            target.push_back(func(_value));
        }
        
        return target;
    }

    // easyparse 实现类
    template <class T, class Fun>
    class __easyparse : public $::easyparse<T>
    {
        typedef std::function<T(const char*)> IParseFun;
    public:
        virtual T parse($::in::string arg) const
        {
            return _fun(arg);
        }
        virtual std::vector<T> split($::in::string src, $::in::string token) const
        {
            std::vector<T> lp;
            return _next(lp, src, token.c_str(), _fun);
        }
        
    public:
        __easyparse(const Fun& fun) : _fun(fun) {}
        Fun _fun;
    };

    // easyparse 构造工厂
    template <class T, class Fun>
    static const __easyparse<T, Fun>& factory(Fun fun)
    {
        static __easyparse<T, Fun> parse(fun);
        return parse;
    }

    // 解析 int
    static inline int intParse($::in::string arg)
    {
        return atoi(arg.c_str());
    }

    // 解析 double
    static inline double floatParse($::in::string arg)
    {
        return strtod(arg.c_str(), NULL);
    }

    // 解析 bool
    static bool boolParse($::in::string arg)
    {
        if (arg.empty()) {
            return false;
        }
        if (arg == "0" || arg == "false" || arg == "False" || arg == "FALSE") {
            return false;
        }
        return true;
    }

    // 解析 string
    static inline std::string stringParse($::in::string arg)
    {
        return arg;
    }
};


const class $& $                                = __easyHelper::__$;
const class $::easyparse<int>& $int             = __easyHelper::factory<int>(__easyHelper::intParse);
const class $::easyparse<float>& $float         = __easyHelper::factory<float>(__easyHelper::floatParse);
const class $::easyparse<double>& $double       = __easyHelper::factory<double>(__easyHelper::floatParse);
const class $::easyparse<bool>& $bool           = __easyHelper::factory<bool>(__easyHelper::boolParse);
const class $::easyparse<std::string>& $string  = __easyHelper::factory<std::string>(__easyHelper::stringParse);



