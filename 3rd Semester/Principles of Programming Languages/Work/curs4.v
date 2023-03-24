(* Limbaj care include:
1. expresii aritmetice + variabile 
2. expresii booleene 
3. Instructiuni (block de instructiuni vid sau nu, atribuiri, if-then-else, while)
 *)

(* 
E := num 
   | var 
   | E + E 
   | E * E
 *)

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
