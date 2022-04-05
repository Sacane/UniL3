#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Implémentation d'un graphe à l'aide d'une liste d'adjacence. Les n sommets
sont identifiés par de simples naturels (0, 1, 2, ..., n-1)."""
from collections import *


class ListeAdjacence(object):
    def __init__(self, num=0):
        """Initialise un graphe sans arêtes sur num sommets.

        >>> G = ListeAdjacence(3)
        >>> G._liste_adjacence
        [[], [], []]
        """
        self.nb_arete = 0
        self.id_sommet = num - 1
        self._liste_adjacence = [list() for _ in range(num)]

    def ajouter_arete(self, source, destination):
        """Ajoute l'arête {source, destination} au graphe, en créant les
        sommets manquants le cas échéant.

        >>> G = ListeAdjacence()
        >>> G.ajouter_sommet()
        0
        >>> G.aretes()
        []
        >>> G.ajouter_sommet()
        1
        >>> G.ajouter_sommet()
        2
        >>> G.ajouter_arete(0, 1)
        >>> G.aretes()
        [(0, 1)]

        """
        m = max(source, destination)
        if m > self.id_sommet:
            for i in range(self.id_sommet, m):
                self.ajouter_sommet()

        if not self.contient_arete(source, destination):
            self.nb_arete += 1
            self._liste_adjacence[source].append(destination)
            if source != destination:
                self._liste_adjacence[destination].append(source)

    def ajouter_aretes(self, iterable):
        """Ajoute toutes les arêtes de l'itérable donné au graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples de naturels.

        >>> G = ListeAdjacence(3)
        >>> it = [(1, 2), (0, 1), (1, 0), (0, 0)]
        >>> G.ajouter_aretes(it)
        >>> G.aretes()
        [(0, 1), (0, 0), (1, 2)]

        """
        for couple in iterable:
            self.ajouter_arete(int(couple[0]), int(couple[1]))

    def ajouter_sommet(self):
        """Ajoute un nouveau sommet au graphe et renvoie son identifiant.

        >>> G = ListeAdjacence()
        >>> G.ajouter_sommet()
        0
        >>> G._liste_adjacence
        [[]]
        >>> G.ajouter_sommet()
        1
        >>> G._liste_adjacence
        [[], []]
        """
        self._liste_adjacence.append([])
        self.id_sommet += 1
        return self.id_sommet

    def aretes(self):
        """Renvoie l'ensemble des arêtes du graphe sous forme de couples (si on
        les stocke sous forme de paires, on ne peut pas stocker les boucles,
        c'est-à-dire les arêtes de la forme (u, u)).

        >>> G = ListeAdjacence(3)
        >>> it = [(1, 2), (0, 1), (1, 0), (0, 0)]
        >>> G.ajouter_aretes(it)
        >>> G.aretes()
        [(0, 1), (0, 0), (1, 2)]
        """
        res = []

        i = 0
        for sommet in self._liste_adjacence:
            for arete in sommet:
                if not (arete, i) in res:
                    res.append((i, arete))
            i += 1
        return res

    def boucles(self):
        """Renvoie les boucles du graphe, c'est-à-dire les arêtes reliant un
        sommet à lui-même.

        >>> G = ListeAdjacence(10)
        >>> G.ajouter_aretes([(1, 3), (1, 1), (4, 9), (9, 4), (8, 2), (4, 4)])
        >>> print(G.boucles())
        [1, 4]

        """
        res = []
        for i in range(self.nombre_sommets()):
            if i in self._liste_adjacence[i]:
                res.append(i)
        return res

    def contient_arete(self, u, v):
        """Renvoie True si l'arête {u, v} existe, False sinon.

        >>> G = ListeAdjacence(10)
        >>> G.ajouter_aretes([(1, 3), (2, 2), (2, 5), (1, 3), (0, 0)])
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
        """
        if v > self.id_sommet:
            return False
        if v in self._liste_adjacence[u]:
            return True
        else:
            return False

    def contient_sommet(self, u):
        """Renvoie True si le sommet u existe, False sinon.

        >>> G = ListeAdjacence()
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
        """

        if self.id_sommet >= u:
            return True
        else:
            return False

    def degre(self, sommet):
        """Renvoie le degré d'un sommet, c'est-à-dire le nombre de voisins
        qu'il possède.

        >>> G = ListeAdjacence(5)
        >>> G.ajouter_aretes([(0, 0), (0, 1), (0, 3)])
        >>> print(G.degre(0))
        3
        """

        return len(self._liste_adjacence[sommet])

    def nombre_aretes(self):
        """Renvoie le nombre d'arêtes du graphe.

        >>> G = ListeAdjacence(5)
        >>> G.ajouter_aretes([(1, 2), (2, 2), (1, 2)])
        >>> G.nombre_aretes()
        2
        """

        return self.nb_arete

    def nombre_boucles(self):
        """Renvoie le nombre d'arêtes de la forme {u, u}.

        >>> G = ListeAdjacence(10)
        >>> it = [(1, 2), (3, 8), (0, 1), (5, 5), (9, 9)]
        >>> G.ajouter_aretes(it)
        >>> G.nombre_boucles()
        2
        """
        nb_boucle = 0
        for (key, value) in self.aretes():
            if key == value:
                nb_boucle += 1
        return nb_boucle

    def nombre_sommets(self):
        """Renvoie le nombre de sommets du graphe.

        >>> from random import randint
        >>> n = randint(0, 1000)
        >>> ListeAdjacence(n).nombre_sommets() == n
        True
        """
        return self.id_sommet + 1

    def retirer_arete(self, u, v):
        """Retire l'arête {u, v} si elle existe; provoque une erreur sinon.

        >>> G = ListeAdjacence(10)
        >>> it = [(1, 2), (3, 8), (0, 1), (5, 5), (9, 9)]
        >>> G.ajouter_aretes(it)
        >>> print(G.contient_arete(2, 1))
        True
        >>> G.retirer_arete(1, 2)
        >>> b = (1, 2) not in G.aretes()
        >>> print(b)
        True
        >>> print((2, 1) not in G.aretes())
        True
        >>> G.retirer_arete(0, 0)
        Traceback (most recent call last):
            ...
        ValueError: l'arete n'est pas dans le graphe


        """
        if (u, v) not in self.aretes():
            raise ValueError("l'arete n'est pas dans le graphe")
        if v <= self.id_sommet and v in self._liste_adjacence[u]:
            self._liste_adjacence[u].remove(v)
            self.nb_arete -= 1
        if u <= self.id_sommet and u in self._liste_adjacence[v]:
            self._liste_adjacence[v].remove(u)
            self.nb_arete -= 1

    def retirer_aretes(self, iterable):
        """Retire toutes les arêtes de l'itérable donné du graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples d'éléments (quel que soit le type du couple).
        Renvoi un boolean spécifiant si oui ou non l'arête à bien été retirer ou non.

        """
        tout_arete_ajoute = True
        for couple in iterable:
            try:
                self.retirer_arete(couple[0], couple[1])
            except:
                tout_arete_ajoute = False
        return tout_arete_ajoute

    def retirer_sommet(self, sommet):
        """Déconnecte un sommet du graphe et le supprime.

        >>> G = ListeAdjacence(5)
        >>> G.ajouter_aretes([(1, 2), (0, 3), (1, 1), (2, 3)])
        >>> G._liste_adjacence
        [[3], [2, 1], [1, 3], [0, 2], []]
        >>> G.retirer_sommet(1)
        >>> G._liste_adjacence
        [[2], [2], [0, 1], []]

        >>> F = ListeAdjacence()
        >>> F.ajouter_aretes([(0, 1), (0, 3), (0, 2), (1, 3), (2, 2), (2, 3), (1, 2), (1, 1)])
        >>> F.retirer_sommet(2)
        >>> F._liste_adjacence
        [[1, 2], [0, 2, 1], [0, 1]]
        """
        if not self.contient_sommet(sommet):
            raise ValueError("le sommet ne fait pas partie du graphe")
        delet = []
        for u in self.sommets():
            for voisins in range(self.degre(u)):
                v = self._liste_adjacence[u][voisins]
                if v > sommet:
                    self._liste_adjacence[u][voisins] -= 1
                if v == sommet:
                    delet.append((u, sommet))
        self.retirer_aretes(delet)
        self._liste_adjacence.pop(sommet)
        self.id_sommet -= 1

    def retirer_sommets(self, iterable):
        """Efface les sommets de l'itérable donné du graphe, et retire toutes
        les arêtes incidentes à ces sommets.


        >>> G = ListeAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (1, 3), (1, 2)])
        >>> G._liste_adjacence
        [[1, 3], [0, 3, 2], [1], [0, 1]]
        >>> G.retirer_sommets([1, 2])
        >>> G._liste_adjacence
        [[1], [0]]
        """
        sorted_iterable = sorted(iterable, reverse=True)

        for sommet in sorted_iterable:
            self.retirer_sommet(sommet)

    def sommets(self):
        """Renvoie l'ensemble des sommets du graphe.

        >>> G = ListeAdjacence()
        >>> G.ajouter_aretes([(3, 2), (0, 0)])
        >>> G.sommets()
        [0, 1, 2, 3]

        """
        l = []
        for i in range(self.nombre_sommets()):
            l.append(i)
        return l

    def sous_graphe_induit(self, iterable):
        """Renvoie le sous-graphe induit par l'itérable de sommets donné.

        >>> G = ListeAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (0, 2), (1, 3), (2, 2), (2, 3), (1, 2), (1, 1)])
        >>> F = G.sous_graphe_induit({0, 1, 3})
        >>> F._liste_adjacence
        [[1, 2], [0, 2, 1], [0, 1]]

        """

        res = ListeAdjacence()
        res.ajouter_aretes(self.aretes())
        for i in range(len(res._liste_adjacence)):
            if i not in iterable:
                res.retirer_sommet(i)

        return res

    def voisins(self, sommet):
        """Renvoie la liste des voisins d'un sommet.

        >>> G = ListeAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (0, 2), (1, 3), (2, 2), (2, 3), (1, 2), (1, 1)])
        >>> G.voisins(0)
        [1, 3, 2]
        >>> G.voisins(1)
        [0, 3, 2, 1]
        """
        return self._liste_adjacence[sommet]


def main():
    import doctest
    doctest.testmod()


if __name__ == "__main__":
    main()
