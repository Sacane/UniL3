def heap_child(i):
    return (i * 2) + 1


def heap_father(i):
    if i % 2 == 0:
        return (i - 2) // 2
    else:
        return (i - 1) // 2


class Tas(object):
    """Implémentation de la structure de données Tas."""

    def __init__(self):
        """Initialisation des structures de données nécessaires."""
        self.node = []
        self.size = 0

    def heap_exchange(self, i, j):
        self.node[i], self.node[j] = self.node[j], self.node[i]

    def shift_up(self, i):
        print('stuck here')
        if i == 0:
            return

        father = heap_father(i)
        if father <= 0:
            print('return')
            return
        while self.node[father] > self.node[i]:

            self.heap_exchange(father, i)
            i = father
            if father == 0:
                return
            else:
                father = heap_father(father)

    def shift_down(self, i):
        if self.size <= 1:
            return
        i_max = self.size - 1
        while (i * 2) + 1 <= i_max or (i * 2) + 2 <= i_max:
            i_next = heap_child(i)
            if (i * 2) + 2 <= i_max and self.node[i_next] > self.node[(i * 2) + 2]:
                i_next = (i * 2) + 2
            if self.node[i] > self.node[i_next]:
                self.heap_exchange(i, i_next)
                i = i_next
            else:
                return

    def inserer(self, element):
        """Insère un élément dans le tas en préservant la structure."""
        self.node.append(element)
        self.size += 1
        self.shift_up(self.size - 1)

    def extraire_minimum(self):
        """Extrait et renvoie le minimum du tas en préservant sa structure."""
        if not self.node:
            return None
        minimum = self.node[0]
        self.node[0] = self.node[self.size - 1]
        self.size -= 1
        self.shift_down(0)
        return minimum

    def is_heap(self):
        if self.size == 0:
            return True
        i = self.size - 1
        print(i)
        while i > 0:

            father = heap_father(i)
            if self.node[0] < father:
                return False
            if self.node[father] > self.node[i]:
                return False
            i -= 1
        return True


class UnionFind(object):
    """Implémentation de la structure de données Union-Find."""

    def __init__(self, ensemble):
        """Initialisation des structures de données nécessaires."""

        self.node = dict()
        for el in ensemble:
            self.node[el] = el

    def find(self, element):
        """Renvoie le numéro de la classe à laquelle appartient l'élément."""
        while self.node[element] != element:
            element = self.node[element]
        return element

    def union(self, premier, second):
        """Fusionne les classes contenant les deux éléments donnés."""
        x = self.find(premier)
        y = self.find(second)
        if x != y:
            self.node[x] = y


def main():
    import doctest

    # union = UnionFind({1, 2, 3, 4})
    # print(union.node)
    # union.union(1, 2)
    # print(union.node)
    # union.union(2, 4)
    # print(union.node)
    # print(union.find(1))
    # print(union.find(2))
    # print(union.find(4))
    # print(union.find(3))
    heap = Tas()
    test_values = [300, 2050, 1002, 293, 450, 1080, 850, 1300, 1000]
    heap.inserer(300)
    if heap.node[0] != 300:
        print('Value error')
    else:
        print('Treatment on continue...')

    heap.inserer(2050)
    if not heap.is_heap():
        print('Error, not a heap')
    else:
        print('continue...')


if __name__ == "__main__":
    main()
