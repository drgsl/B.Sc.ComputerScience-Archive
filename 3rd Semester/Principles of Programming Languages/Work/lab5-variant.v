(*EX1*)
Require Import Coq.Init.Nat.
Require Import String.
Open Scope string_scope.

Inductive Exp := 
| num : nat -> Exp
| var : string -> Exp
| add : Exp -> Exp -> Exp
| sub : Exp -> Exp -> Exp
| div : Exp -> Exp -> Exp.

Coercion num : nat >-> Exp.
Coercion var : string >-> Exp.

(*Antrenament*)
Definition Env := string -> nat.

Definition Sigma0 : Env := fun x => 0.

Fixpoint update (e : Env) (x : string) (v : nat) : Env :=
  fun y => if string_dec x y
           then v
           else (e y).
Definition Sigma1 : Env := update Sigma0 "n" 10.
Compute Sigma1 "n".
Definition Sigma2 : Env := update Sigma1 "x" 60.
Compute Sigma2 "x".
Definition Sigma3 : Env := update Sigma2 "y" 5.
Compute Sigma3 "y".
Compute Sigma3 "x".



Check option.
Check option nat.
Print option.
Check (Some 2).
Check None.

Fixpoint aeval (a : Exp) (sigma : Env) : option nat :=
  match a with
  | num n => Some n
  | var x => Some (sigma x)
  | add a1 a2 => match aeval a1 sigma, aeval a2 sigma with
                  | Some v1, Some v2 => Some (v1 + v2)
                  | _, _ => None
                  end
  | sub a1 a2 => match aeval a1 sigma, aeval a2 sigma with
                 | Some v1, Some v2 => if Nat.ltb v1 v2 
                                       then None
                                       else Some (Nat.sub v1 v2)
                 | _, _ => None
                 end
  | div a1 a2 => match aeval a1 sigma, aeval a2 sigma with
                 | Some v1, Some v2 => if Nat.leb v1 v2 
                                       then Some (v1 / v2)
                                       else None
                 | _, _ => None
                 end
  end.

Inductive Cond :=
| base : bool -> Cond
| bnot : Cond -> Cond
| beq  : Exp -> Exp -> Cond 
| less : Exp -> Exp -> Cond
| band : Cond -> Cond -> Cond.

Coercion base: bool >-> Cond.

Check negb.
Check andb.
Check Nat.ltb.
Check Nat.leb.

Fixpoint beval (b : Cond) (sigma : Env) : option bool :=
  match b with
  | base b => Some b
  | bnot b' => match beval b' sigma with
               | Some c => Some (negb c)
               | _ => None
               end
  | band b1 b2 => match beval b1 sigma, beval b2 sigma with
                  | Some c1, Some c2 => Some (andb c1 c2)
                  | _, _ => None
                  end
  | beq a1 a2 => match aeval a1 sigma, aeval a2 sigma with
                 | Some v1, Some v2 => Some (Nat.eqb v1 v2)
                 | _, _ => None
                 end
  | less a1 a2 => match  aeval a1 sigma, aeval a2 sigma with
                  | Some v1, Some v2 => Some (Nat.ltb v1 v2)
                 | _, _ => None
                  end
  end.

Compute (beval (bnot (base false)) Sigma0).
Compute (beval (band (base true) (base true))) Sigma0.

Inductive Stmt :=
| skip : Stmt 
| assign : string -> Exp -> Stmt
| seq : Stmt -> Stmt -> Stmt
| ite : Cond -> Stmt -> Stmt -> Stmt
| it  : Cond -> Stmt -> Stmt
| dowhile : Stmt -> Cond -> Stmt.

Fixpoint eval (s : Stmt) (sigma : Env) (gas : nat) : option Env :=
  match gas with
  | 0 => Some sigma
  | S g' =>   match s with
              | skip => Some sigma
              | seq s1 s2 => match eval s1 sigma g' with
                             | Some sg => eval s2 sg g'
                             | _ => None
                             end
              | assign x a => match (aeval a sigma) with
                              | Some v1 => Some (update sigma x v1)
                              | _ => None
                              end
              | ite b s1 s2 => match beval b sigma with
                               | Some b1 => if b1
                                            then eval s1 sigma g'
                                            else eval s2 sigma g'
                               | None => None
                               end
              | it b s => match beval b sigma with
                          | Some b1 => if b1
                                       then eval s sigma g'
                                       else Some sigma
                          | None => None
                          end

              | dowhile s b => eval (seq s (ite b (dowhile s b) skip)) sigma g'
              end
   end.

Notation "A +' B" := (add A B) (at level 50, left associativity).
Notation "A -' B" := (sub A B) (at level 50, left associativity).
Notation "A /' B" := (div A B) (at level 40, left associativity).


Notation "! A" := (bnot A) (at level 90).
Notation "A &' B" := (band A B) (at level 93).
Notation "A =' B" := (beq A B) (at level 80).
Notation "A <' B" := (less A B) (at level 80).
Notation "A >' B" := (band (bnot (beq A B)) (bnot (less A B))) (at level 80).
Notation "A |' B" := (bnot (band (bnot A) (bnot B))) (at level 93).
Notation "A <=' B" := (band (less A B) (beq A B)) (at level 80).
Notation "A >=' B" := (bnot (less A B)) (at level 80).

Notation "A ::= B" := (assign A B)(at level 95).
Notation "A ;; B" := (seq A B) (at level 99, right associativity).


Definition cmmdc (a b : string) (inp1 inp2 : Exp) :=
  a ::= inp1 ;;
  b ::= inp2 ;;
ite ( a =' 0 |' b =' 0) (
    "resultat" ::= 0 (* aici nu e chiar corect, mai ales daca ambele sunt 0 *)
    ) (
    ite (a =' b) (
        "resultat" ::= a       
        )(
        (dowhile (ite ( a >' b ) (
                      a ::= a -' b
                     ) (
                      b ::= b -' a
                     )
                )
                (! a =' b)
          );;          
       "resultat" ::= a
        )
    ).

Definition Env1 : Env := update Sigma0 "a" 25.
Definition Env2 : Env := update Env1 "b" 5.

(*Compute (eval (cmmdc "a" "b") Env2 1000).*)

Compute (beval (! false) Sigma0).
Compute (beval ( "b" =' 1 &'  "a" =' 0)) Env2.
Compute (beval (band (beq "b" 1) (beq "a" 0)) Sigma0).

Compute match (eval (cmmdc "a" "b" 10 12) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 12 10) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 10 15) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 7 2) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 2 7) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 700 250) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 700 350) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (cmmdc "a" "b" 0 0) Env2 100) with
        |Some env => env "resultat"
        |None => 666
        end. (* rezultatul aici n-ar trebui sa fie 0, ar trebui aruncata o eroare dar nu tratam asta in programe inca *)




(* EX6 *)

Definition fibb (n : Exp) :=
"i" ::= 1 ;;
"x" ::= 0 ;;
"y" ::= 1 ;;
"z" ::= 0 ;;
ite ( n =' 0) (
      "resultat" ::= "x")
    ( (* else *)
      ite (n =' 1) (
            "resultat" ::= "y"
      ) (* else *)
      ( dowhile (
            "z" ::= "x" +' "y" ;;
            "x" ::= "y" ;;
            "y" ::= "z" ;;
            "i" ::= "i" +' 1
          ) ("i" <' n) ;;
        "resultat" ::= "z"
      )
    ).


(* Output-ul la care ma astept: 0, 1, 1, 2, 3, 5, ... <- secv fibonacci *)
(* pentru input-urile (indici): 0, 1, 2, 3, 4, 5, ... <- de ex: fibb 4 returneaza 3 *)
Compute match (eval (fibb 0) Env2 20) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (fibb 1) Env2 20) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (fibb 2) Env2 20) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (fibb 3) Env2 20) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (fibb 4) Env2 20) with
        |Some env => env "resultat"
        |None => 666
        end.
Compute match (eval (fibb 5) Env2 20) with
        |Some env => env "resultat"
        |None => 666
        end.
