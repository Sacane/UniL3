

CREATE VIEW productCabale AS
(
	SELECT idpro, libelle, prixUnit FROM 
    magasin NATURAL JOIN stocke NATURAL JOIN 
    produit WHERE nom='La cabale des cables'
);