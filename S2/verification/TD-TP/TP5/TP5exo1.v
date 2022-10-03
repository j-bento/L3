Require Import Arith.
Require Import Omega.
Require Export List.
Open Scope list_scope.
Import ListNotations.

(* exercice 1 *)



(* 3. *)
Inductive is_sorted : list nat -> Prop :=
  | is_sorted_O_elt : is_sorted nil
  | is_sorted_1_elt : forall e : nat, is_sorted (e :: nil)
  | is_sorted_S : forall e h : nat , forall q : list nat, e <= h -> is_sorted (h::q) -> is_sorted (e::h::q).

(* 4. *)
Goal (is_sorted (1::2::3::nil)).
Proof.
apply is_sorted_S ; auto.
apply is_sorted_S ; auto.
apply is_sorted_1_elt.
Qed.

(* 1. *)
Inductive is_perm : list nat -> list nat -> Prop :=
  | is_perm_reflex : forall l : list nat, is_perm l l
  | is_perm_pos : forall e: nat, forall l1 l2 : list nat, is_perm l1 l2 -> is_perm (e::l1) (e::l2)
  | is_perm_pos_append : forall e: nat, forall l1 l2 : list nat, is_perm l1 l2 -> is_perm (e::l1) (l2++(e::nil))
  | is_perm_sym : forall l1 l2: list nat, is_perm l1 l2 -> is_perm l2 l1
  | is_perm_trans : forall l1 l2 l3: list nat, is_perm l1 l2 -> is_perm l2 l3 -> is_perm l1 l3.

(* 2. *)

Lemma is_perm_ex1 : (is_perm (1::2::3::nil) (3::2::1::nil)).
Proof.
Admitted.

(* exercice 2 *)
(* 1. *)
Check le_dec. (* less or equal decidability *) 
Print sumbool.

Definition le_10 (n : nat) : bool :=
match (le_dec n 10) with
| left _ => true
| right _ => false
end.

Eval compute in le_10 5.
Eval compute in le_10 15.

(* [x] *)
Fixpoint insert (x : nat) (l : list nat) {struct l} : list nat :=
  match l with
    | nil => x::nil
    | e::q => if le_dec x e then x::e::q else e::(insert x q)
  end.

Fixpoint isort (l: list nat) {struct l} : list nat :=
  match l with
    | nil => []
    | e::q => is_sort l = insert e (is_sort q)
  end.

Eval compute in isort [5; 4; 3; 2; 1].
