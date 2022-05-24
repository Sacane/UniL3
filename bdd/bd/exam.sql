--Q1.
--1. contrainte 'varchar(5000)' sur auteurQ

--2/ contrainte 'DEFAULT NOW()'

--3
CREATE TRIGGER delDate 
BEFORE INSERT ON evaluation 
FOR EACH ROW 
WHEN (note < 1)
EXECUTE PROCEDURE fun();

--La fonction va compter le nombre de note inférieur à 1
--d'une réponse, si le resultat vaut plus que 9 
--On renvoi NULL
--Sinon on renvoi NEW

--4
CREATE TRIGGER onCheckResolue
BEFORE UPDATE OF resolue ON question
FOR EACH ROW 
WHEN (old.resolue=true && new.resolue=false)
EXECUTE PROCEDURE cancel();

--La fonction renvoi null (car si on rentre dans
--la fonction, l'ancienne valeur était true et on veut
--la faire passer à false)

CREATE TRIGGER checkIfAuthorPresent
BEFORE INSERT ON question
FOR EACH ROW
EXECUTE PROCEDURE cancelQuestion();


--Recupère la liste des auteurs qui ont posé une question
--pour chaque auteur si la question qu'il a posé est ouvert et
--que old.auteur == new.auteur on renvoi null.

--6.
--Contrainte UNIQ (Ou ne rien faire car
--Déjà une contrainte de clef primaire)


--7.
CREATE TRIGGER onUpdateQuestion
BEFORE UPDATE ON question
FOR EACH ROW
EXECUTE PROCEDURE writeEdit();

--On copie le message dans une variable
--On copie la date du jour dans unevariable
--On ajoute la date du jour a la fin du message
--On met ce message à la place du new.message

--8.
CREATE TRIGGER onAddQuestion
AFTER INSERT ON question
FOR EACH ROW 
EXECUTE PROCEDURE noticeAdd();

--Raise notice

--9.
CREATE TRIGGER onCheckOpen()
BEFORE INSERT ON reponse
FOR EACH ROW
EXECUTE PROCEDURE foo();



--On recupère * par une requête when idQ = new.idQ
--Si old.resolue = true renvoi null
--sinon on renvoi new

--10.
CREATE TRIGGER onCheckUpdateReponse()
BEFORE UPDATE ON reponse 
FOR EACH ROW 
EXECUTE PROCEDURE cancelUpdateResponse();


--Renvoi null car il ne peut modifier que note et il n'a pas le droit


CREATE OR REPLACE FUNCTION updateQuestion()
RETURNS TRIGGER AS
$$
    DECLARE nb_user int; avg_note float; idQuestion int; author varchar; 
    BEGIN
        SELECT COUNT(pseudo) as users FROM evaluation into nb_user GROUP BY idR;
        SELECT AVERAGE(note) as avgnote FROM evaluation into avg_note GROUP BY note;
        SELECT idQ FROM question into idQuestion WHERE question.idR == NEW.idR;
        SELECT auteurR FROM reponse into author WHERE reponse.auteurR == NEW.pseudo;
        IF nb_user >= 10 AND avg_note > 4 THEN 
            UPDATE TABLE(question) WHERE idQ == idQuestion SET resolue = true;
            RAISE NOTICE 'La question % a été résolue par %' idQ, author;
        END IF

    END; 
$$
LANGUAGE plpgsql;


CREATE TRIGGER onUpdateReponse
AFTER INSERT ON evaluation
FOR EACH ROW
EXECUTE PROCEDURE updateQuestion();


--EXO3

-- Q1: Après évaluation en série des deux transactions
-- Toutes les colonnes de la table questions sont résolue

--Q2 : 
T1 : Admin T2 : Hpotter

T1 : BEGIN
T2 : BEGIN

T1 : DELETE FROM question
WHERE NOT EXISTS (
SELECT * FROM reponse NATURAL JOIN evaluation
WHERE reponse.idQ = question.idQ AND note = 5
);

T2 : DELETE FROM evaluation
WHERE pseudo = ’HP.otter’;
T1 : 
UPDATE question SET resolue = True
WHERE EXISTS (
SELECT * FROM reponse NATURAL JOIN evaluation
WHERE reponse.idQ = question.idQ AND note = 5
);

T1 commit
T2 commit

--Erreur de sérialisation, parce que on execute une requête dont la ligne n'existe pas.

--Q3 : 
-- Il faut se placer dans le niveau d'isolation "SERIALIZABLE"

--Exercice 4 : 
-- 1. Environ 100 octets pour un enregistrement
-- 2. quelques milliers on suppose environ 10 000 utilisateurs
--  espace total occupé par la table : 10 000 * 100 = 1 000 000 octets.
-- On sait que 1 bloc c'est : 4096 octets -> environ 5000
-- Nombre de bloc necéssaire : 1 000 000 / 5000 = environ 200 octets
--4. index primaire non-dense -> une entrée par bloc donc 200 index
--  adresse -> 4/8 octets | 25 octets pour le pseudo
--  environ 30 octets par index, on a 200 octets (nombre de bloc) donc 200 * 30 = 6000 octets pour le nombre d'entrées

--Exercice 5 : 
--1.Un accès au disque dans des opérations sur une BDD
--représente un temps équivalent à qques ms ce qui est
--largement supérieur à tout autre opération arithmétique,
--on cherche donc lors d'opérations à limiter le nombre
--d'accès au disque.

--2.
--Index primaire : les blocs sont triés par la clef de recherche de l'index
--Index secondaire : les blocs ne sont pas triés (forcément dense) ou pas triés
--par la clef de recherche de l'index

--4.
--Si on utilise tout le temps le niveau d'isolation maximum, on ralenti
--énormément les requêtes car à chaque echec on doit tout relancer même
--si la requête est en soit bonne. Des transactions longues peuvent échouer
--et sont très couteuses et longues à relancer.