#include "cvc5_private.h"

#ifndef CVC5__THEORY__SLHV__THEORY_SLHV_H
#define CVC5__THEORY__SLHV__THEORY_SLHV_H

#include <memory>
#include "theory/theory.h"
#include "theory/theory_eq_notify.h"
#include "theory/theory_inference_manager.h"
#include "theory/theory_state.h"
#include "theory/slhv/theory_slhv_rewriter.h"
namespace cvc5::internal {
namespace theory{
namespace slhv {

class TheorySLHV : public Theory {
    public:

    TheorySLHV(Env& env, OutputChannel& out, Valuation valuation);
    ~TheorySLHV();

    TheoryRewriter* getTheoryRewriter() override;
    ProofRuleChecker* getProofChecker() override;
    bool needsEqualityEngine(EeSetupInfo& esi) override;
    void finishInit() override;

    std::string identify() const override { return std::string("TheorySLHV"); }



    //////  MAIN SOLVER
    bool needsCheckLastEffort() override;
    


};
}
}
}
#endif
