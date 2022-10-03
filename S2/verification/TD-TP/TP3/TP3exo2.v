(* 1. *)
Open Scope list.
Definition length (A : Type) : list A -> nat :=
  fix length l :=
  match l with
   | nil => O
   | _ :: l' => S (length l')
  end.

Parameter E : Type.
(* 1. *)
Fixpoint rev (l: list E) {struct l} : list E :=
  match l with
   | nil => nil
   | elt :: li => (app (rev li) (elt :: nil))
  end.

(* 2. *)
Lemma exo2_2: forall (l : list E) (e : E), (rev (l ++ (e::nil))) = (e::(rev l)).
Proof.
intros.
elim l.
  simpl.
  reflexivity.
intros.
simpl.
rewrite H.
reflexivity.
Qed.

Lemma exo2_3: forall (l : list E), (rev (rev l)) = l.
Proof.
intros.
elim l.
  simpl.
  reflexivity.
intros.
simpl.
rewrite exo2_2.
rewrite H.
reflexivity.
Qed.







