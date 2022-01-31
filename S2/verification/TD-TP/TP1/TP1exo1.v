Parameters A B C: Prop.

(* n°1 *)
Goal A -> B -> A. 
intros hyp1 hyp2.
assumption.
Qed.

(* n°2 *)
Goal (A -> B -> C) -> (A -> B) -> A -> C.
intros.
apply (H H1).
apply (H0 H1).
Qed.


(* n°3 *)
Goal A /\ B -> B.
intro.
elim H.
intros.
assumption.
Qed.

(* n°4 *)
Goal B -> A \/ B.
intro.
right.
assumption.
Qed.

(* n°5 *)
Goal (A \/ B) -> ( A -> C ) -> ( B -> C) -> C.
intros.
elim H.
intros.
apply H0.
assumption.
intro.
apply (H1 H2).
Qed.

(* n°6 *)
Goal A -> False -> A.
intro.
auto.
Qed.

(* n°7 *)
Goal False -> A.
intro.
destruct H.
Qed.

(* n°8 *)
Goal (A <-> B) -> A -> B.
intros.
elim H.
intros.
apply (H1 H0).
(*apply H1.
assumption.*)
Qed.

(* n°9 *)
Goal (A <-> B) -> B -> A.
intros.
elim H.
intros.
apply (H2 H0).
(*apply H2.
assumption.*)
Qed.

(* n°10 *)
Goal (A -> B) -> (B -> A ) -> (A <-> B).
intros.
split.
apply H.
apply H0.
Qed.