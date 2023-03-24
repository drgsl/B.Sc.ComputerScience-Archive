def is_empty(obj):
    """
    Return if the object is empty or not
        :param obj: Any - A object
    """
    return not (len(obj) > 0)


def get_smaller_path(list_of_paths):
    """
    Return the smaller path of a list of paths (index, smaller_path)
        :param list_of_paths: List - A list of Paths
    """
    smaller = (0, len(list_of_paths[0]))
    for index, path in enumerate(list_of_paths[1:]):
        if len(path) < smaller[1]:
            smaller = (index, len(path))

    smaller = (smaller[0], list_of_paths[smaller[0]])

    return smaller


def pop_smaller_path(list_of_paths):
    """
    Remove the smaller path from a list of paths and return the Path
        :param list_of_paths: List - A list of Paths
    """
    smaller = get_smaller_path(list_of_paths)

    del list_of_paths[smaller[0]]

    return smaller[1]


def get_last_node(path):
    """
    Return the last Node of a Path
        :param path: List - A Path
    """
    return path[-1]


def get_childrens(node, buckets=(3, 4)):
    childrens = []
    bucketA = buckets[0]
    bucketB = buckets[1]

    if node[0] < bucketA:
        childrens.append((bucketA, node[1]))
    if node[1] < bucketB:
        childrens.append((node[0], bucketB))
    if node[0] > 0:
        childrens.append((0, node[1]))
    if node[1] > 0:
        childrens.append((node[0], 0))
    if (node[0] > 0) and (node[1] < bucketB):
        a = node[0]
        b = node[1]
        while (a > 0) and (b < bucketB):
            a -= 1
            b += 1
        childrens.append((a, b))
    if (node[1] > 0) and (node[0] < bucketA):
        a = node[0]
        b = node[1]
        while (a < bucketA) and (b > 0):
            a += 1
            b -= 1
        childrens.append((a, b))

    return childrens


def remove_cycles(path, childrens):
    """
    Remove repeated nodes of a path
        :param path: List - Path to be compared
        :param childrens: List - Path to remove the cycles
    """
    cycles = [node for node in path if node in childrens]
    for cycle in cycles:
        childrens.remove(cycle)

    return childrens


def dont_have_path_end_with_node(list_of_paths, child):
    """
    Check if a List of Paths has any Path that ends with a certain Node
        :param list_of_paths: List - A list of Paths
        :param child: Tuple[2] - A Node to be compared
    """
    pathsWithNode = [path for path in list_of_paths if path[-1] == child]

    return len(pathsWithNode) == 0


def get_smaller_path_end_with_node(list_of_paths, child):
    """
    Return the smaller path that ends with a certain Node
        :param list_of_paths: List - A list of Paths
        :param child: Tuple[2] - A Node to be compared
    """
    pathsWithNode = [path for path in list_of_paths if path[-1] == child]

    smaller = get_smaller_path(pathsWithNode)

    return smaller[1]


def remove_paths_end_with_node(list_of_paths, child):
    """
    Remove all paths from a list of Paths that end with a certain Node
        :param list_of_paths: List - A list of Paths
        :param child: Tuple[2] - A Node to be compared
    """
    indexPathsWithNode = [
        index
        for index, path in enumerate(list_of_paths)
        if path[-1] == child
    ]

    for pathIndex in indexPathsWithNode:
        del list_of_paths[pathIndex]

    return list_of_paths


def a_star(rootNode, destinationNode, pathList=[]):
    """
    Run a A-Star algorithm to solve Water Jug problem
        :param rootNode: Tuple[2] - The initial state of the buckets
        :param destinationNode: Tuple[2] - The desired final state of the buckets
        :param pathList=[]: List - A list of lists. Will store the possible paths
    """
    startPath = [rootNode]
    pathList.append(startPath)

    while not is_empty(pathList):
        caminho = pop_smaller_path(pathList)

        print(caminho)
        if get_last_node(caminho) == destinationNode:
            return caminho

        childrens = get_childrens(get_last_node(caminho))
        childrens = remove_cycles(caminho, childrens)

        heuristic(caminho, childrens, pathList)


def heuristic(path, childrens, pathList):
    """
    A heuristic algorithm especialist for the Water Jug problem
        :param path: List - A path calculated as the smaller path from the list of paths
        :param childrens: List - A new possible Path to reach the destination Node
        :param pathList: List - A list of lists. Will store the possible paths
    """
    for child in childrens:
        pathWithChild = [node for node in path]
        pathWithChild.append(child)

        if dont_have_path_end_with_node(pathList, child):
            pathList.append(pathWithChild)
        else:
            smallerPath = get_smaller_path_end_with_node(pathList, child)
            pathList = remove_paths_end_with_node(pathList, child)

            if len(pathWithChild) < len(smallerPath):
                pathList.append(pathWithChild)
            else:
                pathList.append(smallerPath)


if __name__ == "__main__":
    root = (0, 0)
    destination = (2, 0)

    print("\nSolution: ", a_star(root, destination))