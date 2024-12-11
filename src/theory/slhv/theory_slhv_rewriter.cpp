#include "theory/slhv/theory_slhv_rewriter.h"

#include "expr/attribute.h"

namespace cvc5::internal {
namespace theory {
namespace slhv {
    TheorySLHVRewriter::TheorySLHVRewriter(NodeManager* nm) : TheoryRewriter(nm) {}

    // TODO: add post rewrite
    RewriteResponse TheorySLHVRewriter::postRewrite(TNode node) {
        Trace("slhv-postrewrite") << "slhv::postRewrite start " << node << std::endl;

        Trace("slhv-rewrite") << "slhv::rewrite : " << node << " -> " << node << std::endl;
        std::cout << "slhv::postRewrite start " << node << std::endl;
        std::cout << "slhv::rewrite : " << node << " -> " << node << std::endl;
        return RewriteResponse(REWRITE_DONE, node);
    }
}
}
}