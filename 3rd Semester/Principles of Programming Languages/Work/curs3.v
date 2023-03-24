Inductive Nat := O | S : Nat -> Nat.

Fixpoint le_Nat (m n : Nat) : bool :=
  match m with
  | O => true
  | S m' => match n with
            | O => false
            | S n' => le_Nat m' n'
            end
  end.

Compute le_Nat O O.
Compute le_Nat (S O) O.
Compute le_Nat O (S O).
Compute le_Nat (S (S O)) (S (S (S O))).

Lemma trans :
  forall m n p,
    le_Nat m n = true ->
    le_Nat n p = true ->
    le_Nat m p = true.
Proof.
  induction m.
  - simpl. reflexivity.
  - intros n p H H'.
    simpl in H.
    destruct n.
    + inversion H.
    + simpl in H'.
      destruct p.
      * inversion H'.
      * simpl. 
        apply IHm with (n := n); assumption.
Qed.


(* Vom lucra cu tipul nat din Coq in loc de tipul Nat definit mai sus. *)

(* Polymorphism *)
Inductive ListNat :=
| Nil'' : ListNat
| Cons'' : nat -> ListNat.

Inductive ListBool :=
| Nil' : ListBool
| Cons' : bool -> ListBool.

(* Code duplication! *)
Inductive List (T : Type) :=
| Nil : List T
| Cons : T -> List T -> List T.
             
Check List.
Definition Listnat := List nat.
Check Nil nat.
Check (Cons nat 2 (Nil nat)).
Check (Cons nat 8 (Cons nat 2 (Nil nat))).

Definition Listbool := List bool.
Check (Cons bool false (Nil bool)).

Check Nil.
Check Cons.

Fixpoint length (T : Type) (l : List T) : nat :=
  match l with
  | Nil _ => 0
  | Cons _ e l' => 1 + (length T l')
  end.

Compute length nat (Nil nat).
Compute length nat (Cons nat 2 (Nil nat)).
Compute length nat (Cons nat 8 (Cons nat 2 (Nil nat))).

(* Implicit Arguments *)
Arguments Nil {T}.
Arguments Cons {T}.
Arguments length {T}.

Compute length Nil.
Compute length (Cons 2 Nil).
Compute length (Cons 8 (Cons 2 Nil)).

Fixpoint length' {T : Type} (l : List T) :=
  match l with
  | Nil => 0
  | Cons e l' => 1 + (length' l')
  end.

(* Higher-order functions *)

Fixpoint filter {T : Type}
         (l : List T)
         (f : T -> bool) : List T :=
  match l with
  | Nil => Nil
  | Cons e l' => if (f e)
                 then Cons e (filter l' f)
                 else filter l' f
  end.

Definition num_list := (Cons 2 (Cons 13 (Cons 7 (Cons 8 Nil)))).
Definition is_digit (n : nat) : bool := Nat.leb n 9.

Check num_list.
Check is_digit.

Compute is_digit 0.
Compute is_digit 9.
Compute is_digit 10.

Compute filter num_list is_digit.

Compute length (filter num_list is_digit).
(* Error: Compute filter (Cons true Nil) is_digit.*)

(* Lambda-functions or anonymous functions *)
Check (fun n => Nat.leb n 9).

Compute filter num_list (fun n => Nat.leb n 9).

Inductive Either (T T' : Type) :=
| fst : T -> Either T T'
| snd : T' -> Either T T'.

Print nat.

(*
Check (fun {T T' : Type} (n : nat) (b : bool) =>
         match n with
         | 0 => fst n
         | S n' => snd b
         end) .
 *)

Definition compose {A B C : Type}
           (f : B -> C)
           (g : A -> B) :=
  fun x => f (g x).

Check compose.

Check compose (fun x => x * 2) (fun x => x + 3).

Compute (compose (fun x => x * 2) (fun x => x + 3)) 2.
Compute (compose (fun x => x + 3) (fun x => x * 2)) 2.
           
(* Prop *)
Check 10 = 10.
Check 10 = 11.
Check Prop.

Goal 10 = 10.
Proof.
  reflexivity.
Qed.

Goal 10 = 11.
Proof.
  (* can't prove this *)
Abort.

(* Implications *)
Lemma simple_impl :
  forall n, n = 0 -> n + 3 = 3.
Proof.
  intros n H.
  rewrite H.
  simpl.
  reflexivity.
Qed.


Lemma not_so_simple:
  forall m n, m = 0 -> n = 0 -> n + m = 0.
Proof.
  intros m n H1 H2.
  rewrite H1.
  rewrite H2.
  simpl.
  trivial.
Qed.

Lemma demo :
  forall (P Q R : Prop),
    (P -> (Q -> R)) <-> (P /\ Q -> R).
Proof.
  intros.
  split.
  - intros H [H1 H2].
    apply H; assumption.
  - intros.
    apply H.
    split; assumption.
Qed.

Lemma disj_1 :
  forall n,
    n = 0 \/ 5 + 5 = 11 -> n + 3 = 3.
Proof.
  intros n [H1 | H2].
  + rewrite H1. simpl. trivial.
  + simpl in H2. inversion H2.
Qed.

Lemma disj_2 :
  forall n,
    n = 0 \/ 5 + 5 = 10 -> n + 3 = 3.
Proof.
  intros n [H1 | H2].
  + subst n. trivial.
  + (* can't prove this *)
Abort.

Lemma fals :
  forall P, False -> P.
Proof.
  intros P H.
  exfalso.
  assumption.
Qed.

Lemma exists1:
  exists (n : nat), n = 0.
Proof.
  exists 0.
  trivial.
Qed.


Lemma exists3:
  forall m,
    (exists n, m = 2 + n) ->
    (exists n, m = 1 + n).
Proof.
  intros m [x H'].
  exists (1 + x).
  simpl in *.
  assumption.
Qed.
