"""Implémentation d'un graphe non orienté à l'aide d'un dictionnaire: les clés
sont les sommets, et les valeurs sont les sommets adjacents à un sommet donné.
Les boucles sont autorisées. Les poids ne sont pas autorisés.

On utilise la représentation la plus simple: une arête {u, v} sera présente
deux fois dans le dictionnaire: v est dans l'ensemble des voisins de u, et u
est dans l'ensemble des voisins de v.

"""


class Graphe(object):
    def __init__(self):
        """Initialise un graphe sans arêtes"""
        self.dictionnaire = dict()

    def ajouter_arete(self, u, v, poid):
        """Ajoute une arête entre les sommmets u et v, en créant les sommets
        manquants le cas échéant.

        >>> G = Graphe()
        >>> G.ajouter_arete(0, 1, 5)
        >>> G.contient_sommet(0)
        True
        >>> G.contient_sommet(1)
        True
        >>> G.contient_sommet(5)
        False
        >>> G.contient_arete(1, 0)
        True
        >>> G.contient_arete(0, 1)
        True
        """
        # vérification de l'existence de u et v, et création(s) sinon
        if u not in self.dictionnaire:
            self.dictionnaire[u] = set()
        if v not in self.dictionnaire:
            self.dictionnaire[v] = set()
        # ajout de u (resp. v) parmi les voisins de v (resp. u)
        self.dictionnaire[u].add((v, poid))
        self.dictionnaire[v].add((u, poid))

    def ajouter_aretes(self, iterable):
        """Ajoute toutes les arêtes de l'itérable donné au graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples d'éléments (quel que soit le type du couple).
        """
        for u, v, p in iterable:
            self.ajouter_arete(u, v, p)

    def ajouter_sommet(self, sommet):
        """Ajoute un sommet (de n'importe quel type hashable) au graphe."""
        self.dictionnaire[sommet] = set()

    def ajouter_sommets(self, iterable):
        """Ajoute tous les sommets de l'itérable donné au graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des éléments hashables."""
        for sommet in iterable:
            self.ajouter_sommet(sommet)

    def aretes(self):
        """Renvoie l'ensemble des arêtes du graphe. Une arête est représentée
        par un tuple (a, b, p) avec a <= b afin de permettre le renvoi de boucles.
        >>> G = Graphe()
        >>> G.ajouter_aretes([(1, 2, 10), (3, 8, 2), (0, 1, 9), (5, 5, 8), (9, 9, 11)])
        >>> (1, 2, 10) in G.aretes()
        True
        >>> (3, 8, 2) in G.aretes()
        True
        """
        return {
            tuple((u, v, p)) for u in self.dictionnaire
            for (v, p) in self.dictionnaire[u] if u <= v
        }

    def boucles(self):
        """Renvoie les boucles du graphe, c'est-à-dire les arêtes reliant un
        sommet à lui-même."""
        return {(u, u) for u in self.dictionnaire for a, p in self.dictionnaire[u] if u == a}

    def contient_arete(self, u, v):
        """Renvoie True si l'arête {u, v} existe, False sinon.

        >>> G = Graphe()
        >>> G.ajouter_aretes({(0, 1, 2), (4, 3, 5)})
        >>> G.contient_arete(1, 0)
        True
        >>> G.contient_arete(0, 1)
        True
        >>> G.contient_arete(0, 0)
        False
        >>> G.contient_arete(3, 4)
        True
        >>> G.ajouter_arete(0, 0, 1)
        >>> G.contient_arete(0, 0)
        True
        """
        if self.contient_sommet(u) and self.contient_sommet(v):
            for a, p in self.dictionnaire[v]:
                if u == a:
                    return True
        return False

    def contient_sommet(self, u):
        """Renvoie True si le sommet u existe, False sinon."""
        return u in self.dictionnaire

    def degre(self, sommet):
        """Renvoie le nombre de voisins du sommet; s'il n'existe pas, provoque
        une erreur."""
        return len(self.dictionnaire[sommet])

    def nombre_aretes(self):
        """Renvoie le nombre d'arêtes du graphe."""
        return len(self.aretes())

    def nombre_boucles(self):
        """Renvoie le nombre d'arêtes de la forme {u, u}.

        >>> G = Graphe()
        >>> G.ajouter_aretes([(1, 2, 10), (3, 8, 2), (0, 1, 9), (5, 5, 8), (9, 9, 11)])
        >>> G.nombre_boucles()
        2
        """
        return len(self.boucles())

    def nombre_sommets(self):
        """Renvoie le nombre de sommets du graphe."""
        return len(self.dictionnaire)

    def retirer_arete(self, u, v):
        """Retire l'arête {u, v} si elle existe; provoque une erreur sinon."""
        self.dictionnaire[u].remove(v)  # plante si u ou v n'existe pas
        self.dictionnaire[v].remove(u)  # plante si u ou v n'existe pas

    def retirer_aretes(self, iterable):
        """Retire toutes les arêtes de l'itérable donné du graphe. N'importe
        quel type d'itérable est acceptable, mais il faut qu'il ne contienne
        que des couples d'éléments (quel que soit le type du couple)."""
        for u, v in iterable:
            self.retirer_arete(u, v)

    def retirer_sommet(self, sommet):
        """Efface le sommet du graphe, et retire toutes les arêtes qui lui
        sont incidentes."""
        del self.dictionnaire[sommet]
        # retirer le sommet des ensembles de voisins
        for u in self.dictionnaire:
            self.dictionnaire[u].discard(sommet)

    def retirer_sommets(self, iterable):
        """Efface les sommets de l'itérable donné du graphe, et retire toutes
        les arêtes incidentes à ces sommets."""
        for sommet in iterable:
            self.retirer_sommet(sommet)

    def sommets(self):
        """Renvoie l'ensemble des sommets du graphe."""
        return set(self.dictionnaire.keys())

    def sous_graphe_induit(self, iterable):
        """Renvoie le sous-graphe induit par l'itérable de sommets donné."""
        G = Graphe()
        G.ajouter_sommets(iterable)
        for u, v, p in self.aretes():
            if G.contient_sommet(u) and G.contient_sommet(v):
                G.ajouter_arete(u, v, p)
        return G

    def poids_arete(self, u, v):
        """Renvoi le poid étiquetté sur l'arête (u, v)

        >>> G = Graphe()
        >>> G.ajouter_aretes({(1, 2, 4), (3, 2, 5)})
        >>> G.contient_arete(1, 2)
        True
        >>> print(G.poids_arete(1, 2))
        4
        >>> print(G.poids_arete(2, 1))
        4
        >>> print(G.poids_arete(2, 3))
        5
        """
        if self.contient_arete(u, v):
            for a, p in self.dictionnaire[v]:
                if a == u:
                    return p
        return None

    def voisins(self, sommet):
        """Renvoie l'ensemble des voisins du sommet donné."""
        return self.dictionnaire[sommet]


def heap_father(i):
    if (i - 1) // 2 == 0:
        return 0
    if i % 2 == 0:
        return (i - 2) // 2
    else:
        return (i - 1) // 2


class Tas(object):
    """Implémentation de la structure de données Tas."""

    def __init__(self):
        """Initialisation des structures de données nécessaires.
        """
        self.node = [(-1, -1, -1)]
        self.size = 0

    def heap_exchange(self, i, j):
        self.node[i], self.node[j] = self.node[j], self.node[i]

    def shift_up(self, i):
        child = i // 2
        while child > 0:
            if self.node[i] < self.node[child]:
                self.heap_exchange(i, child)
            i //= 2
            child = i // 2

    def inserer(self, element):
        """Insère un élément dans le tas en préservant la structure.

        >>> heap = Tas()
        >>> heap.inserer(300)
        >>> heap.inserer(1050)
        >>> heap.inserer(1002)
        >>> heap.inserer(293)
        >>> heap.inserer(450)
        >>> heap.is_heap()
        True

        """
        self.node.append(element)
        self.size += 1

        self.shift_up(self.size)

    def shift_down(self, i):
        while (i * 2) <= self.size:
            mc = self.min_child(i)
            if self.node[i] > self.node[mc]:
                self.heap_exchange(i, mc)
            i = mc

    def min_child(self, i):

        if (i * 2) + 1 > self.size:
            return i * 2
        else:
            if self.node[i * 2] < self.node[(i * 2) + 1]:
                return i * 2
            else:
                return (i * 2) + 1

    def extraire_minimum(self):
        """Extrait et renvoie le minimum du tas en préservant sa structure.
        """
        if len(self.node) == 1:
            return None
        root = self.node[1]
        self.node[1] = self.node[self.size]
        *self.node, _ = self.node
        self.size -= 1
        self.shift_down(1)
        return root

    def is_heap(self):
        """Vérifie si le tas est bien un tas (utilisé pour les tests)"""
        if self.size <= 2:
            return True
        if self.size == 0:
            return True
        i = self.size - 1
        while i > 0:
            father = heap_father(i)
            if father == 0:
                return True
            if self.node[father] > self.node[i]:
                return False
            i -= 1
        return True


class UnionFind(object):
    """Implémentation de la structure de données Union-Find."""

    def __init__(self, ensemble):
        """Initialisation des structures de données nécessaires.

        >>> union = UnionFind({1, 2, 3, 4})
        >>> print(union.node)
        {1: 1, 2: 2, 3: 3, 4: 4}


        """
        self.node = dict()
        for el in ensemble:
            self.node[el] = el

    def find(self, element):
        """Renvoie le numéro de la classe à laquelle appartient l'élément.

        >>> union = UnionFind({1, 2, 3, 4})
        >>> union.union(1, 2)
        >>> print(union.node)
        {1: 2, 2: 2, 3: 3, 4: 4}
        >>> union.union(2, 4)
        >>> print(union.node)
        {1: 2, 2: 4, 3: 3, 4: 4}
        >>> union.find(1)
        4
        >>> union.find(2)
        4
        >>> union.find(3)
        3
        >>> union.find(4)
        4
        """
        while self.node[element] != element:
            element = self.node[element]
        return element

    def union(self, premier, second):
        """Fusionne les classes contenant les deux éléments donnés.

        >>> union = UnionFind({1, 2, 3, 4})
        >>> union.union(1, 2)
        >>> print(union.node)
        {1: 2, 2: 2, 3: 3, 4: 4}
        >>> union.union(2, 4)
        >>> print(union.node)
        {1: 2, 2: 4, 3: 3, 4: 4}
        """

        x = self.find(premier)
        y = self.find(second)
        if x != y:
            self.node[x] = y


def stockerAretesValides(G, u, S, hors_arbre):
    for (v, p) in G.voisins(u):
        if hors_arbre[v]:
            S.inserer((p, u, v))


def extraireAreteSure(S: Tas, hors_arbre):
    while S.node:
        (p, u, v) = S.extraire_minimum()
        if hors_arbre[u] != hors_arbre[v]:
            return u, v, p
    return None, None, 10000000


def acpm_prim(G: Graphe, depart):
    """ Renvoi un arbre de poid minimal utilisant l'algorithme de Prim

    >>> G = Graphe()
    >>> G.ajouter_sommets([0, 1, 2, 3, 4, 5, 6])
    >>> G.ajouter_aretes({(0, 1, 5), (1, 4, 2), (0, 3, 4), (3, 4, 3), (4, 6, 7), (3, 6, 4), (5, 6, 12), (3, 5, 7), (2, 3, 9), (2, 5, 5), (0, 2, 7), (0, 4, 2), (3, 5, 7)})
    >>> K = acpm_prim(G, 1)
    >>> K.contient_arete(1, 4) and K.poids_arete(1, 4) == 2
    True
    >>> K.contient_arete(0, 4) and K.poids_arete(0, 4) == 2
    True
    >>> K.contient_arete(0, 2) or K.contient_arete(3, 5)
    True
    >>> K.poids_arete(5, 2) == 5
    True
    """
    arbre = Graphe()
    arbre.ajouter_sommet(depart)
    hors_arbre = [True for _ in G.sommets()]
    hors_arbre[depart] = False
    candidates = Tas()
    stockerAretesValides(G, depart, candidates, hors_arbre)
    while arbre.nombre_aretes() < G.nombre_sommets() - 1:
        (u, v, p) = extraireAreteSure(candidates, hors_arbre)
        if u is None:
            return arbre
        if not hors_arbre[u]:
            u, v = v, u
        arbre.ajouter_arete(u, v, p)
        hors_arbre[u] = False
        stockerAretesValides(G, u, candidates, hors_arbre)
    return arbre


def acpm_kruskal(G: Graphe):
    """ Renvoi une foret de poid minimal utilisant l'algorithme de kruskal

    >>> G = Graphe()
    >>> G.ajouter_sommets([0, 1, 2, 3, 4, 5, 6])
    >>> G.ajouter_aretes({(0, 1, 5), (1, 4, 2), (0, 3, 4), (3, 4, 3), (4, 6, 7), (3, 6, 4), (5, 6, 12), (3, 5, 7), (2, 3, 9), (2, 5, 5), (0, 2, 7), (0, 4, 2), (3, 5, 7)})
    >>> K = acpm_kruskal(G)
    >>> K.contient_arete(1, 4) and K.poids_arete(1, 4) == 2
    True
    >>> K.contient_arete(0, 4) and K.poids_arete(0, 4) == 2
    True
    >>> K.contient_arete(0, 2) or K.contient_arete(3, 5)
    True
    >>> K.poids_arete(5, 2) == 5
    True
    """
    foret = type(G)()
    classes = UnionFind(G.sommets())
    for (u, v, p) in sorted(G.aretes(), key=lambda e: e[2]):
        if classes.find(u) != classes.find(v):
            foret.ajouter_arete(u, v, p)
            classes.union(classes.find(u), classes.find(v))
    return foret


def fcpm_prim(G: Graphe):
    """ Renvoi une foret de poid minimal utilisant l'algorithme de Prim

    >>> G = Graphe()
    >>> G.ajouter_sommets([0, 1, 2, 3, 4, 5, 6])
    >>> G.ajouter_aretes({(0, 1, 5), (1, 4, 2), (0, 3, 4), (3, 4, 3), (4, 6, 7), (3, 6, 4), (5, 6, 12), (3, 5, 7), (2, 3, 9), (2, 5, 5), (0, 2, 7), (0, 4, 2), (3, 5, 7)})
    >>> K = fcpm_prim(G)
    >>> K.contient_arete(1, 4) and K.poids_arete(1, 4) == 2
    True
    >>> K.contient_arete(0, 4) and K.poids_arete(0, 4) == 2
    True
    >>> K.contient_arete(0, 2) or K.contient_arete(3, 5)
    True
    >>> K.poids_arete(5, 2) == 5
    True
    """
    foret = type(G)()
    waiting = list(G.sommets())
    while foret.nombre_sommets() != G.nombre_sommets():
        foret = acpm_prim(G, waiting[0])
        for element in waiting:
            if element in foret.sommets():
                waiting.remove(element)
    return foret


def main():

    import doctest
    doctest.testmod()


if __name__ == "__main__":
    main()
