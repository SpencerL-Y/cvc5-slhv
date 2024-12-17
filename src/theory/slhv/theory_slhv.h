#include "cvc5_private.h"

#ifndef CVC5__THEORY__SLHV__THEORY_SLHV_H
#define CVC5__THEORY__SLHV__THEORY_SLHV_H

#include <memory>
#include "theory/theory.h"
#include "theory/theory_eq_notify.h"
#include "theory/theory_inference_manager.h"
#include "theory/theory_state.h"
#include "theory/slhv/theory_slhv_rewriter.h"

#include "context/cdhashmap.h"
#include "context/cdhashset.h"
#include "context/cdlist.h"
#include "context/cdqueue.h"
namespace cvc5::internal {
namespace theory{
namespace slhv {

class TheorySLHV : public Theory {

    typedef context::CDList<Node> NodeList;
    typedef context::CDHashSet<Node> NodeSet;
    typedef context::CDHashMap<Node, Node> NodeNodeMap;

    public:


    TheorySLHV(Env& env, OutputChannel& out, Valuation valuation);
    ~TheorySLHV();

    TheoryRewriter* getTheoryRewriter() override;
    ProofRuleChecker* getProofChecker() override;
    bool needsEqualityEngine(EeSetupInfo& esi) override;
    void finishInit() override;

    std::string identify() const override { return std::string("TheorySLHV"); }



    //////  MAIN SOLVER

    /** Do we need a check call at last call effort? */
    bool needsCheckLastEffort() override;
    
    /** Post-check, called after the fact queue of the theory is processed. */
    void postCheck(Effort level) override;

    /** Notify fact */
    void notifyFact(TNode atom, bool pol, TNode fact, bool isInternal) override;
        


    // theory plugin attrs
    private: 
    
    TheorySLHVRewriter d_rewriter;

    /** A (default) theory state object */
    TheoryState d_state;
    /** The inference manager */
    TheoryInferenceManager d_im;

    NodeList d_theory_facts;
};
}
}
}
#endif
