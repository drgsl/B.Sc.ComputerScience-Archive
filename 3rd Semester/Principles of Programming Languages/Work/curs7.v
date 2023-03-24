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




Inductive aeval : AExp -> Env -> AExp -> Env -> Prop :=
| lookup : forall x sigma,
    aeval (avar x) sigma (sigma x) sigma 
| add_1 : forall a1 a2 a1' sigma,
    aeval a1 sigma a1' sigma -> 
    aeval (a1 +' a2) sigma (a1' +' a2) sigma 
| add_2 : forall a1 a2 a2' sigma,
    aeval a2 sigma a2' sigma -> 
    aeval (a1 +' a2) sigma (a1 +' a2') sigma
| add : forall i1 i2 n sigma, 
    n = anum (i1 + i2) ->
    aeval (i1 +' i2) sigma n sigma 
| mul_1 : forall a1 a2 a1' sigma,
    aeval a1 sigma a1' sigma -> 
    aeval (a1 *' a2) sigma (a1' *' a2) sigma 
| mul_2 : forall a1 a2 a2' sigma,
    aeval a2 sigma a2' sigma -> 
    aeval (a1 *' a2) sigma (a1 *' a2') sigma
| mul : forall i1 i2 n sigma, 
    n = anum (i1 * i2) ->
    aeval (i1 *' i2) sigma n sigma 
.


Compute (sigma' "n").
Example ex1 : aeval (2 +' "n") sigma' (2 +' 10) sigma'.
Proof.
  eapply add_2.
  eapply lookup.
Qed.
  
Inductive aeval_clos : AExp -> Env -> AExp -> Env -> Prop :=
| a_refl : forall a sigma, aeval_clos a sigma a sigma (* <a, sigma> -> <a, sigma> *)
| a_tran : forall a1 a2 a3 sigma,
    aeval a1 sigma a2 sigma ->
    aeval_clos a2 sigma a3 sigma ->
    aeval_clos a1 sigma a3 sigma.


Example ex1' : aeval_clos (2 +' "n") sigma' 12 sigma'.
Proof.
  eapply a_tran.
  - eapply add_2.
    eapply lookup.
  - eapply a_tran.
    + eapply add. reflexivity.
    + unfold sigma'. simpl. 
      apply a_refl.
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

Inductive beval : BExp -> Env -> BExp -> Env -> Prop :=
| not : forall b b' sigma,
    beval b sigma b' sigma ->
    beval (! b) sigma (! b') sigma
| not_true: forall sigma,
    beval (! btrue) sigma bfalse sigma
| not_false: forall sigma,
    beval (! bfalse) sigma btrue sigma
| and_1 : forall b1 b1' b2 sigma,
    beval b1 sigma b1' sigma ->
    beval (b1 &' b2) sigma (b1' &' b2) sigma
| and_true : forall b2 sigma,
    beval (btrue &' b2) sigma b2 sigma
| and_false : forall b2 sigma,
    beval (bfalse &' b2) sigma bfalse sigma
| lt_1 : forall a1 a1' a2 sigma,
    aeval a1 sigma a1' sigma ->
    beval (a1 <' a2) sigma (a1' <' a2) sigma
| lt_2 : forall (i1 : nat) a2 a2' sigma,
    aeval a2 sigma a2' sigma ->
    beval (i1 <' a2) sigma (i1 <' a2') sigma
| lt : forall i1 i2 b sigma,
    b = (if Nat.ltb i1 i2 then btrue else bfalse) ->
    beval (i1 <' i2) sigma b sigma
| gt_1 : forall a1 a1' a2 sigma,
    aeval a1 sigma a1' sigma ->
    beval (a1 >' a2) sigma (a1' >' a2) sigma
| gt_2 : forall (i1 : nat) a2 a2' sigma,
    aeval a2 sigma a2' sigma ->
    beval (i1 >' a2) sigma (i1 >' a2') sigma
| gt : forall i1 i2 b sigma,
    b = (if negb (Nat.leb i1 i2) then btrue else bfalse)->
    beval (i1 >' i2) sigma b sigma.

Inductive beval_clos : BExp -> Env -> BExp -> Env -> Prop :=
| b_refl : forall a sigma, beval_clos a sigma a sigma (* <a, sigma> -> <a, sigma> *)
| b_tran : forall a1 a2 a3 sigma,
    beval a1 sigma a2 sigma ->
    beval_clos a2 sigma a3 sigma ->
    beval_clos a1 sigma a3 sigma.
         
Example ex2 :
  forall sigma, 
  beval_clos (2 +' 4 <' 10) sigma btrue sigma.
Proof.
  intros.
  eapply b_tran.
  + eapply lt_1.
    eapply add. simpl. reflexivity.
  + eapply b_tran.
    * apply lt.
      simpl. reflexivity.
    * apply b_refl.
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

Check update.
Inductive eval : Stmt -> Env -> Stmt -> Env -> Prop :=
| e_assign2: forall x a a' sigma, 
    aeval a sigma a' sigma -> 
    eval (x ::= a) sigma (x ::= a') sigma
| e_assign: forall x i sigma sigma', 
    sigma' = update sigma x i -> 
    eval (x ::= i) sigma skip sigma'
| e_skip: forall s2 sigma,
    eval (skip ;; s2) sigma s2 sigma
| e_seq: forall s1 s1' s2 sigma sigma',
    eval s1 sigma s1' sigma' ->
    eval (s1 ;; s2) sigma (s1' ;; s2) sigma'
| e_ite: forall b b' s1 s2 sigma,
    beval b sigma b' sigma -> 
    eval (ite b s1 s2) sigma (ite b' s1 s2) sigma
| e_itetrue: forall s1 s2 sigma,
    eval (ite btrue s1 s2) sigma s1 sigma
| e_itefalse: forall s1 s2 sigma,
    eval (ite bfalse s1 s2) sigma s2 sigma
| e_while: forall b s sigma,
    eval (while b s) sigma (ite b (s ;; while b s) skip) sigma.

Inductive eval_clos : Stmt -> Env -> Stmt -> Env -> Prop :=
| refl : forall stmt sigma, eval_clos stmt sigma stmt sigma
| tran : forall s1 s2 s3 sigma1 sigma2 sigma3,
    eval s1 sigma1 s2 sigma2 ->
    eval_clos s2 sigma2 s3 sigma3 ->
    eval_clos s1 sigma1 s3 sigma3.

Print sigma'.
Example ex3:
  eval_clos ("x" ::= "n") sigma' skip (update sigma' "x" 10).
Proof.
  eapply tran.
  - eapply e_assign2.
    apply lookup.
  - eapply tran.
    + eapply e_assign. reflexivity.
    + eapply refl.
Qed.

(* 
  <a, sigma> -> <a', sigma>
------------------------------------
<a + a2, sigma> -> <a' + a2, sigma>                        
*)
