DROP TABLE IF EXISTS historiquePrix;
CREATE TABLE historiquePrix (
    log_id serial primary key,
    date date,
    idmag int references magasin(idmag),
    idpro int references produit(idpro),
    ancienPrix numeric(5,2),
    nouveauPrix numeric(5,2)
);


CREATE OR REPLACE FUNCTION majPrix()
RETURNS TRIGGER AS
$$
    DECLARE
        best record;
    BEGIN
        INSERT INTO historiquePrix 
        VALUES (DEFAULT, NOW(), NEW.idmag, NEW.idpro, OLD.prixunit, NEW.prixunit);

        RAISE NOTICE 'Le prix du produit % du magasin % est passé de % à %', NEW.idpro, NEW.idmag, OLD.prixunit, NEW.prixunit;

        PERFORM * FROM stocke WHERE prixunit < NEW.prixunit;
        IF NOT FOUND THEN
            RAISE NOTICE 'Ce produit est au meilleur prix du marché';
            SELECT nom, ville, idpro, libelle INTO best
            FROM stocke NATURAL JOIN produit NATURAL JOIN magasin;
            RAISE NOTICE 'Il est vendu chez % à % (%: %)', best.nom, best.ville, best.idpro, best.libelle;
        END IF;

        RETURN NEW;
    END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER on_update_prix
BEFORE UPDATE ON stocke
FOR EACH ROW
WHEN (OLD.prixunit <> NEW.prixunit)
EXECUTE PROCEDURE majPrix();

-- DROP TRIGGER on_update_prix ON stocke;
SELECT * FROM historiquePrix;
UPDATE stocke SET prixunit = 10.00 WHERE idmag = 44 AND idpro = 193;
SELECT * FROM historiquePrix;