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
        [(0, 1), (1, 0)]

        """
        m = max(source, destination)
        if m > self.id_sommet:
            for i in range(self.id_sommet, m):
                self.ajouter_sommet()

        if not self.contient_arete(source, destination):
            self.nb_arete += 1
            self._liste_adjacence[source].append(destination)
            if source != destination:
                self.nb_arete += 1
                self._liste_adjacence[destination].append(source)

    def init_sommet(self, init=1):
        for i in range(init):
            self.ajouter_sommet()

    def ajouter_aretes(self, iterable):
        """Ajoute toutes les arêtes de l'itérable donné au graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples de naturels.

        >>> G = ListeAdjacence()
        >>> G.init_sommet(3)
        >>> it = [(1, 2), (0, 1), (1, 0), (0, 0)]
        >>> G.ajouter_aretes(it)
        >>> G.aretes()
        [(0, 1), (0, 0), (1, 2), (1, 0), (2, 1)]

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

        >>> G = ListeAdjacence()
        >>> G.init_sommet(3)
        >>> it = [(1, 2), (0, 1), (1, 0), (0, 0)]
        >>> G.ajouter_aretes(it)
        >>> G.aretes()
        [(0, 1), (0, 0), (1, 2), (1, 0), (2, 1)]
        """
        res = []
        i = 0
        for sommet in self._liste_adjacence:
            for arete in sommet:
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
        for i in range(len(self._liste_adjacence)):
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
        2
        """

        return len(self._liste_adjacence[sommet]) if sommet not in self._liste_adjacence[sommet] else len(
            self._liste_adjacence[sommet]) - 1

    def nombre_aretes(self):
        """Renvoie le nombre d'arêtes du graphe.

        >>> G = ListeAdjacence(5)
        >>> G.ajouter_aretes([(1, 2), (2, 2), (1, 2)])
        >>> G.nombre_aretes()
        3
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
        for i in range(len(self._liste_adjacence)):
            if i in self._liste_adjacence[i]:
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
        >>> print((2, 1) in G.aretes())
        True
        >>> G.retirer_arete(1, 2)
        >>> b = (1, 2) not in G.aretes()
        >>> print(b)
        True
        >>> print((2, 1) not in G.aretes())
        True


        """

        if v <= self.id_sommet and v in self._liste_adjacence[u]:
            self._liste_adjacence[u].remove(v)
            self._liste_adjacence[v].remove(u)

    def retirer_aretes(self, iterable):
        """Retire toutes les arêtes de l'itérable donné du graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples d'éléments (quel que soit le type du couple).
        Renvoi un boolean spécifiant si oui ou non l'arête à bien été retirer ou non.

        """

        for couple in iterable:
            if len(couple) > 2:
                return False
            self.retirer_arete(couple[0], couple[1])
        return True

    def retirer_sommet(self, sommet):
        """Déconnecte un sommet du graphe et le supprime.

        >>> G = ListeAdjacence(5)
        >>> G.ajouter_aretes([(1, 2), (0, 3), (1, 1)])
        >>> G.sommets()
        [[3], [2, 1], [1], [0], []]
        >>> G.retirer_sommet(1)
        >>> G.sommets()
        [[3], [], [], [0], []]
        """

        self._liste_adjacence[sommet].clear()
        for s in self._liste_adjacence:
            if sommet in s:
                s.remove(sommet)

    def retirer_sommets(self, iterable):
        """Efface les sommets de l'itérable donné du graphe, et retire toutes
        les arêtes incidentes à ces sommets.

        """

        for sommet in iterable:
            self.retirer_sommet(sommet)



    def sommets(self):
        """Renvoie l'ensemble des sommets du graphe.

        >>> G = ListeAdjacence()
        >>> G.ajouter_aretes([(3, 2), (0, 0)])
        >>> G.sommets()
        [[0], [], [3], [2]]

        """
        return self._liste_adjacence

    def sous_graphe_induit(self, iterable):
        """Renvoie le sous-graphe induit par l'itérable de sommets donné.

        >>> G = ListeAdjacence()
        >>> G.ajouter_aretes([(0, 1), (0, 3), (0, 2), (1, 3), (2, 2), (2, 3), (1, 2), (1, 1)])
        >>> F = G.sous_graphe_induit({0, 1, 3})
        >>> F._liste_adjacence
        [[1, 3], [0, 3, 1], [], [0, 1]]

        """

        res = ListeAdjacence(max(iterable) + 1)
        for sommet in iterable:
            for voisin in self.voisins(sommet):
                if voisin in iterable:
                    res.ajouter_arete(sommet, voisin)
        return res

    def voisins(self, sommet):
        """Renvoie la liste des voisins d'un sommet."""
        return self._liste_adjacence[sommet]


def main():
    import doctest
    doctest.testmod()


if __name__ == "__main__":
    main()
