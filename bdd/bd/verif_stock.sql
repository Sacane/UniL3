DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
\i magasin_trigger.sql

CREATE OR REPLACE FUNCTION majStock()
RETURNS TRIGGER AS
$$
	DECLARE
		mag int; sto stocke%ROWTYPE;s stocke%ROWTYPE;

	BEGIN
        SELECT idmag INTO mag FROM facture WHERE idfac = NEW.idfac;

        RAISE NOTICE 'Le magasin concerné est le magasin %', mag;

        SELECT * INTO sto FROM stocke WHERE idmag = mag AND idpro = NEW.idpro;
        IF NOT FOUND THEN
            RAISE NOTICE 'Le magasin % ne vend pas le produit %.', mag, NEW.idpro;
            RETURN NULL;
        ELSIF NEW.quantite > sto.quantite THEN
            RAISE NOTICE 'Le magasin % n ayant que % exemplaires, la quantite de l insertion est modifiée à %', mag, sto.quantite, sto.quantite;
            NEW.quantite = sto.quantite;
        END IF;

		-- Update of the amount
		UPDATE stocke SET quantite = quantite - NEW.quantite WHERE idmag = mag AND NEW.idpro = idpro;
		NEW.prixUnit = stocke.prixUnit;
		RETURN NEW ;
	END;
$$
LANGUAGE plpgsql;

--Le trigger gère si on a bien ajouter un produit dans le magasin

CREATE TRIGGER verif_stock
BEFORE INSERT ON contient
FOR EACH ROW
EXECUTE PROCEDURE majStock();

--To delete it : DROP TRIGGER verif_stock ON contient; 

--To disable it : ALTER TABLE contient DISABLE TRIGGER verif_stock;

--to enable it : ALTER TABLE contient ENABLE TRIGGER verif_stock;

--INSERT INTO contient VALUES(0, 0, 20, 2);

--SELECT * FROM stocke WHERE idmag = 44 AND idpro = 193;
--INSERT INTO contient VALUES(0, 193, 20, 20000);
--INSERT INTO contient VALUES(0, 193, 20, 120);
--SELECT * FROM stocke WHERE idmag = 44 AND idpro = 193;


DROP TRIGGER IF EXISTS majFid ON contient;
DROP FUNCTION IF EXISTS majFid_fun;

CREATE OR REPLACE FUNCTION majFid_fun()
RETURNS TRIGGER AS
$$
    DECLARE
        pts_gagnes int;
        fac facture%ROWTYPE;
        card fidelite%ROWTYPE;

    BEGIN
        pts_gagnes = NEW.prixunit * NEW.quantite;

        SELECT * INTO fac FROM facture WHERE idfac = NEW.idfac;
        SELECT * INTO card FROM fidelite WHERE fac.numcli = numcli AND fac.idmag = idmag;
        IF NOT FOUND THEN
            RAISE NOTICE 'Si vous aviez une carte, vour auriez gagné % points', pts_gagnes;
            RETURN NEW;
        END IF;

        RAISE NOTICE 'Vous avez gagné % points de fidélité', pts_gagnes;
        UPDATE fidelite SET points = points + pts_gagnes WHERE idmag = fac.idmag AND numcli = fac.numcli;

        RETURN NEW;
    END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER majFid
AFTER UPDATE OR INSERT ON contient
FOR EACH ROW
EXECUTE PROCEDURE majFid_fun();



