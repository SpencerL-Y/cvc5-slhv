/******************************************************************************
 *
 * Theory of SLHV rewriter.
 */
#include "cvc5_private.h"


#ifndef CVC5__THEORY__SLHV__THEORY_SLHV_REWRITER_H
#define CVC5__THEORY__SLHV__THEORY_SLHV_REWRITER_H

#include "theory/theory_rewriter.h"
#include "theory/type_enumerator.h"

namespace cvc5::internal {
namespace theory {
namespace slhv {
class TheorySLHVRewriter : public TheoryRewriter 
{
    public:
        TheorySLHVRewriter(NodeManager* nm);
        RewriteResponse postRewrite(TNode node) override;
        RewriteResponse preRewrite(TNode node) override
        {
            Trace("slhv-prerewrite") << "slhv::preRewrite returnning" << node << std::endl;
            std::cout << "slhv::preRewrite returnning" << node << std::endl;
            return RewriteResponse(REWRITE_DONE, node);
        }
};




}
}
}



#endif