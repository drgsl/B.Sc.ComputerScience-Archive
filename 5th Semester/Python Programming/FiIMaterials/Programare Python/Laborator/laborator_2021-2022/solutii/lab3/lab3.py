from collections.abc import Iterable


def function1(a, b):
    """
    a,b = lists
    (a intersected with b, a reunited with b, a - b, b - a)
    """
    # de returnat set de seturi ?
    return set(a) & set(b), set(a) | set(b), set(a) - set(b), set(b)-set(a)


def function2(s):
    """
     "Ana has apples." given as a parameter the function will return the dictionary: {'a': 3, 's': 2, '.': 1, 'e': 1, 'h': 1, 'l': 1, 'p': 2, ' ': 2, 'A': 1, 'n': 1} .
    :param s: un string
    :return: a dictionary in which the keys are the characters in the character string and the values are the number of occurrences of that character in the given text
    """
    return {i: s.count(i) for i in set(s)}
    #sau - mai ineficient
    # return {ch: string.count(ch) for ch in string}


def return_elements(element):
    if isinstance(element, Iterable) and type(element) != str:
        values = []
        if type(element) == dict:
            for el in element.values():
                values += return_elements(el)
        else:
            for el in element:
                values += return_elements(el)
        return values
    return [element]


def function3(dict1, dict2):
    """
    :param dict1: dictionary
    :param dict2: dictionary
    :return: (dict1-dict2) | (dict2-dict1)
    """
    return list(set(return_elements(dict1)) ^ set(return_elements(dict2)))


def build_xml_element(tag, content, **parameters):
    """
    Function 4
    "<a href=\"http://python.org \ "_class = \" my-link \ "id = \" someid \ "> Hello there </a>"
    :param tag:
    :param content:
    :param parameters:
    :return:
    """
    return "<" + tag + " " + r" ".join([p[0]+" = \"" + p[1] + "\"" if type(p[1]) == str else p[0]+" = " + str(p[1])
                                        for p in parameters.items()])+">"+content+"</"+tag+">"


def validate_dict(rules, dictionary):
    """
    Function 5
    s={("key1", "", "inside", ""), ("key2", "start", "middle", "winter")}
    and
    d= {"key1": "come inside, it's too cold out", "key3": "this is not valid"} => False
    :param rules: set of tuples
    :param dictionary: dictionary
    :return:
    """
    rules_dict = {rule[0]: [rule[1], rule[2], rule[3]] for rule in rules}
    return all([key in rules and value.startswith(rules_dict[key][1]) and
                rules_dict[key][2] in value and value.endswith(rules_dict[key][3])
                for key, value in dictionary.items()])


def function6(lista):
    """
    a is the number of unique elements in the list, and b representing the number of duplicate elements in the list
    :param lista
    :return: (a,b)
    """
    # return len(set(lista)),len([el for el in set(lista) if lista.count(el)>1])
    #daca elementele sunt de maxim 2 ori in lista
    return len(set(lista)), len(lista) - len(set(lista))


def function7(*sets):
    """
    a dictionary with the following operations from all sets two by two: reunion, intersection, a-b, b-a.
    The key will have the following form: "a op b", where a and b are two sets, and op is the applied operator: |, &, -.
    :param sets:
    :return:
    """
    result = {}
    for idx1 in range(0, len(sets) - 1):
        for idx2 in range(idx1 + 1, len(sets)):
            result.update({(str(sets[idx1]) + " | " + str(sets[idx2])): (sets[idx1] | sets[idx2]),
                           (str(sets[idx1]) + " & " + str(sets[idx2])): (sets[idx1] & sets[idx2]),
                           (str(sets[idx1]) + " - " + str(sets[idx2])): (sets[idx1] - sets[idx2]),
                           (str(sets[idx2]) + " - " + str(sets[idx1])): (sets[idx2] - sets[idx1])})
    return result


def loop(mapping):
    """
    Function8
    :param mapping: dictionary
    :return: list
    """
    to_return = list()
    value = mapping['start']
    while value not in to_return:
        to_return.append(value)
        value = mapping[value]
    return to_return


def function9(*arguments, **keywords):
    """
     the number of positional arguments whose values can
     be found among keyword arguments values.
    :param elements:
    :param keywords:
    :return:
    """
    return len([el for el in arguments if el in keywords.values()])