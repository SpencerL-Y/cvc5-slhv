; EXPECT: sat
(set-logic ALL)
(set-option :produce-proofs true)
(declare-fun a () Bool)
(declare-fun b () Bool)
(declare-fun c () Bool)
(assert c)
(assert (not b))
(assert (ite a b c))
(check-sat)