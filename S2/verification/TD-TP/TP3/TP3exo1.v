
Fixpoint plus (n m : nat) {struct n} : nat :=
match n with
| 0 => m
| S p => S (plus p m) 
end.

(* 1. *)
Fixpoint mult (n m : nat) {struct n} : nat :=
match n with
| 0 => 0
| S p => (plus (mult p m) m)
end.


(* 2. remplace automatiquement (S (S 0)) par 2 *) 
Lemma preuve_2_n: forall n : nat , (mult 2 n) = (plus n n).
Proof.
intro.
simpl.
reflexivity.
Qed.

(* 3. *)
Lemma utile: forall m n : nat , (plus m (S n)) = S (plus m n).
Proof.
intros.
elim m.
  simpl.
  reflexivity.
intros.
simpl.
rewrite H.
reflexivity.
Qed.

Lemma ComPlus: forall m n : nat , (plus m n) = (plus n m).
Proof.
intros.
elim m.
  elim n.
    reflexivity.
  intros.
  simpl.
  rewrite <- H.
  simpl.
  reflexivity.
intros.
simpl.
rewrite H.
rewrite utile.
reflexivity.
Qed.

Lemma preuve_n_2: forall n : nat , (mult n 2) = (plus n n).
Proof.
intro.
elim n.
  reflexivity.
intros.
simpl.
rewrite H.
rewrite <- utile.
rewrite ComPlus.
simpl.
rewrite utile.
rewrite utile.
reflexivity.
Qed.

