(set-logic ALL)
(set-info :status unsat)
(set-option :produce-models true)
(set-option :sets-exp true)
(declare-fun A () (Set (_ BitVec 3)))
(declare-fun B () (Set (_ BitVec 3)))
(declare-fun universe () (Set (_ BitVec 3)))
(declare-fun x () (_ BitVec 3))
(assert (= (set.card A) 5))
(assert (= (set.card B) 5))
(assert (not (= A B)))
(assert (= (set.card (set.inter A B)) 2))
(assert (= (set.card (set.minus A B)) 3))
(assert (= (set.card (set.minus B A)) 3))
(assert (= universe (as set.universe (Set (_ BitVec 3)))))
(assert (not (set.member x A)))
(assert (not (set.member x B)))
(check-sat)