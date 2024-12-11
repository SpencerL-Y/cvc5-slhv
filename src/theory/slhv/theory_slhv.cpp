#include "theory/slhv/theory_slhv_rewriter.h"
#include "theory/slhv/theory_slhv_type_rules.h"
#include "theory/slhv/theory_slhv.h"


namespace cvc5::internal{
namespace theory {
namespace slhv {

    TheorySLHV::TheorySLHV(Env& env, OutputChannel& out, Valuation valuation) : 
    Theory(THEORY_SLHV, env, out, valuation), 
    d_rewriter(nodeManager())
    {

    }

    TheorySLHV::~TheorySLHV() 
    {

    }

    TheoryRewriter* TheorySLHV::getTheoryRewriter() 
    {
        return &d_rewriter;
    }

    ProofRuleChecker* TheorySLHV::getProofChecker() 
    {
        return nullptr;
    }

    bool TheorySLHV::needsEqualityEngine(EeSetupInfo& esi) 
    {
        return true;
    }

    void TheorySLHV::finishInit() 
    {

    }

    bool TheorySLHV::needsCheckLastEffort()
    {
        return true;
    }

}
}
}