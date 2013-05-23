/*  This file is part of the Vc library. {{{

    Copyright (C) 2013 Matthias Kretz <kretz@kde.org>

    Vc is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    Vc is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Vc.  If not, see <http://www.gnu.org/licenses/>.

}}}*/

#ifndef VC_COMMON_MASKENTRY_H
#define VC_COMMON_MASKENTRY_H

#include "macros.h"

Vc_NAMESPACE_BEGIN(Common)

template<typename M> class MaskEntry
{
    M &mask;
    size_t offset;
public:
    constexpr MaskEntry(M &m, size_t o) : mask(m), offset(o) {}
    constexpr MaskEntry(const MaskEntry &) = default;
    constexpr MaskEntry(MaskEntry &&) = default;
    Vc_ALWAYS_INLINE MaskEntry &operator=(const MaskEntry &) = default;

    Vc_ALWAYS_INLINE Vc_PURE operator bool() const { const M &m = mask; return m[offset]; }
    Vc_ALWAYS_INLINE bool operator=(bool x) {
        mask.setEntry(offset, x);
        return x;
    }
};

namespace
{
    template<size_t Bytes> struct MaskBoolStorage;
    template<> struct MaskBoolStorage<1> { typedef signed char type; };
    template<> struct MaskBoolStorage<2> { typedef signed short type; };
    template<> struct MaskBoolStorage<4> { typedef signed int type; };
    template<> struct MaskBoolStorage<8> { typedef signed long long type; };
} // anonymous namespace

template<size_t Bytes> class MaskBool
{
    typedef typename MaskBoolStorage<Bytes>::type storage_type Vc_MAY_ALIAS;
    storage_type data;
public:
    MaskBool(bool x) : data(x ? -1 : 0) {}
    MaskBool &operator=(bool x) { data = x ? -1 : 0; return *this; }

    MaskBool(const MaskBool &) = default;
    MaskBool(MaskBool &&) = default;
    MaskBool &operator=(const MaskBool &) = default;

    operator bool() const { return (data & 1) != 0; }
} Vc_MAY_ALIAS;

Vc_NAMESPACE_END

#include "undomacros.h"

#endif // VC_COMMON_MASKENTRY_H