
#include "cvc5_private.h"

#ifndef CVC5__THEORY__SLHV__THEORY_SLHV_TYPE_RULES_H
#define CVC5__THEORY__SLHV__THEORY_SLHV_TYPE_RULES_H
#include "expr/node.h"
#include "expr/type_node.h"

namespace cvc5::internal
{
namespace theory
{
namespace slhv
{
struct SLHVNilTypeRule 
{
        static TypeNode preComputeType(NodeManager* nm, TNode n);
        static TypeNode computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut);
};


struct SLHVEmpTypeRule 
{
        static TypeNode preComputeType(NodeManager* nm, TNode n);
        static TypeNode computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut);
};


struct SLHVPtoTypeRule 
{
        static TypeNode preComputeType(NodeManager* nm, TNode n);
        static TypeNode computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut);
};

struct SLHVBlkTypeRule 
{
        static TypeNode preComputeType(NodeManager* nm, TNode n);
        static TypeNode computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut);
};

struct SLHVDisjUTypeRule 
{
        static TypeNode preComputeType(NodeManager* nm, TNode n);
        static TypeNode computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut);
};

struct SLHVUndefTypeRule 
{
        static TypeNode preComputeType(NodeManager* nm, TNode n);
        static TypeNode computeType(NodeManager* NodeManager, 
                                    TNode n,
                                    bool check,
                                    std::ostream* errOut);
};

struct IntHeapProperties {
    static Cardinality computeCardinality(TypeNode type);

    static bool isWellFounded(TypeNode type);

    static Node mkGroundTerm(TypeNode type);
};



} // namespace slhv

} // namespace theory

} // namespace cvc5::internal



#endif