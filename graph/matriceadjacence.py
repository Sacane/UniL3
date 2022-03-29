#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Implémentation d'un graphe à l'aide d'une matrice d'adjacence. Les n sommets
sont identifiés par de simples naturels (0, 1, 2, ..., n-1)."""
import graphviz


class MatriceAdjacence(object):
    def __init__(self, num=0):
        """Initialise un graphe sans arêtes sur num sommets.

        >>> G = MatriceAdjacence()
        >>> G._matrice_adjacence
        []
        """
        self.nb_sommet = num
        self.nb_arete = 0
        self._matrice_adjacence = [[0] * num for _ in range(num)]

    def ajouter_arete(self, source, destination):
        """Ajoute l'arête {source, destination} au graphe, en créant les
        sommets manquants le cas échéant.


        >>> G = MatriceAdjacence()
        >>> G.ajouter_arete(0, 2)
        >>> G._matrice_adjacence
        [[0, 0, 1], [0, 0, 0], [0, 0, 0]]

        >>> F = MatriceAdjacence(3)
        >>> F.ajouter_arete(0, 5)
        >>> F._matrice_adjacence
        [[0, 0, 0, 0, 0, 1], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]

        >>> F.ajouter_arete(2, 3)
        >>> F._matrice_adjacence
        [[0, 0, 0, 0, 0, 1], [0, 0, 0, 0, 0, 0], [0, 0, 0, 1, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]


        >>> P = MatriceAdjacence()
        >>> P.ajouter_arete(0, 6)
        >>> P._matrice_adjacence
        [[0, 0, 0, 0, 0, 0, 1], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0]]
        >>> P.ajouter_arete(5, 4)
        >>> P._matrice_adjacence
        [[0, 0, 0, 0, 0, 0, 1], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 1, 0], [0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0]]
        """

        max_sommet = max(source, destination)
        while max_sommet >= self.nb_sommet:
            self.ajouter_sommet()
        if max_sommet == source:
            source, destination = destination, source
        self._matrice_adjacence[source][destination] = 1
        self.nb_arete += 1

    def ajouter_aretes(self, iterable):
        """Ajoute toutes les arêtes de l'itérable donné au graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples de naturels.


        >>> G = MatriceAdjacence(3)
        >>> it = [(1, 2), (0, 1), (1, 0), (0, 0), (0.5, 3)]
        >>> G.ajouter_aretes(it)
        >>> G.aretes()
        [(0, 0), (0, 1), (1, 2)]
        """

        for (src, dest) in iterable:

            if type(src) != int or type(dest) != int:
                continue
            self.ajouter_arete(src, dest)

    def ajouter_sommet(self):
        """Ajoute un nouveau sommet au graphe et renvoie son identifiant.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_sommet()
        0
        >>> G._matrice_adjacence
        [[0]]
        >>> G.ajouter_sommet()
        1
        >>> G._matrice_adjacence
        [[0, 0], [0, 0]]
        >>> G.ajouter_sommet()
        2
        >>> G._matrice_adjacence
        [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        >>> G.ajouter_sommet()
        3
        >>> G.ajouter_sommet()
        4
        >>> G._matrice_adjacence
        [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
        """
        self.nb_sommet += 1
        self._matrice_adjacence.append([0] * self.nb_sommet)
        for i in range(self.nb_sommet - 1):
            self._matrice_adjacence[i].append(0)
        return self.nb_sommet - 1

    def aretes(self):
        """Renvoie l'ensemble des arêtes du graphe sous forme de couples (si on
        les stocke sous forme de paires, on ne peut pas stocker les boucles,
        c'est-à-dire les arêtes de la forme (u, u)).

        >>> G = MatriceAdjacence(3)
        >>> it = [(1, 2), (0, 1), (1, 0), (0, 0)]
        >>> G.ajouter_aretes(it)
        >>> G.aretes()
        [(0, 0), (0, 1), (1, 2)]
        """
        res = []
        for i in range(self.nb_sommet):
            for j in range(self.nb_sommet):
                if self._matrice_adjacence[i][j] == 1 and (j, i) not in res:
                    res.append((i, j))
        return res

    def boucles(self):
        """Renvoie les boucles du graphe, c'est-à-dire les arêtes reliant un
        sommet à lui-même.


        >>> G = MatriceAdjacence(10)
        >>> G.ajouter_aretes([(1, 3), (1, 1), (4, 9), (9, 4), (8, 2), (4, 4)])
        >>> print(G.boucles())
        [1, 4]
        """

        return [src for (src, dest) in self.aretes() if src == dest]

    def contient_arete(self, u, v):
        """Renvoie True si l'arête {u, v} existe, False sinon.

        >>> G = MatriceAdjacence(10)
        >>> G.ajouter_aretes([(1, 3), (2, 2), (2, 5), (0, 0)])
        >>> G.contient_arete(1, 3)
        True
        >>> G.contient_arete(4, 5)
        False
        >>> G.contient_arete(1, 7)
        False
        >>> G.contient_arete(0, 1)
        False
        >>> G.contient_arete(2, 2)
        True
        >>> G.contient_arete(0, 0)
        True
        >>> G.contient_arete(3, 1)
        True
        """
        if u > self.nb_sommet or v > self.nb_sommet:
            return False
        if self._matrice_adjacence[u][v] == 1 or self._matrice_adjacence[v][u] == 1:
            return True
        else:
            return False

    def contient_sommet(self, u):
        """Renvoie True si le sommet u existe, False sinon.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_sommet()
        0
        >>> G.ajouter_sommet()
        1
        >>> G.ajouter_sommet()
        2
        >>> G.ajouter_sommet()
        3
        >>> print(G.contient_sommet(2))
        True
        >>> print(G.contient_sommet(3))
        True
        >>> print(G.contient_sommet(5))
        False
        >>> G.ajouter_arete(9, 3)
        >>> print(G.contient_sommet(8))
        True
        >>> print(G.contient_sommet(9))
        True
        >>> print(G.contient_arete(9, 3))
        True
        >>> print(G.contient_arete(3, 9))
        True
        """
        return self.nb_sommet >= u

    def degre(self, sommet):
        """Renvoie le degré d'un sommet, c'est-à-dire le nombre de voisins
        qu'il possède.

        >>> G = MatriceAdjacence(5)
        >>> G.ajouter_aretes([(0, 0), (0, 1), (0, 3)])
        >>> print(G.degre(0))
        3
        """
        cpt = 0
        for i in range(len(self._matrice_adjacence[sommet])):
            if self._matrice_adjacence[sommet][i] == 1:
                cpt += 1
        return cpt

    def nombre_aretes(self):
        """Renvoie le nombre d'arêtes du graphe.


        >>> G = MatriceAdjacence(5)
        >>> G.ajouter_aretes([(1, 2), (2, 2), (1, 2)])
        >>> G.nombre_aretes()
        3
        """
        return self.nb_arete

    def nombre_boucles(self):
        """Renvoie le nombre d'arêtes de la forme {u, u}.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(0, 0), (5, 5), (3, 0), (0, 2), (4, 4), (3, 2)])
        >>> print(G.nombre_boucles())
        3
        """

        count = 0
        for (key, value) in self.aretes():
            if key == value:
                count += 1
        return count

    def nombre_sommets(self):
        """Renvoie le nombre de sommets du graphe.

        >>> from random import randint
        >>> n = randint(0, 1000)
        >>> MatriceAdjacence(n).nombre_sommets() == n
        True
        """
        return self.nb_sommet

    def retirer_arete(self, u, v):
        """Retire l'arête {u, v} si elle existe; provoque une erreur sinon.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 2), (0, 5), (3, 2), (1, 2)])
        >>> print(G.contient_arete(0, 5))
        True
        >>> G.retirer_arete(0, 5)
        >>> G.contient_arete(0, 5)
        False
        >>> G.retirer_arete(0, 8)
        Traceback (most recent call last):
            ...
        ValueError: l'arete n'est pas dans le graphe
        >>> G.nb_arete
        4
        >>> G.ajouter_arete(2, 3)
        >>> G.retirer_arete(3, 2)
        Traceback (most recent call last):
            ...
        ValueError: l'arete n'est pas dans le graphe
        """
        if (u, v) not in self.aretes():
            raise ValueError("l'arete n'est pas dans le graphe")

        if self._matrice_adjacence[u][v] == 1:
            self._matrice_adjacence[u][v] = 0
            self.nb_arete -= 1

        elif self._matrice_adjacence[v][u] == 1:
            self._matrice_adjacence[v][u] = 0
            self.nb_arete -= 1

    def retirer_aretes(self, iterable):
        """Retire toutes les arêtes de l'itérable donné du graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples d'éléments (quel que soit le type du couple).

        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(0, 0), (0, 1), (0, 3)])
        >>> G._matrice_adjacence
        [[1, 1, 0, 1], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        >>> G.retirer_aretes([(0, 0), (0, 3)])
        True
        >>> G._matrice_adjacence
        [[0, 1, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        >>> G.nombre_aretes()
        1
        """
        tout_arete_ajoute = True
        for (src, dest) in iterable:
            try:
                self.retirer_arete(src, dest)
            except:
                tout_arete_ajoute = False
        return tout_arete_ajoute

    def retirer_sommet(self, sommet):
        """Déconnecte un sommet du graphe et le supprime.

        >>> G = MatriceAdjacence()
        >>> for _ in range(4):
        ...     G.ajouter_sommet()
        0
        1
        2
        3
        >>> G._matrice_adjacence
        [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        >>> G.retirer_sommet(2)
        >>> G._matrice_adjacence
        [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
        >>> G.ajouter_arete(0, 2)
        >>> G.ajouter_arete(1, 0)
        >>> G._matrice_adjacence
        [[0, 1, 1], [0, 0, 0], [0, 0, 0]]
        >>> G.retirer_sommet(1)
        >>> G._matrice_adjacence
        [[0, 1], [0, 0]]
        >>> G.ajouter_sommet()
        2
        >>> G.ajouter_sommet()
        3
        >>> G._matrice_adjacence
        [[0, 1, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        >>> G.ajouter_arete(1, 2)
        >>> G._matrice_adjacence
        [[0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        >>> G.retirer_sommet(2)
        >>> G._matrice_adjacence
        [[0, 1, 0], [0, 0, 0], [0, 0, 0]]

        """
        if not self.contient_sommet(sommet):
            raise ValueError("le sommet ne fait pas partie du graphe")
        for i in range(self.nb_sommet):
            self._matrice_adjacence[i].pop(sommet)
        self._matrice_adjacence.pop(sommet)
        self.nb_sommet -= 1

    def retirer_sommets(self, iterable):
        """Efface les sommets de l'itérable donné du graphe, et retire toutes
        les arêtes incidentes à ces sommets. Renvoi True si tout les sommets
        de l'iterable ont ete retire avec succes, False sinon.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (1, 3), (1, 2)])
        >>> G._matrice_adjacence
        [[0, 1, 0, 1], [0, 0, 1, 1], [0, 0, 0, 0], [0, 0, 0, 0]]

        >>> G.retirer_sommets([1, 2])
        True
        >>> G.contient_sommet(3)
        False
        >>> G.contient_arete(1, 3)
        False

        """
        sommet_ajoute = True
        for sommet in iterable:
            try:
                self.retirer_sommet(sommet)
            except:
                sommet_ajoute = False
        return sommet_ajoute

    def sommets(self):
        """Renvoie l'ensemble des sommets du graphe.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(3, 2), (0, 0)])
        >>> G.sommets()
        [0, 1, 2, 3]

        """

        return [i for i in range(self.nb_sommet)]

    def sous_graphe_induit(self, iterable):
        """Renvoie le sous-graphe induit par l'itérable de sommets donné.

        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (0, 2), (1, 3), (2, 2), (2, 3), (1, 2), (1, 1)])
        >>> F = G.sous_graphe_induit({0, 1, 3})
        >>> F._matrice_adjacence
        [[0, 1, 1], [0, 1, 1], [0, 0, 0]]

        """
        res = MatriceAdjacence()
        res.ajouter_aretes(self.aretes())
        for i in range(len(res._matrice_adjacence)):
            if i not in iterable:
                res.retirer_sommet(i)
        return res

    def voisins(self, sommet):
        """Renvoie la liste des voisins d'un sommet.
        >>> G = MatriceAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (0, 2), (1, 3), (2, 2), (2, 3), (1, 2), (1, 1)])
        >>> G.voisins(0)
        [1, 2, 3]
        >>> G.voisins(1)
        [0, 1, 2, 3]

        """

        return [i for i in range(self.nb_sommet) if self._matrice_adjacence[sommet][i] == 1 or
                self._matrice_adjacence[i][sommet] == 1]


def export_dot(Graphe):
    """Renvoie une chaîne encodant le graphe au format dot.
    """

    dot = graphviz.Graph()
    edges = []
    for sommet in Graphe.sommets():
        dot.node(str(sommet), str(sommet))
    for (src, dest) in Graphe.aretes():
        edges.append(str(src) + str(dest))
    dot.edges(edges)

    return dot


def main():
    import doctest
    doctest.testmod()


if __name__ == "__main__":
    main()
