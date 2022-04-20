DROP TABLE IF EXISTS test;

CREATE TABLE test(
    a int,
    b int
);

INSERT INTO test(a, b) VALUES (1, 1);
INSERT INTO test(a, b) VALUES (2, 2);

--Q1. Un verrou à été déposer par t2 lorsque t1 a essayé d'écrire dans la base de donnée
-- t1 a été rollback car il a essayé d'écrire pendant que t2 écris dans la même colonne

--2. l'erreur de deadlock s'effectue egalement en isolation
-- repeatable read

--3. Pas d'erreur, la transaction s'effectue correctement
--T1 et T2 effectue la mise à jour et les deux transactions sont commit à la fin

--En repeatable read, T2 rollback car c'est une erreur de type
--unrepeatable read

--4. Je suis très surpris du résultat, je pensais que
-- la colonne 2 aurait tout de même été supprimé mais pas la une
--On observe qu'aucune n'a été supprimer par T2.

--Postgres delete les transaction seulement si 
--la requête marche avant ET après l'état de la transaction d'après.


-- T1 : Joueur Bobar 
-- T2 : Admin
-- T1 : begin transaction isolation level read committed;          
-- T2 : begin transaction isolation level read committed; 

-- T2 : changer l'état de a partie dominion si il y a 2 membres
-- select count(pid) from demande where pid=8; -> 2 membres
-- update partie set etat  = 'ferme' where pid=8;


-- T1 veut se desister d'une partie encore ouvert 
-- select etat from partie where pid=8;
-- delete from demande where pid=8 and jid = 2;

-- T2 : confirmer les demande du jeu pid=2
-- update demande set statut='valide' where pid=8;

--commit
--commit

-- En repeatable read et en serializable le système renvoi des erreurs

--2)--
    --T1 ADMIN :--
    --BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;--
    --UPDATE partie SET etat = 'annulé' WHERE pid = 3;--
    --UPDATE demande SET statut = 'refusé' WHERE pid = 3;--
    --COMMIT;--
    --SELECT * FROM partie;--

    --T2 JOUEUR :--
    --INSERT INTO demande VALUES (1,3,now(),'en attente');--
    --INSERT INTO demande VALUES (2,3,now(),'en attente');--


    
    --BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;--
    --INSERT INTO demande VALUES (4,3,now(),'en attente');--
    --COMMIT--
    --SELECT * FROM demande;--

--5)
--T1 Admin || T2: joueur (jid 3)
--T1 observe la bdd et voit que la partie 8 atteint le nbmax de demande
--T2 fais une demande pour la partie 8
--T1 cloture la partie (etat fermé pour la partie 8)
--T2 commit
--T1 met à jour les demandes à validé
--T1 commit
--

--3)
-- T1 valide
--T1 ferme
--T2 refuse en attente
--T2 commit
--T1 confirme la partie 

--Exercice 3

--On observe une table généré automatiquement avec des 
--lignes déjà remplis


--relfilenode : 147459

--3 select locktype, tuple, virtualtransaction from pg_locks where relation = 147459;
--Il n'y a aucun verrou sur la table test

--4. A chaque lecture/ecriture sur la base un verrou apparait pour chaque transaction
--   Lorsqu'il y a un conflit, un tuple apparait dans un verrou
--  Ensuite lorsqu'une transaction commit les verrou de cette transaction sont supprimé de la table.