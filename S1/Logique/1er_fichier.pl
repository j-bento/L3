%opérateurs

and(A,B) :- A,B.
or(A,B) :- A;B.
nand(A,B) :- not(and(A,B)).
nor(A,B) :- not(or(A,B)).
xor(A,B) :- or(A,B), nand(A,B).
s(a,b).
s(b,c).
s(c,d).
s(d,e).

mi(X,Y,Z) :-s(X,Y),s(Y,Z).
inf(X,Y) :-s(X,Y).
inf(X,Z) :-s(X,Y),inf(Y,Z).
/*
tests à exécuter:
s(c,d).
s(d,c).
s(X,c).
mi(a,b,c).

mi(a,b,d).
mi(b,X,d).
inf(a,d).
inf(Y,c).
*/


%exoA
homme(albert).
homme(jean).
homme(paul).
homme(bertrand).
homme(louis).
homme(benoit).
homme(edgar).

femme(germaine).
femme(christiane).
femme(simone).
femme(marie).
femme(sophie).
femme(madeleine).

parent(albert,jean).
parent(jean,paul).
parent(paul,bertrand).
parent(paul,sophie).
parent(jean,simone).
parent(louis,benoit).
parent(paul,edgar).

parent(germaine,jean).
parent(christiane,simone).
parent(christiane,paul).
parent(simone,benoit).
parent(marie,bertrand).
parent(marie,sophie).
parent(madeleine,edgar).

%i. :
/*
tests:
homme(paul).
femme(benoit).
femme(X).
homme(X).
parent(marie,sophie).
parent(X,jean),femme(X).
parent(paul,X).
{X}/(parent(X,Y),homme(X)).
*/
%ii:
pere(X,Y) :- parent(X,Y),homme(X).
mere(X,Y) :- parent(X,Y),femme(X).
fils(X,Y) :- parent(Y,X),homme(X).
fille(X,Y) :- parent(Y,X),femme(X).
grand_pere(X,Y) :- parent(X,Z),parent(Z,Y),homme(X).
grand_mere(X,Y) :- parent(X,Z),parent(Z,Y),femme(X).
grand_parent(X,Y) :- parent(X,Z),parent(Z,Y).
frere(X,Y) :- mere(P1,X),pere(P2,X),mere(P1,Y),pere(P2,Y),homme(X).
soeur(X,Y) :- mere(P1,X),pere(P2,X),mere(P1,Y),pere(P2,Y),femme(X).
demifrere(X,Y) :- parent(P1,X),parent(P2,X),parent(P1,Y),not(parent(P2,Y)),homme(X).
demisoeur(X,Y) :- parent(P1,X),parent(P2,X),parent(P1,Y),not(parent(P2,Y)),femme(X).
cousin(X,Y) :- grand_parent(Z,X),grand_parent(Z,Y),X\=Y.

%iii:
ancetre(X,Y) :- parent(X,Y);parent(X,Z),ancetre(Z,Y).
descendant(X,Y) :- ancetre(Y,X).
memefamille(X,Y) :- descendant(X,Z),descendant(Y,Z).

%exoB:

q(X,Z) :- p(X,Y),p(Y,Z).
/*
p([1|Z],Z).
q(U ,[]).
q(U,[1,2 ,3]).
*/
lg([],0).
lg([_|L1],N1) :- lg(L1,N), N1 is N+1.

%exoC:
liste1([a,2,b,3,4]).
%i:

appartient(X,[X|_]).
appartient(X,[_|L1]) :- appartient(X,L1).
% appartient(X,[Y|L]) :- X\==Y,appartient(X,L).
%ii:

non_appartient(X,L) :- not(appartient(X,L)).

%iii:
sans_repetition([]).
sans_repetition([X|L]) :- non_appartient(X,L),sans_repetition(L).

%iv:
/*
L1=[2,3]
X=1
L2=[1,2,3]
*/

%ajout_tete(X,L1,L2) :- [X|L1] == L2.
ajout_tete(X,L1,[X|L1]).

ajout_fin(X,[],[X]).
ajout_fin(X,[Y|L1],L2):-ajout_tete(Y,L3,L2), ajout_fin(X,L1,L3).