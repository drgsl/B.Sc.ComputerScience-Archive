Require Import Coq.Init.Nat.
Require Import String.
Open Scope string_scope.

(* Inductive A :=
|p: A -> A
|q: A -> A
|r: A -> A
|p1: A -> A
|p2: A -> A
|p': A -> A.
Check A. *)

Inductive A :=
|p
|q
|r
|p1
|p2
|p'.
Check A.

Inductive LP : Type :=
|pr : string -> LP
|f : LP
|notf : LP
|notpr : LP -> LP
|andpr : LP -> LP -> LP
|orpr  : LP -> LP -> LP.
Check pr.


Fixpoint eval (p q r p1 p2 p' : A) : bool := true.

Compute eval (p).
Compute eval (q).
Compute eval (r).
Compute eval (p1).
Compute eval (p2).
Compute eval (p').

Fixpoint tau (f : LP) : LP := f.
Fixpoint not (f : LP) : LP := notf.

Compute tau (f).
Compute not (f).

Lemma tau_f_equals_tau_not_not_f:
  forall f, tau (f) = tau ( not ( not (f) ) ).
Proof.
intro f.



