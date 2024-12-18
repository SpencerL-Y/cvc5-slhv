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
          d_end_addresses(context()),
          d_undefs(context())
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
            }
            for(auto ht : this->d_hts)
            {
                std::cout << "ht: " << ht << std::endl;
            }
            for(auto aht : this->d_atomic_hts)
            {
                std::cout << "aht: " << aht << std::endl;
            }
        } else {
            std::cout << "this is effort standard" << std::endl;
        }
    }

    /** Notify fact */
    void TheorySLHV::notifyFact(TNode atom, bool pol, TNode fact, bool isInternal) 
    {
        std::cout << "begin notifyFact of theory SLHV !!!" << std::endl;
        std::cout << "atom: " << atom << " fact: " << fact << std::endl;
        this->d_theory_facts.push_back(fact);
        if(this->isNot(fact)) 
        {
            std::cout << "negative literal" << std::endl;
        }
        else 
        {
            std::cout << "positive literal" << std::endl;
            // preprocessing
            this->extractHeapTerms(fact);
            this->classifyFormulas(fact);
            this->collectEndAddresses();

            // preRegister formulas induced by the endAddresses
            NodeManager* nm = nodeManager();
            for(auto pair : this->d_EAPairs)
            {
                Node ea_constraint = nm->mkNode(Kind::LT, {pair.first, pair.second});
                this->d_inferManager->propagateLit(ea_constraint);
            }
        }
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

    bool TheorySLHV::isUndef(Node f)
    {
        return (f.getKind() == Kind::SLHV_UNDEF);
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

    bool TheorySLHV::isPostiveLiteral(Node f)
    {
        return (this->isBlk(f) || this->isUndef(f) || this->isHeapEquality(f));
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

    bool TheorySLHV::isHt(Node t)
    {
        if(t.getType().isIntHeap())
        {
            return true;
        } else {
            return false;
        }
    }


    bool TheorySLHV::isAtomicHt(Node t)
    {
        if(this->isPt(t) ||
           this->isHvar(t))
        {
            return true;
        } else {
            return false;
        }   
    }
    
    void TheorySLHV::extractHeapTerms(Node t)
    {
        if(this->isAtomicHt(t))
        {
            if(this->isPt(t))
            {
                this->d_pts.insert(t);
            }
            this->d_hts.insert(t);
            this->d_atomic_hts.insert(t);
        } else if(this->isHt(t)) {
            this->d_hts.insert(t);
        } else {
            
        }

        for(Node child_term : t)
        {
            this->extractHeapTerms(child_term);
        }
    }

    void TheorySLHV::classifyFormulas(Node t)
    {
        if(this->isPostiveLiteral(t)) 
        {
            if(this->isBlk(t))
            {
                this->d_blks.insert(t);
            } else if(this->isHeapEquality(t)) {
                this->d_heap_eqs.insert(t);
            } else if(this->isUndef(t)) {
                this->d_undefs.insert(t);
            }
        } else {
            if(!this->isNot(t))
            {
                std::cout << "ERROR: fact is not literal" << std::endl;
            }
        }
    }

    void TheorySLHV::collectEndAddresses()
    {   
        NodeManager* nm = nodeManager();
        Node constantOne = nm->mkConstInt(Rational(1));
        for(Node f : this->d_blks)
        {
            Node startAddr = f[1];
            Node endAddr = f[2];
            std::cout << "startAddr: " << startAddr  <<  " endAddr: " << endAddr << std::endl;
            this->d_end_addresses.insert(startAddr);
            this->d_end_addresses.insert(endAddr);
            this->d_EAPairs.push_back({startAddr, endAddr});
        }
        for(Node f : this->d_pts)
        { 
            Node startAddr = f[0];
            Node endAddr = nm->mkNode(Kind::ADD, startAddr, constantOne);
            std::cout << "startAddr:  " << startAddr << " endAddr: " << endAddr << std::endl;    
            this->d_end_addresses.insert(startAddr);
            this->d_end_addresses.insert(endAddr);
            this->d_EAPairs.push_back({startAddr, endAddr});
        }
    }

}
}
}