Require Import String.
Open Scope string_scope.

Inductive AExp :=
| anum : nat -> AExp
| avar : string -> AExp
| aplus : AExp -> AExp -> AExp
| amul : AExp -> AExp -> AExp.

(* Coercion *)
Coercion anum : nat >-> AExp.
Coercion avar : string >-> AExp.
(* Notation *)
Notation "A +' B" := (aplus A B) (at level 50, left associativity).
Notation "A *' B" := (amul A B) (at level 40, left associativity).

Definition Env := string -> nat.
Definition sigma0 : Env :=
  fun x => 0.

Definition sigma' : Env :=
  fun x => if string_dec x "n"
           then 10
           else 0.

Definition update (e : Env) (x : string) (v : nat) : Env :=
  fun y => if string_dec x y
           then v
           else (e y).

Definition sigma1 := update sigma0 "n" 11.

(* Fixpoint aeval (a : AExp) (sigma : Env) : nat := *)
(*   match a with *)
(*   | anum n => n *)
(*   | avar x => (sigma x) *)
(*   | aplus a1 a2 => (aeval a1 sigma) + (aeval a2 sigma) *)
(*   | amul a1 a2 => (aeval a1 sigma) * (aeval a2 sigma) *)
(*   end. *)


Reserved Notation "A =[ S ]=> N" (at level 60).

Inductive aeval : AExp -> Env -> nat -> Prop :=
| const : forall n sigma,
    anum n =[ sigma ]=> n (* <n, sigma> => <n> *)
| lookup : forall x sigma,
    avar x =[ sigma ]=> (sigma x) (* <x, sigma> => <sigma(x)> *)
| add : forall a1 a2 i1 i2 sigma n,
    a1 =[ sigma ]=> i1 ->
    a2 =[ sigma ]=> i2 ->
    n = i1 + i2 ->                                 
    a1 +' a2 =[ sigma ]=> n
| times : forall a1 a2 i1 i2 sigma n,
    a1 =[ sigma ]=> i1 ->
    a2 =[ sigma ]=> i2 ->
    n = i1 * i2 ->                                 
    a1 *' a2 =[ sigma ]=> n
where "A =[ S ]=> N" := (aeval A S N).

Compute (sigma' "n").
Example ex1 : 2 +' "n" =[ sigma' ]=> 12.
Proof.
  apply add with (i1 := 2) (i2 := 10).
  - apply const.
  - apply lookup.
  - simpl. reflexivity.
Qed.

Example ex1' : 2 +' "n" =[ sigma' ]=> 12.
Proof.
  eapply add.
  - apply const.
  - apply lookup.
  - unfold sigma'. simpl. reflexivity.
Qed.



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

(* Fixpoint beval (b : BExp) (sigma : Env) : bool := *)
(*   match b with *)
(*   | btrue => true *)
(*   | bfalse => false *)
(*   | bnot b' => negb (beval b' sigma) *)
(*   | band b1 b2 => andb (beval b1 sigma) (beval b2 sigma) *)
(*   | blt a1 a2 => Nat.ltb (aeval a1 sigma) (aeval a2 sigma) *)
(*   | bgt a1 a2 => negb (Nat.leb (aeval a1 sigma) (aeval a2 sigma)) *)
(*   end. *)

Reserved Notation "B ={ S }=> B'" (at level 91).
Check Nat.leb.
Inductive beval : BExp -> Env -> bool -> Prop :=
| bs_true : forall sigma, btrue ={ sigma }=> true 
| bs_false : forall sigma, bfalse ={ sigma }=> false
| bs_nottrue : forall b sigma,
    b ={ sigma }=> true -> 
    (bnot b) ={ sigma }=> false
| bs_notfalse : forall b sigma,
    b ={ sigma }=> false -> 
    (bnot b) ={ sigma }=> true
| bs_andtrue : forall b1 b2 sigma b,
    b1 ={ sigma }=> true ->
    b2 ={ sigma }=> b ->
    (b1 &' b2) ={ sigma }=> b
| bs_andfalse : forall b1 b2 sigma,
    b1 ={ sigma }=> false ->
    (b1 &' b2) ={ sigma }=> false
| bs_lt : forall a1 a2 i1 i2 b sigma,
    a1 =[ sigma ]=> i1 ->
    a2 =[ sigma ]=> i2 ->    
    b = Nat.ltb i1 i2 ->
    (a1 <' a2) ={ sigma }=> b
| bs_gt : forall a1 a2 i1 i2 b sigma,
    a1 =[ sigma ]=> i1 ->
    a2 =[ sigma ]=> i2 ->    
    b = negb (Nat.leb i1 i2) ->
    (a1 >' a2) ={ sigma }=> b                              
where "B ={ S }=> B'" := (beval B S B').

Example ex2 :
  2 +' "n" <' 10 ={ sigma' }=> false.
Proof.
  eapply bs_lt.
  - eapply add.
    + apply const.
    + apply lookup.
    + unfold sigma'. simpl. reflexivity.
  - apply const.
  - unfold Nat.ltb. simpl. reflexivity.
Qed.


(* statements *)
Inductive Stmt :=
| skip : Stmt
| seq : Stmt -> Stmt -> Stmt
| assign : string -> AExp -> Stmt
| ite : BExp -> Stmt -> Stmt -> Stmt
| while : BExp -> Stmt -> Stmt.


Notation "A ::= B" := (assign A B) (at level 95).
Notation "A ;; B" := (seq A B) (at level 99, right associativity).

(* Fixpoint eval (s : Stmt) (sigma : Env) (gas : nat) : Env := *)
(*   match gas with *)
(*   | O => sigma *)
(*   | S g' =>   match s with *)
(*               | skip => sigma *)
(*               | seq s1 s2 => eval s2 (eval s1 sigma g') g' *)
(*               | assign x a => update sigma x (aeval a sigma) *)
(*               | ite b s1 s2 => if (beval b sigma) *)
(*                                then eval s1 sigma g' *)
(*                                else eval s2 sigma g' *)
(*               | while b s => eval (ite b (seq s (while b s)) skip) sigma g' *)
(*               end *)
(*   end. *)


Reserved Notation "Stmt -{ Env }-> Env'" (at level 99).
Check update.
Inductive eval : Stmt -> Env -> Env -> Prop :=
| bs_assign : forall x a i sigma sigma',
    a =[ sigma ]=> i -> 
    sigma' = update sigma x i ->
    (x ::= a) -{ sigma }-> sigma' 
| bs_seq : forall s1 s2 sigma sigma1 sigma2,
    s1 -{ sigma }-> sigma1 ->
    s2 -{ sigma1 }-> sigma2 ->
    (s1 ;; s2) -{ sigma }-> sigma2 
| bs_skip : forall sigma,
    skip -{ sigma }-> sigma
| bs_whiletrue : forall b sigma s sigma',
    b ={ sigma }=> true -> 
    (s ;; while b s) -{ sigma }-> sigma' ->
    (while b s) -{ sigma }-> sigma'
| bs_whilefalse : forall b s sigma,
    b ={ sigma }=> false -> 
    (while b s) -{ sigma }-> sigma
| bs_iftrue : forall b sigma s1 s2 sigma',
    b ={ sigma }=> true ->
    s1 -{ sigma }-> sigma' -> 
    (ite b s1 s2) -{ sigma }-> sigma'
| bs_iffalse : forall b sigma s1 s2 sigma',
    b ={ sigma }=> false ->
    s2 -{ sigma }-> sigma' -> 
    (ite b s1 s2) -{ sigma }-> sigma'
where "Stmt -{ Env }-> Env'" := (eval Stmt Env Env').

Check sigma0.
Definition sigma3 := update (update sigma0 "i" 0) "i" 1.
Example ex3:
  ("i" ::= 0 ;;
  while ("i" <' 1) (
          "i" ::= "i" +' 1
        ))
  -{ sigma0 }-> sigma3.
Proof.
  eapply bs_seq.
  - eapply bs_assign.
    + apply const.
    + eauto.
  - eapply bs_whiletrue.
    + eapply bs_lt.
      * eapply lookup.
      * apply const.
      * unfold Nat.ltb. simpl. trivial.
    + eapply bs_seq.
      * admit.
Admitted.

Create HintDb mydb.
Hint Constructors aeval : mydb.
Hint Constructors beval : mydb.
Hint Constructors eval : mydb.
Hint Unfold update : mydb.
Hint Unfold Nat.ltb : mydb.

Example ex3_eauto:
  ("i" ::= 0 ;;
  while ("i" <' 1) (
          "i" ::= "i" +' 1
        ))
  -{ sigma0 }-> sigma3.
Proof.
  eauto 10 with mydb.
Qed.

Definition sigma4 := update sigma3 "i" 2.

Example ex3'_eauto:
  ("i" ::= 0 ;;
  while ("i" <' 2) (
          "i" ::= "i" +' 1
        ))
  -{ sigma0 }-> sigma4.
Proof.
  eauto 15 with mydb.
Qed.
