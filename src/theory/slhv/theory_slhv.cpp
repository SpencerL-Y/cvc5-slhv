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
          d_theory_facts(context()),
          d_heap_eqs(context()),
          d_blks(context()),
          d_atomic_hts(context()),
          d_hts(context()),
          d_pts(context()),
          d_end_addresses(context())
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
        if(level > EFFORT_STANDARD) 
        {
            std::cout << "this is final check" << std::endl;
            for(auto f : this->d_theory_facts) 
            {
                std::cout << "fact: " << f << std::endl;
                if(f.getKind() == Kind::NOT) 
                {
                    std::cout << "negative literal" << std::endl;
                } 
                else 
                {
                    std::cout << "positive literal" << std::endl;
                }
            }
        } else 
        {
            std::cout << "this is effort standard" << std::endl;
        }
    }

    /** Notify fact */
    void TheorySLHV::notifyFact(TNode atom, bool pol, TNode fact, bool isInternal) 
    {
        std::cout << "begin notifyFact of theory SLHV !!!" << std::endl;
        std::cout << "atom: " << atom << " fact: " << fact << std::endl;
        this->d_theory_facts.push_back(fact);

    }






    // util functions to determine the type of formulas
    // for literals:
    bool TheorySLHV::isNot(Node f)
    {
        return (f.getKind() == Kind::NOT);
    }

    bool TheorySLHV::isBlk(Node f)
    {
        return (f.getKind() == Kind::SLHV_BLK);
    }

    bool TheorySLHV::isHeapEquality(Node f)
    {
        if(f.getKind() == Kind::EQUAL) 
        {
            if(f[0].getType().isIntHeap()) 
            {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        } 
        
    }

    // for terms:
    bool TheorySLHV::isPt(Node t)
    {
        return (t.getKind() == Kind::SLHV_PTO);
    }

    bool TheorySLHV::isHvar(Node t)
    {
        return (t.isConst() && t.getKind() == Kind::INTHEAP_TYPE);
    }

    bool TheorySLHV::isEmp(Node t)
    {
        return (t.getKind() == Kind::SLHV_EMP);
    }

    bool TheorySLHV::isDisju(Node t)
    {
        return (t.getKind() == Kind::SLHV_DISJU);
    }
}
}
}