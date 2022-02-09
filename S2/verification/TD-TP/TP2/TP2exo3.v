(* TP2 exo3 *)
Open Scope type_scope.

Section Iso_axioms.

Variables A B C: Set.
Axiom Com : A * B = B * A.
Axiom Ass : A * (B * C) = A * B * C.
Axiom Cur : (A * B -> C) = (A -> B -> C).
Axiom Dis : (A -> B * C) = (A -> B) * (A -> C).
Axiom P_unit : A * unit = A.
Axiom AR_unit : (A -> unit) = unit.
Axiom AL_unit : (unit -> A) = A.

End Iso_axioms.
(* 1. *)
Lemma isos_ex1 : forall A B :Set, A * (B -> unit) = A.
Proof.
intros.
rewrite AR_unit.
rewrite P_unit.
reflexivity.
Qed.

Lemma isos_ex2 : forall A B : Set, A * unit * B = B * (unit * A).
Proof.
intros.
rewrite P_unit.
rewrite Ass.
rewrite P_unit.
apply (Com A B).
Qed.

Lemma isos_ex3 : forall A B C : Set,(A * unit -> B * (C * unit)) =
(A * unit -> (C -> unit) * C) * (unit -> A -> B).
Proof.
intros.
rewrite P_unit.
rewrite AL_unit.
rewrite Dis.
rewrite AR_unit.
rewrite (Com C unit).
apply (Com (A -> B) (A -> unit * C)).
Qed.

(* 2. *)
(* nouvelle tactique *)
Ltac simplifie := intros;
repeat (rewrite P_unit || rewrite AR_unit || rewrite AL_unit || rewrite Ass ||rewrite Dis);
try reflexivity.

(* 3. *)
(* redémonstration *)
Lemma isos_ex1_v2 : forall A B :Set, A * (B -> unit) = A.
Proof.
simplifie.
Qed.

Lemma isos_ex2_v2 : forall A B : Set, A * unit * B = B * (unit * A).
Proof.
intros.
simplifie.
apply (Com A B).
Qed.

Lemma isos_ex3_v2 : forall A B C : Set,(A * unit -> B * (C * unit)) =
(A * unit -> (C -> unit) * C) * (unit -> A -> B).
Proof.
simplifie.
rewrite (Com unit (A -> C)).
simplifie.
apply (Com (A -> B) (A -> C)).
Qed.
