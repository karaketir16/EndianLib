#pragma once

#include <cstdint>
#include <climits>
#include <bit>




#if defined(__linux__) || defined(__CYGWIN__)
#include <endian.h>
#endif

#ifndef __cpp_lib_endian
namespace std {
enum class endian{
    big,
    little
};
}
#else
static_assert(
    (std::endian::native == std::endian::big) ||
        (std::endian::native == std::endian::little)
    , "byte order must be little or big");
#endif

#ifdef BYTE_ORDER
#if (BYTE_ORDER == BIG_ENDIAN) || (BYTE_ORDER == BIG_ENDIAN)
#error "byte order must be little or big"
#endif
#endif


#pragma pack(push, 1)

namespace _endian_ {


template <typename T>
T swap_endian(T u) //https://stackoverflow.com/a/4956493
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

static bool is_little_endian(){
#ifdef __cpp_lib_endian
    return std::endian::native == std::endian::little;
#elif defined(BYTE_ORDER)
    return BYTE_ORDER == LITTLE_ENDIAN;
#else
    int x = 1;
    char *c = reinterpret_cast<char*>(&x);
    return c[0];

#endif
}


static bool IsSameEndian(std::endian e){
    static const bool is_le = is_little_endian();
    switch (e)
    {
    case std::endian::big:
        return !is_le;
        break;
    case std::endian::little:
        return is_le;
        break;
    }
    return false;
};


template<typename T, std::endian e>
struct _E_Base{

    _E_Base(const T& x = 0){
        if(IsSameEndian(e)){
            this->val = x;
        } else {
            this->val = swap_endian(x);
        }
    }

    operator T() const{
        if(IsSameEndian(e)){
            return this->val;
        } else {
            return swap_endian(this->val);
        }
    }

    template<typename other>
    operator _E_Base<other, std::endian::big>() const {
        _E_Base<other, std::endian::big> temp = static_cast<T>(*this);
        return temp;
    }

    template<typename other>
    operator _E_Base<other, std::endian::little>() const {
        _E_Base<other, std::endian::little> temp = static_cast<T>(*this);
        return temp;
    }

    _E_Base& operator++(){
        (*this) = static_cast<T>(*this) + 1;
        return *this;
    }

    _E_Base operator++(int){
        _E_Base temp = *this;
        ++(*this);
        return temp;
    }

    _E_Base& operator--(){
        (*this) = (*this) + 1;
        return *this;
    }

    _E_Base operator--(int){
        _E_Base temp = *this;
        --(*this);
        return temp;
    }

    _E_Base& operator+=(const _E_Base& other) {
        *this = *this + other;
        return *this;
    }

    _E_Base& operator-=(const _E_Base& other) {
        *this = *this - other;
        return *this;
    }

    _E_Base& operator*=(const _E_Base& other) {
        *this = *this * other;
        return *this;
    }

    _E_Base& operator/=(const _E_Base& other) {
        *this = *this / other;
        return *this;
    }

    _E_Base& operator%=(const _E_Base& other) {
        *this = *this % other;
        return *this;
    }

    _E_Base& operator&=(const _E_Base& other) {
        *this = *this & other;
        return *this;
    }

    _E_Base& operator|=(const _E_Base& other) {
        *this = *this | other;
        return *this;
    }

    _E_Base& operator^=(const _E_Base& other) {
        *this = *this ^ other;
        return *this;
    }

    _E_Base& operator<<=(const _E_Base& other) {
        *this = *this << other;
        return *this;
    }

    _E_Base& operator>>=(const _E_Base& other) {
        *this = *this >> other;
        return *this;
    }

protected:
    T val;
} __attribute__((packed));


#define _CREATE_ENDIAN_TYPE(x) \
typedef _endian_::_E_Base<x, std::endian::big> be_##x;\
    typedef _endian_::_E_Base<x, std::endian::little> le_##x;


}

_CREATE_ENDIAN_TYPE(int8_t)
_CREATE_ENDIAN_TYPE(int16_t)
_CREATE_ENDIAN_TYPE(int32_t)
_CREATE_ENDIAN_TYPE(int64_t)

_CREATE_ENDIAN_TYPE(uint8_t)
_CREATE_ENDIAN_TYPE(uint16_t)
_CREATE_ENDIAN_TYPE(uint32_t)
_CREATE_ENDIAN_TYPE(uint64_t)

_CREATE_ENDIAN_TYPE(float)
_CREATE_ENDIAN_TYPE(double)


#pragma pack(pop)