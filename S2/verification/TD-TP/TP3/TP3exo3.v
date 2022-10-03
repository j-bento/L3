Parameter S : Set.
Inductive FProp : Set :=
  | Symb: S -> FProp
  | Not : FProp -> FProp
  | And : FProp -> FProp -> FProp
  | Or : FProp -> FProp -> FProp 
  | Imp : FProp -> FProp -> FProp
  | Equ : FProp -> FProp -> FProp.

Parameter a b c : S.

Check (Symb a).

Check (Not (And (Symb a) (Symb b))).

Fixpoint sub (F : FProp) {struct F} : list FProp :=
  match F with
    | (Symb F) => (Symb F) :: nil
    | (Not Q) => F :: (sub Q)
    | (And Q R) => F :: (sub Q) ++ (sub R)
    | (Or Q R) => F :: (sub Q) ++ (sub R)
    | (Imp Q R) => F :: (sub Q) ++ (sub R)
    | (Equ Q R) => F :: (sub Q) ++ (sub R)
  end.

Fixpoint nbc (f : FProp) {struct f} : nat :=
  match f with
    | (Symb s) => 0
    | (Not g) => 1 + (nbc g)
    | (And g h) => 1 + (nbc g) + (nbc h)
    | (Or g h) => 1 + (nbc g) + (nbc h)
    | (Imp g h) => 1 + (nbc g) + (nbc h)
    | (Equ g h) => 1 + (nbc g) + (nbc h)
  end.

Check (nbc (And (Not (Symb a)) (Symb b)) = 2).

Lemma lsLgtInd : forall L1 L2 : list FProp, (length (L1 ++ L2)) = (length L1) + (length L2).
Proof.
  intros.
  elim L1.
    simpl.
    reflexivity.

    intros.
    simpl.
    rewrite H.
    reflexivity.
Qed.

Require Export Omega.

Goal forall F : FProp, (length (sub F)) <=  (2 * (nbc F)) + 1.
Proof.
intro.
simpl.
elim F.
intro.
simpl.
trivial.
intros.
simpl.
omega.
intros; simpl; trivial; rewrite lsLgtInd; omega.
intros; simpl; trivial; rewrite lsLgtInd; omega.
intros; simpl; trivial; rewrite lsLgtInd; omega.
intros; simpl; trivial; rewrite lsLgtInd; omega.
Qed.