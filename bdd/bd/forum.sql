DROP TABLE IF EXISTS participe CASCADE;
DROP TABLE IF EXISTS vendre CASCADE;
DROP TABLE IF EXISTS soiree CASCADE;
DROP TABLE IF EXISTS deguisement CASCADE;
DROP TABLE IF EXISTS personne CASCADE;
DROP TABLE IF EXISTS personne CASCADE;
DROP TABLE IF EXISTS question CASCADE;
DROP TABLE IF EXISTS reponse CASCADE;
DROP TABLE IF EXISTS evaluation CASCADE;

CREATE TABLE personne (
	pseudo varchar(25) primary key, --25 octets
	nom varchar(25), --25 octets
	prenom varchar(25), --25 octets
    email varchar(50), -- 50 octets
    mdp varchar(20)     --20 octets
);

CREATE TABLE question (
	idQ serial primary key,
	auteurQ varchar(5000) REFERENCES personne(pseudo),
	dateQ Date DEFAULT NOW(),
    theme varchar(25),
    descriptions varchar(100),
    resolue boolean
);

CREATE TABLE reponse (
	idR serial primary key,
	auteurR varchar(25) REFERENCES personne(pseudo),
	dateR Date DEFAULT NOW(),
    idQ integer REFERENCES question(idQ),
    messages varchar(300)
);

CREATE TABLE evaluation (
	pseudo varchar(25) REFERENCES personne(pseudo),
	idR integer REFERENCES reponse(idR),
	note numeric,
    PRIMARY KEY(pseudo, idR)
);

INSERT INTO personne VALUES ('Sacane', 'Ramaroson', 'Johan', 'johan.ramaroson@gmail.com', '01012000');
INSERT INTO personne VALUES ('Verestah', 'Menaa', 'Mathis', 'mathis.menaa@gmail.com', '0101200011');

INSERT INTO question(auteurQ, theme, descriptions, resolue) VALUES ('Sacane', 'Examen', 'Peut on reussir bdd ?', false);
INSERT INTO reponse(auteurR, dateR, idQ, messages) VALUES ('Verestah', NOW(), 1, 'On va réussir bdd');

INSERT INTO evaluation VALUES ('Sacane', 1, 4);

--3.Resolue : 

--CREATE TRIGGER checkOnResolue
--BEFORE UPDATE OF resolue ON 
--WHEN (new.resolue = true) 
--EXECUTE PROCEDURE noReopen();
