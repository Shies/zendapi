// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by softboy on 2017/08/08.

#ifndef ZAPI_DS_CALLABLE_VARIANT_H
#define ZAPI_DS_CALLABLE_VARIANT_H

#include "zapi/ds/Variant.h"
#include "zapi/stdext/TypeTraits.h"

namespace zapi
{
namespace lang
{

class Parameters;

} // lang
} // zapi

namespace zapi
{
namespace ds
{

using zapi::lang::Parameters;

class ZAPI_DECL_EXPORT CallableVariant final : public Variant
{
public:
   CallableVariant(const std::function<Variant(Parameters &)> &callable);
   CallableVariant(const std::function<Variant()> &callable);
   CallableVariant(const std::function<void()> &callable);
   CallableVariant(const std::function<void(Parameters &)> &callable);
   Variant operator ()() const;
   template <typename ...Args>
   Variant operator ()(Args&&... args);
   virtual ~CallableVariant();
protected:
   Variant exec(int argc, Variant *argv) const;
};

template <typename ...Args>
Variant CallableVariant::operator ()(Args&&... args)
{
   Variant vargs[] = { static_cast<Variant>(args)... };
   return exec(sizeof...(Args), vargs);
}

} // ds 
} // zapi

#endif // ZAPI_DS_CALLABLE_VARIANT_H
