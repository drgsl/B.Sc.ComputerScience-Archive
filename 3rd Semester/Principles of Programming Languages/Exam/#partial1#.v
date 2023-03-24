Inductive Nat := O : Nat
               | S : Nat -> Nat.

Check S(S O).

Fixpoint plus (n m : Nat) :=
match n with
  | O => m
  | S n' => S (plus n' m)
end.

Eval compute in (plus O O).
Eval compute in (plus (S(S O)) (S O)).

Lemma plus_O_m_is_m:
  forall m, plus O m = m.
Proof.
intros m.
simpl.
reflexivity.
Qed.

Theorem plus_eq:
forall m n, m = n -> plus O m = plus O n.
Proof.
intros.
rewrite H.
reflexivity.
Qed.

Theorem plus_c_a:
forall k, plus k (S O) <> O.
Proof.
intros.
destruct k as [| k'] eqn:E.
Show 2.
simpl. unfold not. intro H. inversion H.
simpl. unfold not. intro H. inversion H.
Qed.

Check Nat_ind.

Lemma plus_n_O_is_n:
forall n, plus n O = n.
Proof.
induction n.
simpl.
reflexivity.
simpl.
rewrite IHn.
reflexivity.
Qed.

(*auto/trivial*)
