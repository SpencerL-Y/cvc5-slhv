#include "cvc5_public.h"

#ifndef CVC5__INTHEAP_VALUE_H
#define CVC5__INTHEAP_VALUE_H

#include "base/check.h"
#include "base/exception.h"

#include "util/integer.h"


namespace cvc5::internal
{
    
class IntHeapValue 
{
    private:
        Integer address;
        Integer content;
    public: 
        IntHeapValue(const Integer& addr, const Integer& cont) : address(addr), content(cont) {}
        ~IntHeapValue() {}

        IntHeapValue& operator=(const IntHeapValue& i) {
            if(this == &i) {
                return *this;
            }
            address = i.address;
            content = i.content;
            return *this;
        }
};
} // namespace cvc5::internal


#endif