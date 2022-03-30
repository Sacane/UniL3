CREATE OR REPLACE FUNCTION verif_stock() 
RETURNS TRIGGER AS
$$
	DECLARE 
		sto stocke%ROWTYPE;
		mag int;

	BEGIN

	SELECT idmag INTO mag FROM facture WHERE idfac = NEW.idfac;
	RAISE NOTICE 'La facture concerne le magasin %.',mag;

	SELECT * INTO sto FROM stocke WHERE idmag = mag AND idpro = NEW.idpro;
	IF NOT FOUND THEN
		RAISE NOTICE 'Le produit % n''est pas disponible dans le magasin %.', sto.idpro, mag;
		RETURN NULL;
	ELSIF NEW.quantite > sto.quantite THEN  -- Si la quantité demandé est trop élevé par rapport à la quantité actuel du produit,
											-- On assigne la totalité de la quantité restante 
		RAISE NOTICE 'Le produit n est pas disponible dans la quantité demandée, tout le stocke restant vous sera attribué : %', sto.quantite;
		NEW.quantite = sto.quantite;
	END IF;
	
	UPDATE stocke SET quantite = quantite - NEW.quantite 
	WHERE idmag = mag AND NEW.idpro = idpro;
	NEW.prixUnit = sto.prixUnit;
	RETURN NEW;
	END;
$$ language plpgsql;

CREATE TRIGGER stock_trigger
BEFORE INSERT
ON contient
FOR EACH ROW
EXECUTE PROCEDURE verif_stock();



-- 1. ALTER TABLE contient DISABLE TRIGGER verif_stock;
-- ALTER TABLE contient ENABLE TRIGGER verif_stock;

-- 2. Le trigger s'active avant chaque insertion dans la table contient
--	  Elle vérifie bien si le produit est encore disponible dans le magasin en question avant de l'ajouter dans la table contient

--INSERT INTO contient VALUES(0, 0, 20, 2);  -> Pas assez de quantité dans le magasin
--INSERT INTO contient VALUES(3, 182, 232.92, 2);

-- EXERCICE 2 


