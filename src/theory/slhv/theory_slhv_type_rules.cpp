

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


// struct SLHVEmpTypeRule 
// {
//         static TypeNode preComputeType(NodeManager* nm, TNode n);
//         static TypeNode computeType(NodeManager* NodeManager, 
//                                     TNode n,
//                                     bool check,
//                                     std::ostream* errOut);
// };


// struct SLHVPtoTypeRule 
// {
//         static TypeNode preComputeType(NodeManager* nm, TNode n);
//         static TypeNode computeType(NodeManager* NodeManager, 
//                                     TNode n,
//                                     bool check,
//                                     std::ostream* errOut);
// };

// struct SLHVBlkTypeRule 
// {
//         static TypeNode preComputeType(NodeManager* nm, TNode n);
//         static TypeNode computeType(NodeManager* NodeManager, 
//                                     TNode n,
//                                     bool check,
//                                     std::ostream* errOut);
// };

// struct SLHVDisjUTypeRule 
// {
//         static TypeNode preComputeType(NodeManager* nm, TNode n);
//         static TypeNode computeType(NodeManager* NodeManager, 
//                                     TNode n,
//                                     bool check,
//                                     std::ostream* errOut);
// };

// struct SLHVUndefTypeRule 
// {
//         static TypeNode preComputeType(NodeManager* nm, TNode n);
//         static TypeNode computeType(NodeManager* NodeManager, 
//                                     TNode n,
//                                     bool check,
//                                     std::ostream* errOut);
// };



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