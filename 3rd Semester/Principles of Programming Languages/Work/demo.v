Inductive Nat :=
| O : Nat         (* zero *)
| S : Nat -> Nat. (* succ *)

Check O.
Check S.
Check (S O).
Check S (S O).
Check S (S (S (S O))).


Fixpoint plus (n m : Nat) : Nat :=
  match n with
  | O => m
  | S n' => S (plus n' m)
  end.

Compute plus (S O) (S O).
Compute plus O (S (S (S (S O)))).
Compute plus (S (S (S (S O)))) O.

Print bool.
Print nat.

Lemma plus_O_n_is_n:
  forall n, plus O n = n.
Proof.
  (* tactica *)
  intro n.
  simpl.
  reflexivity.
Qed.

Lemma plus_eq:
  forall m n, m = n -> plus O m = plus O n.
Proof.
  intros m n H.
  (* rewrite H. *)
  (* rewrite <- H. *)
  (* simpl. exact H/assumption. *)
  trivial.
Qed.

Lemma plus_c_a:
  forall k, plus k (S O) <> O.
Proof.
  intro k.
  destruct k as [a a'|k']; simpl; unfold not; intro H; inversion H.
Qed.

Check Nat_ind.

Lemma n_plus_O_is_n:
  forall n, plus n O = n.
Proof.
  intro n.
  induction n.
  - trivial.
  - simpl. rewrite IHn. reflexivity.
Qed.

Lemma plus_comm:
  forall n m, plus n m = plus m n.
Proof.
  induction n.
  - intro m.
    simpl.
    rewrite n_plus_O_is_n.
    reflexivity.
  - induction m.
    + simpl.
      rewrite n_plus_O_is_n.
      trivial.
    + simpl.
      rewrite <- IHm.
      simpl.
      rewrite IHn.
      simpl.
      rewrite IHn.
      trivial.
Qed.
