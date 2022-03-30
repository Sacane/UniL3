-- Universite.sql représente les données d'un ensemble de cours suivi par des étudiants, ainsi que leurs examen
-- correspondant. Elle gère la montée en grade des étudiants via une vue, selon la situation de l'étudiant
-- Un trigger s'active, lui permettant ou non selon les critères de l'insertion de le faire monté ou non.


--Tests : 

--Recherche de la liste des etudiant avec le nom "Potter" avec leur notes si ils ont eut 10 à leur épreuve
--SELECT * FROM etudiant NATURAL JOIN examen NATURAL JOIN cours WHERE nom='Potter' and examen.note >= 10;

--Insertion de l'étudiante 'Hermionne Granger' dans la table nouveauL3 :
--INSERT INTO nouveauL3 VALUES (2, 'Granger');
--Resultats : 1) Miss Granger à été ajouter dans nouveauL3. Des points de jury ont également été ajouter dans examen pour lui
--permettre de compenser sa licence via cette seule matière.

DROP TRIGGER IF EXISTS insereL3 ON nouveauL3;

CREATE OR REPLACE FUNCTION pointsJury() RETURNS TRIGGER AS
$$
	DECLARE 
		etu etudiant%ROWTYPE; deja int; jury record; pts int; nomEtu text; currentNumEtud int;

	BEGIN
	SELECT * INTO etu FROM etudiant WHERE numEtud = NEW.numEtud;
	IF NOT FOUND THEN 
		RAISE NOTICE 'L''étudiant n''existe pas.' ; RETURN NULL ;
	END IF;
	IF etu.numLic != 2 THEN 
		RAISE NOTICE 'L''étudiant n''est pas en L2.' ; RETURN NULL ; 
	END IF ;

	SELECT numEtud INTO deja FROM nouveauL3 WHERE numEtud = NEW.numEtud;
	IF FOUND THEN
		RAISE NOTICE '% passe déjà en L3.', etu.nom; RETURN NULL ;
	END IF;

	--Verification du nom de l'étudiant avec son numéro inscrit dans la db
	SELECT numEtud INTO currentNumEtud FROM etudiant WHERE nom = NEW.nom;
	IF NOT FOUND THEN 
		RAISE NOTICE 'Le nom de l''étudiant et son numéro ne correspondent pas.' ; RETURN NULL ;
		RETURN NULL;
	END IF;
	IF currentNumEtud <> etu.numEtud THEN
		RAISE NOTICE 'Le nom de l''étudiant et son numéro ne correspondent pas.';
		RETURN NULL;
	END IF;


    --Somme des ects dans lequel l'étudiant à obtenu au moins la moyenne
    SELECT sum(ects) into pts FROM examen NATURAL JOIN cours WHERE numEtud=NEW.numEtud and note >= 10;
    IF pts IS NULL THEN 
        pts = 0;
    END IF;
	SELECT * INTO jury FROM cours WHERE intitule = 'Points de jury';
	IF NOT FOUND THEN 
		RAISE NOTICE 'Le cours Points de Jury n''existe pas encore, nous le créons..';
		INSERT INTO cours(intitule, ects) VALUES ('Points de jury', 10);
	END IF;
    --On ajoute les ects du points de jury avec ceux des autres cours validés
    pts = pts + jury.ects;

	--Demarche : Si la somme des ects est supérieur à 65, l'étudiant passe en L3, sinon une notice apparait indiquant qu'il lui manque des matières
    IF pts < 65 THEN
        RAISE NOTICE 'L''étudiant % n''a cumulé que % ects sur 65, les points de jury sont insuffisant. Vous ne passerez pas !', NEW.nom, pts;
		RETURN NULL;
	ELSE 
		RAISE NOTICE 'Felicitation ! Vous avez cumulé assez d''ECTS pour passer en L3 !';
		INSERT INTO examen VALUES (etu.numEtud, jury.codeCours, 10);
	END IF;

	RETURN NEW ;
	END ;
$$
LANGUAGE plpgsql;

CREATE TRIGGER insereL3
INSTEAD OF INSERT ON nouveauL3
FOR EACH ROW 
EXECUTE PROCEDURE pointsJury();

-- \i universite.sql : Pour tester le trigger, réinitialisez la base de donnée "universite.sql" au cas où.
-- \i points_jury.sql initialisez le trigger

--INSERT INTO nouveauL3 VALUES (4, 'Weasley'); -> Pas assez d'ECTS cumulé

--INSERT INTO nouveauL3 VALUES (4, 'Londubat'); -> Le numéro et le nom ne correspondent pas

--INSERT INTO nouveauL3 VALUES (5, 'Delacour'); -> L'insertion s'execute correctement

