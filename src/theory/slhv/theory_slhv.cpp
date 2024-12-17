#include "theory/slhv/theory_slhv_rewriter.h"
#include "theory/slhv/theory_slhv_type_rules.h"
#include "theory/slhv/theory_slhv.h"


namespace cvc5::internal{
namespace theory {
namespace slhv {

    TheorySLHV::TheorySLHV(Env& env, OutputChannel& out, Valuation valuation) 
        : Theory(THEORY_SLHV, env, out, valuation), 
          d_rewriter(nodeManager()),
          d_state(env, valuation),
          d_im(env, *this, d_state, getStatsPrefix(THEORY_SLHV)),
          d_theory_facts(context())
    {
        d_theoryState = &d_state;
        d_inferManager = &d_im;
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
    
    void TheorySLHV::postCheck(Effort level)
    {
        std::cout << "begin postCheck of theory SLHV !!!!" << std::endl;
        if(level > EFFORT_STANDARD) {
            std::cout << "this is final check" << std::endl;
            for(auto f : this->d_theory_facts) {
                std::cout << "fact: " << f << std::endl;
            }
        }
    }

    /** Notify fact */
    void TheorySLHV::notifyFact(TNode atom, bool pol, TNode fact, bool isInternal) 
    {
        std::cout << "begin notifyFact of theory SLHV !!!" << std::endl;
        std::cout << "atom: " << atom << " fact: " << fact << std::endl;
        this->d_theory_facts.push_back(fact);

    }


}
}
}