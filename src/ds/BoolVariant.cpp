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
// Created by zzu_softboy on 2017/08/08.

#include "zapi/ds/BoolVariant.h"

namespace zapi
{
namespace ds
{

using zapi::ds::internal::VariantPrivate;

BoolVariant::BoolVariant()
   : Variant(false)
{}

BoolVariant::BoolVariant(bool value)
   : Variant(value)
{}

BoolVariant::BoolVariant(const BoolVariant &other)
   : Variant(other)
{}

BoolVariant::BoolVariant(BoolVariant &&other) ZAPI_DECL_NOEXCEPT
   : Variant(std::move(other))
{}

BoolVariant::BoolVariant(const Variant &other)
{
   zval *self = getZvalPtr();
   zval *from = const_cast<zval *>(other.getZvalPtr());
   if (getType() == Type::Boolean) {
      ZVAL_BOOL(self, Z_TYPE_INFO_P(from) == IS_TRUE);
   } else {
      zval temp;
      ZVAL_DUP(&temp, from);
      convert_to_boolean(&temp);
      ZVAL_COPY_VALUE(self, &temp);
   }
}

BoolVariant::BoolVariant(Variant &&other)
   : Variant(std::move(other))
{
   if (getType() != Type::Boolean) {
      convert_to_boolean(getZvalPtr());
   }
}

BoolVariant &BoolVariant::operator=(const BoolVariant &other)
{
   if (this != &other) {
      ZVAL_BOOL(getZvalPtr(), Z_TYPE_INFO_P(other.getZvalPtr()) == IS_TRUE);
   }
   return *this;
}

BoolVariant &BoolVariant::operator=(BoolVariant &&other) ZAPI_DECL_NOEXCEPT
{
   assert(this != &other);
   m_implPtr = std::move(other.m_implPtr);
   return *this;
}

BoolVariant &BoolVariant::operator=(const Variant &other)
{
   ZVAL_BOOL(getZvalPtr(), other.toBool());
   return *this;
}

BoolVariant &BoolVariant::operator=(Variant &&other)
{
   m_implPtr = std::move(other.m_implPtr);
   if (getType() != Type::Boolean) {
      convert_to_boolean(getZvalPtr());
   }
   return *this;
}

BoolVariant &BoolVariant::operator=(bool value)
{
   ZVAL_BOOL(getZvalPtr(), value);
   return *this;
}

BoolVariant::~BoolVariant()
{}

BoolVariant::operator bool() const
{
   return toBool();
}

bool BoolVariant::toBool() const ZAPI_DECL_NOEXCEPT
{
   return Z_TYPE_INFO_P(getZvalPtr()) == IS_TRUE ? true : false;
}

bool operator ==(const BoolVariant &lhs, const BoolVariant &rhs)
{
   return lhs.toBool() == rhs.toBool();
}

bool operator !=(const BoolVariant &lhs, const BoolVariant &rhs)
{
   return lhs.toBool() != rhs.toBool();
}

} // ds
} // zapi