; EXPECT: sat
; COMMAND-LINE: 
; COMMAND-LINE: --solve-bv-as-int=sum
(set-logic QF_BV)
(declare-const v (_ BitVec 3))
(assert (not (bvssubo v v)))
(check-sat)