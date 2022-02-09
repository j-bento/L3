(* TP2exo4 *)
Section Peano.
Parameter N : Set.
Parameter o : N.
Parameter s : N -> N.
Parameters plus mult : N -> N -> N.
Variables x y : N.
Axiom ax1 : ~((s x) = o).
Axiom ax2 : exists z, ~(x = o) -> (s z) = x.
Axiom ax3 : (s x) = (s y) -> x = y.
Axiom ax4 : (plus x o) = x.
Axiom ax5 : (plus x (s y)) = s (plus x y).
Axiom ax6 : (mult x o) = o.
Axiom ax7 : (mult x (s y)) = (plus (mult x y) x).
End Peano.
(* 1. *)
Lemma plus_1_2 : (plus (s o) (s (s o))) = (s (s (s o))). 
Proof.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.

Lemma plus_2_2 : (plus (s (s o)) (s (s o))) = (s (s (s (s o)))). 
Proof.
rewrite ax5.
rewrite ax5.
rewrite ax4.
reflexivity.
Qed.

Lemma fois_2_2 : (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).
Proof.
rewrite ax7.
rewrite ax7.
rewrite ax6.
rewrite ax5.
rewrite ax5.
rewrite ax5.
rewrite ax5.
rewrite ax4.
rewrite ax4.
reflexivity.
Qed.
(* 2. *)
Ltac autorw := intros;
repeat (rewrite ax7 || rewrite ax5 || rewrite ax6 || rewrite ax4);
try reflexivity.

(* 3. *)
Lemma plus_1_2_v2 : (plus (s o) (s (s o))) = (s (s (s o))). 
Proof.
autorw.
Qed.

Lemma plus_2_2_v2 : (plus (s (s o)) (s (s o))) = (s (s (s (s o)))). 
Proof.
autorw.
Qed.

Lemma fois_2_2_v2 : (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).
Proof.
autorw.
Qed.

(* 4. *)
Hint Rewrite ax5 ax4 ax7 ax6 : axiomes.
Lemma plus_1_2_v3 : (plus (s o) (s (s o))) = (s (s (s o))). 
Proof.
autorewrite with axiomes using try reflexivity.
Qed.

Lemma plus_2_2_v3 : (plus (s (s o)) (s (s o))) = (s (s (s (s o)))). 
Proof.
autorewrite with axiomes using try reflexivity.
Qed.

Lemma fois_2_2_v3 : (mult (s (s o)) (s (s o))) = (s (s (s (s o)))).
Proof.
autorewrite with axiomes using try reflexivity.
Qed.