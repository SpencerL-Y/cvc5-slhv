

#include "theory/slhv/theory_slhv_type_rules.h"



#include "theory/builtin/theory_builtin_type_rules.h"
#include "theory/type_enumerator.h"
#include "util/cardinality.h"

namespace cvc5::internal {
namespace theory
{
namespace slhv
{
    


TypeNode SLHVNilTypeRule::preComputeType(NodeManager* nm, TNode n) 
{
    return nm->integerType();
}

TypeNode SLHVNilTypeRule::computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut)
{
    Assert(n.getKind() == Kind::SLHV_NIL);
    return NodeManager->integerType();
}


TypeNode SLHVEmpTypeRule::preComputeType(NodeManager* nm, TNode n) 
{
    TypeNode intType = nm->integerType();
    return nm->mkIntHeapType(intType, intType);
}

TypeNode SLHVEmpTypeRule::computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut)
{
    Assert(n.getKind() == Kind::SLHV_EMP);
    TypeNode intType = NodeManager->integerType();
    return NodeManager->mkIntHeapType(intType, intType);
}

TypeNode SLHVPtoTypeRule::preComputeType(NodeManager* nm, TNode n) 
{
    TypeNode intType = nm->integerType();
    return nm->mkIntHeapType(intType, intType);
}

TypeNode SLHVPtoTypeRule::computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut)
{
    Assert(n.getKind() == Kind::SLHV_PTO);
    TypeNode intType = NodeManager->integerType();
    if(check) 
    {
        for(const Node& nc : n) 
        {
            TypeNode ctype = nc.getTypeOrNull();
            if(!ctype.isInteger()) 
            {
                if(errOut) 
                {
                    (*errOut) << "child of slhv pto is not integer";
                }
                return TypeNode::null();
            }
        }
    }
    return NodeManager->mkIntHeapType(intType, intType);
}



TypeNode SLHVBlkTypeRule::preComputeType(NodeManager* nm, TNode n) 
{
    return nm->booleanType();
}

TypeNode SLHVBlkTypeRule::computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut)
{
    Assert(n.getKind() == Kind::SLHV_BLK);
    TypeNode intType = NodeManager->integerType();
    if(check) 
    {
        TypeNode firstType = n[0].getTypeOrNull();
        if(!firstType.isIntHeap()) 
        {
            if(errOut) 
            {
                (*errOut) << "first child of blk is not intheap type";
            }
            return TypeNode::null();
        }
        TypeNode secondType = n[1].getTypeOrNull();
        TypeNode thirdType = n[2].getTypeOrNull();
        if(!secondType.isInteger() || !thirdType.isInteger()) 
        {
            if(errOut) {
                (*errOut) << "second or third child of blk is not integerd";
            }
            return TypeNode::null();
        }
    }
    return NodeManager->booleanType();
}


TypeNode SLHVDisjUTypeRule::preComputeType(NodeManager* nm, TNode n) {
    TypeNode intType = nm->integerType();
    return nm->mkIntHeapType(intType, intType);
}


TypeNode SLHVDisjUTypeRule::computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut) 
{
    Assert(n.getKind() == Kind::SLHV_DISJU);
    TypeNode intType = NodeManager->integerType();
    if(check) 
    {
        for(const Node& nc : n) 
        {
            TypeNode ctype = nc.getTypeOrNull();
            if(!ctype.isIntHeap())
            {
                if(errOut) 
                {
                    (*errOut) << "some child of disju is not intheap";
                }
                return TypeNode::null();
            }
        }
    }
    return NodeManager->mkIntHeapType(intType, intType);
}


TypeNode SLHVUndefTypeRule::preComputeType(NodeManager* nm, TNode n) 
{
    return nm->booleanType();
}

TypeNode SLHVUndefTypeRule::computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut)
{
    Assert(n.getKind() == Kind::SLHV_UNDEF);
    if(check)
    {
        for(const Node& nc : n) 
        {
            TypeNode ctype = nc.getTypeOrNull();
            if(!ctype.isIntHeap()) 
            {
                if(errOut) 
                {
                    (*errOut) << "child of slhv undefine is not intheap";
                }
                return TypeNode::null();
            }
        }
    }
    return NodeManager->booleanType();
}



// IntHeapProperties implementation
Cardinality IntHeapProperties::computeCardinality(TypeNode type) 
{
    Assert(type.getKind() == Kind::INTHEAP_TYPE);

    Cardinality addrCard = type[0].getCardinality();
    Cardinality contentCard = type[1].getCardinality();
    return  addrCard ^ contentCard;
}

bool IntHeapProperties::isWellFounded(TypeNode type) {
    return type[0].isWellFounded() && type[1].isWellFounded();
}

Node IntHeapProperties::mkGroundTerm(TypeNode type) {
    Assert(type.getKind() == Kind::INTHEAP_TYPE);
    std::cout << "IntHeapProperties::mkGroundTerm" << std::endl;
    return builtin::SortProperties::mkGroundTerm(type);
}

} // namespace slhv
} // namespace theory
}