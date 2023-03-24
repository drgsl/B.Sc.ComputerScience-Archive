(* Comentariu *)
(*1. Definiti un tip de date algebric pt zilele sapt*)
Inductive Day:=
| Monday
| Tuesday
| Wednesday
| Thurdsday
| Friday
| Saturday
| Sunday.

Check Monday.
Check Day.

Print Day.

Check bool.
Print bool.
(*Definiti o functie de egalitate peste acest tip de date. *)

Definition eg_day (d1 d2 : Date) : bool :=
match d1, d2 with 
|Monday, Monday => true
|Tuesday, Tuesday => true
|Wednesday, Wednesday => true
|Thursday, Thursday => true
|d1', d2' => false
end.



