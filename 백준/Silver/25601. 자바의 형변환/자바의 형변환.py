import sys

read = sys.stdin.readline


class Node:
    def __init__(self, name):
        self.name = name
        self.children = []

    def add_child(self, child):
        self.children.append(child)

    def find_child(self, name):
        if self.name == name:
            return True
        for child in self.children:
            if child.find_child(name):
                return True
        return False

    def __repr__(self):
        return self.name


def main():
    n = int(read())
    nodes = dict()
    for i in range(n - 1):
        a, b = read().split()

        if a in nodes:
            a_node = nodes[a]
        else:
            a_node = Node(a)

        if b in nodes:
            b_node = nodes[b]
        else:
            b_node = Node(b)

        b_node.add_child(a_node)
        nodes[a] = a_node
        nodes[b] = b_node

    a, b = read().split()
    if nodes[a].find_child(b) or nodes[b].find_child(a):
        print(1)
    else:
        print(0)


main()
