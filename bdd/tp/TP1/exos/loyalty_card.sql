DROP TRIGGER IF EXISTS loyalty_trigger ON contient;
DROP TRIGGER IF EXISTS treshold ON fidelite;

CREATE OR REPLACE FUNCTION update_loyalty()
RETURNS TRIGGER AS 
$$
    DECLARE 
    pts int;
    delta int;
    fac facture%ROWTYPE;
    loyalty fidelite%ROWTYPE;


    BEGIN
        pts = NEW.prixUnit * NEW.quantite;

        SELECT * into fac FROM facture WHERE idfac = NEW.idfac;
        SELECT * into loyalty FROM fidelite WHERE numcli = fac.numcli AND idmag = fac.idmag;
        IF NOT FOUND THEN 
            RAISE NOTICE 'Dommage ! Vous n avez pas de cartes de fidelité, vous auriez pu quand meme gagner % points :))))', pts;
            RETURN NULL;
        END IF;
        IF (TG_OP = 'INSERT') THEN
            RAISE NOTICE 'Insertion en cours...';
            RAISE NOTICE 'Vous avez gagné % points !', pts;
            UPDATE fidelite SET points = points + pts WHERE idmag = fac.idmag AND fac.numcli = numcli;
            RETURN NEW;
        END IF;
        IF (TG_OP = 'UPDATE') THEN 
            RAISE NOTICE 'Mis à jour en cours...';
            IF pts < loyalty.points THEN 
                RAISE NOTICE 'Ne vous inquiétez pas, vos points ne diminiueront pas.';
                UPDATE fidelite SET points = loyalty.points WHERE idmag = fac.idmag AND fac.numcli = numcli;
                RETURN NEW;
            ELSE 
                delta = pts - loyalty.points;
                RAISE NOTICE 'Vous avez gagné % nouveaux points ! Vos points totaux sont désormais de %', delta, pts;
                UPDATE fidelite SET points = loyalty.points WHERE idmag = fac.idmag AND fac.numcli = numcli;
                RETURN NEW;
            END IF;

        END IF;

        RETURN NEW;
    END;
$$
language plpgsql;

-- Ce trigger met a jour les points de fidélité du client losqu'il achète des produits
-- Si le client en question ne possède pas de cartes de fidélité, on lui envoi un message avec le nombre de 
-- Point qu'il aurait pu gagner
CREATE TRIGGER loyalty_trigger
AFTER UPDATE OR INSERT ON contient
FOR EACH ROW 
EXECUTE PROCEDURE update_loyalty();


-- 
-- INSERT INTO contient VALUES (0, 50, 10, 5);
-- -> Pas de carte de fidélité
-- INSERT INTO contient VALUES (8, 10, 10, 5);
-- -> Gain de 50 points sur la carte 

--SELECT * FROM fidelite WHERE numcli=92; --> On recherche le client 92 et on regarde son nombre de points -> 102
-- INSERT INTO contient VALUES (16 , 77, 10, 20); 
-- SELECT * FROM fidelite WHERE numcli=92; --> Nouveau nombre de pts de fidélité du 92 = 302

--TEST UPDATE : 
--UPDATE contient SET prixUnit = 110 WHERE idpro=87 AND idfac=16;


CREATE OR REPLACE FUNCTION control_treshold()
RETURNS TRIGGER AS 
$$
    BEGIN
        RAISE NOTICE 'Attention, vous avez gagne trop de points de fidelite ! Vos points sont remis automatiquement à 1000';
        NEW.points = 1000;
        RETURN NEW;
    END;
    
$$
language plpgsql;


--Ce trigger vérifie que les points de fidélités du client ne dépassent pas 1000
CREATE TRIGGER treshold
BEFORE UPDATE ON fidelite
FOR EACH ROW
WHEN (NEW.points > 1000)
EXECUTE PROCEDURE control_treshold();

--\i magasin_trigger.sql pour tester les triggers réunitialisez la table avant au cas où
--\i loyalty_card.sql

-- INSERT INTO contient VALUES (16 , 78, 100, 20); On insère un achat équivalent à 2000 points pour faire interagir les deux triggers
-- -> On reçoit un message indiquant que le client à gagné trop de points.

-- SELECT * FROM fidelite WHERE numcli=92 -> On check les points de fidelite du client 92, on s'aperçoit que ses points sont bien à 1000. 

