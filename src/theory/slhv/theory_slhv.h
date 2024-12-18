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

#include "util/rational.h"

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

    /** the list of facts*/
    NodeList d_theory_facts;
    /** other nodes infos */
    NodeSet d_heap_eqs;
    NodeSet d_blks;
    NodeSet d_atomic_hts;
    NodeSet d_hts;
    NodeSet d_pts;
    NodeSet d_end_addresses;
    NodeSet d_undefs;
    /** a vector of endAddress pairs */
    std::vector<std::pair<Node, Node>> d_EAPairs;


    // util functions to determine the type of formulas
    // for literals:
    bool isNot(Node f);
    bool isBlk(Node f);
    bool isUndef(Node f);
    bool isHeapEquality(Node f);
    bool isPostiveLiteral(Node f);

    // for terms:
    bool isPt(Node t);
    bool isHvar(Node t);
    bool isEmp(Node t);
    bool isDisju(Node t);
    bool isHt(Node t);
    bool isAtomicHt(Node t);


    // preprocessing
    void extractHeapTerms(Node t);
    void classifyFormulas(Node f);
    void collectEndAddresses();


    
};
}
}
}
#endif
