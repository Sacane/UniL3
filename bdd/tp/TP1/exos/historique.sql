DROP TABLE IF EXISTS historiquePrix;
DROP TRIGGER IF EXISTS on_update_prix ON stocke;

CREATE TABLE historiquePrix (
    log_id serial primary key,
    date date,
    idmag int references magasin(idmag),
    idpro int references produit(idpro),
    ancienPrix numeric(5,2),
    nouveauPrix numeric(5,2)
);

CREATE OR REPLACE FUNCTION add_price_history()
RETURNS TRIGGER AS
$$
    DECLARE best record;
    BEGIN
        INSERT INTO historiquePrix VALUES 
        (DEFAULT, NOW(), NEW.idmag, NEW.idpro, OLD.prixUnit, NEW.prixUnit);

        PERFORM * FROM stocke WHERE prixUnit < NEW.prixUnit;
        IF NOT FOUND THEN
            RAISE NOTICE 'Ce produit est devenue le meilleure du marché actuel';
            SELECT nom, ville, idpro, libelle INTO best FROM stocke NATURAL JOIN produit NATURAL JOIN magasin WHERE idpro = NEW.idpro;
            RAISE NOTICE 'Il est vendu dans le magasin % situé à %, reférence : %, produit : %', best.nom, best.ville, best.idpro, best.libelle;
        END IF;
        RETURN NEW;
    END;
    
$$
LANGUAGE plpgsql;

CREATE TRIGGER on_update_prix
BEFORE UPDATE ON stocke
FOR EACH ROW
WHEN (OLD.prixunit <> NEW.prixunit)
EXECUTE PROCEDURE add_price_history();

--UPDATE stocke SET prixunit = 19 WHERE idpro = 40 AND idmag = 0;

--3. 
--Test à incrémenter à chaque tentative -> UPDATE stocke SET prixunit = 310 WHERE idpro = 40 AND idmag = 0;


