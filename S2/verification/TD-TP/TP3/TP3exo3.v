Parameter S : Set.
Inductive FProp : Set :=
  | Symb: S -> FProp
  | Not : FProp -> FProp
  | And : FProp -> FProp -> FProp
  | Or : FProp -> FProp -> FProp 
  | Impl : FProp -> FProp -> FProp
  | Equ : FProp -> FProp -> FProp.

Parameter a b c : S.

Check (Symb a).

Check (Not (And (Symb a) (Symb b))).

Fixpoint nbc (f : FProp) {struct f} : nat :=
  match f with
    | (Symb s) => 0
    | (Not g) => 1 + (nbc g)
    | (And g h) => 1 + (nbc g) + (nbc h)
    | (Or g h) => 1 + (nbc g) + (nbc h)
    | (Impl g h) => 1 + (nbc g) + (nbc h)
    | (Equ g h) => 1 + (nbc g) + (nbc h)
  end.

Check (nbc (And (Not (Symb a)) (Symb b)) = 2). 

(* Fixpoint sub (f : FProp) {struct f} : list FProp :=
  match f with
    | (Symb s) => s::nil
    | (Not g) => (Not g) :: (sub g)
    | (And g h) => (sub g) ++ (sub h)
    | (Or g h) => 
    | (Impl g h) =>
    | (Equ g h) => 
  end. *)