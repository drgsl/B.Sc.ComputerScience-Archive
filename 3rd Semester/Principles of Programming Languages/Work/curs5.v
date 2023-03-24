Require Import String.
Open Scope string_scope.

Inductive AExp :=
| anum : nat -> AExp
| avar : string -> AExp
| aplus : AExp -> AExp -> AExp
| amul : AExp -> AExp -> AExp.

Check (anum 2).
Check (avar "a").
Check (aplus (anum 2) (avar "a")).

(* Coercion *)
Coercion anum : nat >-> AExp.
Coercion avar : string >-> AExp.

Check (aplus (anum 2) (anum 4)).
Check (aplus 2 4).

Check (aplus 2 "a").

(* Notation *)
Notation "A +' B" := (aplus A B) (at level 50, left associativity).
Notation "A *' B" := (amul A B) (at level 40, left associativity).

Check 2 +' "a".


Check (aplus (anum 2) (avar "a")).
Check 2 +' "a".
Check 2 +' "a" *' 4.

Set Printing All.
Check 2 +' "a" *' 4.
Unset Printing All.
Check 2 +' "a" *' 4.

Definition Env := string -> nat.
Definition sigma0 : Env :=
  fun x => 0.

Check sigma0.

Compute sigma0 "x".
Compute sigma0 "y".

Definition sigma' : Env :=
  fun x => if string_dec x "n"
           then 10
           else 0.
Compute sigma' "x".
Compute sigma' "n".

Definition update (e : Env) (x : string) (v : nat) : Env :=
  fun y => if string_dec x y
           then v
           else (e y).

Definition sigma1 := update sigma0 "n" 11.
Compute sigma1 "n".
Compute sigma1 "x".
Print AExp.
Fixpoint aeval (a : AExp) (sigma : Env) : nat :=
  match a with
  | anum n => n
  | avar x => (sigma x)
  | aplus a1 a2 => (aeval a1 sigma) + (aeval a2 sigma)
  | amul a1 a2 => (aeval a1 sigma) * (aeval a2 sigma)
  end.

Compute aeval (2 +' "n") sigma1.
Compute aeval (2 +' "x" +' ("n" *' "n")) sigma1.
Compute aeval "n" sigma1.

Definition sigma2 := update sigma1 "x" 4.
Compute sigma2 "x".
Compute sigma2 "n".

Inductive BExp :=
| btrue : BExp
| bfalse : BExp
| bnot : BExp -> BExp
| band : BExp -> BExp -> BExp
| blt : AExp -> AExp -> BExp
| bgt : AExp -> AExp -> BExp.

Notation "A <' B" := (blt A B) (at level 80).
Notation "A >' B" := (bgt A B) (at level 80).
Notation "! A" := (bnot A) (at level 90).
Infix "&'" := band (at level 93).

Check (2 +' "x" <' "y").
Check ! (2 +' "x" <' "y").
Check 2 +' "x" <' "y" &' ! "x" >' "y".
Set Printing All.
Check (! 2 +' "x" <' "y") &' "x" >' "y".
Unset Printing All.

Check negb.
Check andb.
Check Nat.ltb.
Check Nat.leb.
Fixpoint beval (b : BExp) (sigma : Env) : bool :=
  match b with
  | btrue => true
  | bfalse => false
  | bnot b' => negb (beval b' sigma)
  | band b1 b2 => andb (beval b1 sigma) (beval b2 sigma)
  | blt a1 a2 => Nat.ltb (aeval a1 sigma) (aeval a2 sigma)
  | bgt a1 a2 => negb (Nat.leb (aeval a1 sigma) (aeval a2 sigma))
  end.

Compute beval (2 +' "x" <' "n") sigma2.
Compute beval (2 +' "x" >' "n") sigma2.
Compute beval ("n" >' "n") sigma2.
Compute beval (("n" >' "n") &' !(2 +' "x" <' "n")) sigma2.
Compute beval (!("n" >' "n") &' (2 +' "x" <' "n")) sigma2.

(* statements *)
Inductive Stmt :=
| skip : Stmt
| seq : Stmt -> Stmt -> Stmt
| assign : string -> AExp -> Stmt
| ite : BExp -> Stmt -> Stmt -> Stmt
| while : BExp -> Stmt -> Stmt.

Check skip.
Check assign "x" (2 +' "y").
Check ite ("i" <' "n") (assign "max" "n") (assign "max" "i").

Notation "A ::= B" := (assign A B) (at level 95).
Check ite ("i" <' "n") (
        "max" ::= "n"
      ) (
        "max" ::= "i"
      ).

Notation "A ;; B" := (seq A B) (at level 99, right associativity).

Check "n" ::= 10 ;;
      "i" ::= 0 ;;
      "s" ::= 0 ;;
      while ("i" <' "n" +' 1) (
         "s" ::= "s" +' "i";;
         "i" ::= "i" +' 1
      ).

Fixpoint eval (s : Stmt) (sigma : Env) (gas : nat) : Env :=
  match gas with
  | O => sigma
  | S g' =>   match s with
              | skip => sigma
              | seq s1 s2 => eval s2 (eval s1 sigma g') g'
              | assign x a => update sigma x (aeval a sigma)
              | ite b s1 s2 => if (beval b sigma)
                               then eval s1 sigma g'
                               else eval s2 sigma g'
              | while b s => eval (ite b (seq s (while b s)) skip) sigma g'
              end
  end.

Compute (eval ("n" ::= 11) sigma0 10) "n".

Compute (eval ("n" ::= 11 ;; "i" ::= 100) sigma0 10) "n".
Compute (eval ("n" ::= 11 ;; "i" ::= 100) sigma0 10) "i".

Definition sum := "n" ::= 10 ;;
      "i" ::= 0 ;;
      "s" ::= 0 ;;
      while ("i" <' "n" +' 1) (
         "s" ::= "s" +' "i";;
         "i" ::= "i" +' 1
            ).

Compute eval sum sigma0 1000.

Compute (eval sum sigma0 1000) "s" .
Compute (eval sum sigma0 1000) "i" .


Compute (eval sum sigma0 2) "n".
Compute (eval sum sigma0 50) "s".

Lemma helper :
  forall n, n >= 0.
Proof.
  induction n; auto.
Qed.

Lemma aexp_is_positive:
  forall a sigma,
    aeval a sigma >= 0.
Proof.
  intros.
  apply helper.
Qed.

(* Certified code *)
Require Import Extraction.
Extraction Language Haskell.
Recursive Extraction eval.
