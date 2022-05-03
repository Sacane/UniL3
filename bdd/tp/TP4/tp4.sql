DROP TABLE IF EXISTS test;


CREATE TABLE test(
    id serial primary key,
    a int,
    b int
);


--Ctid référence à l'emplacement physique 
--de la version de la ligne dans la table sous
-- forme de tuple d'entier
--Elle fait référence au bloc dans lequel elle est 
--stocké dans la table
--Elle est utilisé comme index 

--xmin est l'id de la transaction 
--d'insertion de la ligne correspondante

--xmax est l'identité de la transaction de suppression
--de la ligne correspondante

--INSERT INTO test(a, b) VALUES (1, 2);

--3.  lors de l'insertion dans une transaction
-- Xmin se remplit selon le numéro de transaction
-- ayant ajouté la ligne
-- On peut aussi noter que lorsque l'on insert des
--valeurs, le ctid se met a jour meme lorsqu'il n'y a pas de commit

--4. Lors de suppressions de ligne non commité, 
-- on observe dans les autres transactions que la colonne xmax est remplie
-- à l'endroit où elle est supprimé par d'autres.
-- 

--5 . On peut observer ici que lors d'un update la deuxieme valeur
--du tuple ctid de la ligne concerné est incrémentée de 1 seulement
--Dans T1.
--Dans T2, si il y une insertion après l'update de T1, on peut
--observer que la valeur de ctid[1] est la nouvelle valeur de l'update de t1 + 1
--Ainsi, lorsque l'on observe l'état de ctid avant de tout commit dans T2
--On obtient un ctid (0, 7) au lieu de (0, 6).

--Exercice 2

--1. Pour le moment il n'y a qu'un seul bloc qui est utilisé pour stocker les  valeurs

--3. Il y a 185 enregistrement dans chaque bloc

--  185 * 32 * 3 = 18000 bits environ donc 2200 octets

--4. 

--Exo 3:

--SELECT relpages, reltuples FROM pg_class WHERE relname='test';

--Il y a bien 55 blocs (le bloc de l'id 10000 est (54))

--Il ya bien 10000 enregistrements

--DELETE FROM test WHERE a < 5;

--Lors de la suppression, pg_class n'est pas tout de suite
--mis à jour, on observe toujours le même nombre de tuples
--Après la commande ANALYZE sur test le nombre de tuple est bien mis à jour
--Mais pas le nombre de bloc, donc on peut supposer que les blocs se mettront 
--à jour plus tard.

--3. INSERT INTO test(a, b) SELECT round(99, random()*100) FROM generate_series(10000, 14000);
--Les nouveaux enregistrements ont été insérés dans de nouveaux blocs

--INSERT INTO test(a,b) SELECT round(99), round(random()*100) FROM generate_series (10000,14000);
--UPDATE test set b = b + 1 WHERE a = 99;

--Les blocs vont être marqué comme "à supprimer" mais ne le sont pas
--Donc lors de l'update il supprime et insère la valeur, ce qui conduit à une augmentation du nombre
--de bloc

--5. Toutes les lignes ont été supprimés

--6. Les lignes supprimés sont marqué comme supprimés mais sont toujours
--présent dans les blocs

--7. Ici on observe que les blocs supprimés ont bien été supprimés
--contrairement aux 5000 premiers 