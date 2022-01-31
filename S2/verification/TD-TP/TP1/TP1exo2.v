Parameter E: Set.
Parameters P Q: E->Prop.

(* n°1 *)
Goal forall x, P x -> exists y, P y \/ Q y .
intros.
exists x.
left.
assumption.
Qed.

(* n°2 *)
Goal (exists x, P x \/ Q x) -> (exists y, P y) \/ (exists z, Q z).
intro.
elim H.
intros.
destruct H0.
left.
exists x.
assumption.
right.
exists x.
assumption.
Qed.

(* n°3 *)
Goal (forall x, P x) /\ (forall y, Q y) -> (forall z, P z /\ Q z).
intros.
elim H.
intros.
exists.
apply H0.
apply H1.
Qed.

(* n°4 *)
Goal (forall x, P x /\ Q x) -> (forall y, P y) /\ (forall z, Q z).
intro.
exists.
apply H.
apply H.
Qed.

(* n°5 *)
Goal (forall x, ~ P x ) -> ~ ( exists y, P y).
intro.
intro.
elim H0.
apply H.
Qed.

(* n°6 *)
Goal ~(forall x, P x ) -> ( exists y, ~ P y).
intro.
destruct H.
intro.
