#include "cvc5_private.h"


#ifndef CVC5__THEORY__SLHV__TYPE_ENUMERATOR_H
#define CVC5__THEORY__SLHV__TYPE_ENUMERATOR_H

#include "expr/kind.h"
#include "expr/type_node.h"
#include "theory/type_enumerator.h"
#include "util/intheap_value.h"
#include "util/integer.h"

namespace cvc5::internal
{
namespace theory
{
namespace slhv
{

class IntHeapEnumerator : public TypeEnumeratorBase<IntHeapEnumerator>
{
    Integer d_current_max_addr;
    Integer d_current_max_content;
    
    public:
    IntHeapEnumerator(TypeNode type, TypeEnumeratorProperties* tep = nullptr) : TypeEnumeratorBase<IntHeapEnumerator>(type), d_current_max_addr(1), d_current_max_content(0)
    {}

    Node operator*() override 
    {
        TNode addrInt = NodeManager::currentNM()->mkConstInt(d_current_max_addr);
        TNode contentInt = NodeManager::currentNM()->mkConstInt(d_current_max_content);
        return NodeManager::currentNM()->mkNode(Kind::SLHV_PTO, addrInt, contentInt);
    } 

    IntHeapEnumerator& operator++() override {
        d_current_max_addr += 1;
        d_current_max_content += 1;
        return *this;
    }

    bool isFinished() override {return false;}
};


} // namespace slhv

} // namespace theory

    
} // namespace cvc5::internal


#endif