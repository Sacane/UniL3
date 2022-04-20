DROP TABLE IF EXISTS test;
DROP TABLE IF EXISTS test2;
CREATE TABLE test(
	id serial primary key,
	a int,
    b int
);

--INSERT INTO test(a, b) VALUES (1, 2)
--RETURNING id;

--INSERT INTO test(id, a, b) VALUES (1, 3, 4)
--RETURNING id;

--Ici Une erreur survient : l'id est la même, une erreur intervient


--Après ajout des valeurs, si l'on fait un rollback les transactions effectués après le BEGIN sont annulés.


--4. Après simulation de la panne, les transactions effectuées après Begin n'ont pas été sauvegardés dans la base de donnée.

--5. En terminant avec COMMIT les transactions sont bien effectués dans la base de donnée.

-- L'erreur suivante disant que on ne peut faire de command car la transaction est annulé : 
--current transaction is aborted, commands ignored until end of transaction block


-- 8. EN rejouant le scénario précédent et en finissant la transaction par commit
-- le système refuse le commit et effectue un rollback à la place

-- La transaction est annulé même lors de banales fautes de frappe
--testé avec la suite d'instruction : 

-- BEGIN ;
-- INSERT INTO test(a, b) VALUES (2, 5);
-- INSERT INTO tes VALUES (blabla);

--got : 
--ERROR:  relation "tes" does not exist
--LINE 1: INSERT INTO tes VALUES (blabla);


--EXERCICE 2 

-- 1. Le niveau d'isolation de postgres par défaut est : 
--    Read committed, le dirty read n'existe pas sous postgres

--2. Read commited : 

-- Le reaad commited n'effectue pas le dirty read : 
-- Lorsque l'on met à jour une valeur dans la table depuis T1,
-- T2 ne peut pas lire cette nouvelle valeur tant que T1 n'a pas commit


-- En isolation REPEATABLE READ, il n'y a pas de dirty read
-- Cependant si T1 commit mais que T2 n'a pas finis sa transaction
-- Alors les changements apportés par T2 ne seront pas validés même
-- Si il commit et qu'aucune erreur n'est indiqué
--REPEATABLE READ gère également le phantom Read
--Repeatable read ne gère pas les probleme de sérialisation anomaly

-- Sérialisable : T1 valide le projet seulement si T1 et T2 
-- executent des transactions en série


--4. Serializable s'execute comme en repeatable read ici

--Exercice 3 : 

--

CREATE OR REPLACE FUNCTION foo() 
RETURNS TRIGGER AS
$$
BEGIN
    IF NEW.a % 2 = 0 THEN
        RAISE NOTICE 'a est pair';
    END IF;
    IF NEW.b % 2 = 0 THEN
        RETURN NULL;
    END IF;
    IF NEW.a = NEW.b THEN
        RAISE EXCEPTION 'a = b not valid';
    END IF;
RETURN NEW;
END;
$$
language plpgsql;

CREATE TRIGGER bar 
BEFORE INSERT ON test
FOR EACH ROW
EXECUTE PROCEDURE foo();


--Lorsque l'on active un trigger retournant null
--Il 'n y a pas d'erreur dans postgres
--Mais la valeur n'est pas insérer, un rollback ou un commit 
-- s'executent comme attendu

--Si par contre on déclenche un trigger retournant une
--exception, postgres renvoi une erreur. 

--On peut donc conclure que renvoyer null ne fait
--pas planter le système lors de transaction
--Seul l'exception le fait, après exception on ne peut 
-- Ni rollback ni commit

-- Exercice 4 

--1. La création de table s'annule après rollback dans une transaction
-- Après commit la table est bien crée

--Une création de table fonctionne correctement
--Durant une transaction.
--Postgres autorise donc  bien les rollback pour la création
--de table.

--Renommer une colonne fonctionne correctement également
--On peut conclure que toutes les opérations LDD 
--AVec postgres n'impose pas de commit implicite.