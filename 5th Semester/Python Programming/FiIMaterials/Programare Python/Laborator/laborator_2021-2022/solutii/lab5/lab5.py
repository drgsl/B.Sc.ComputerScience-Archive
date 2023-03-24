def function2(*args, **kwargs):

    sum = 0

    for kw in kwargs.keys():
        sum += int(kwargs[kw])

    return sum


anom_function = lambda *args, **kwargs: sum([val for val in kwargs.values()])


def function3(string):

    def function3_with_f(string):

        return [ch for ch in string if ch.lower() in "aeiou"]

    anon_function = lambda string: [ch for ch in string if ch.lower() in "aeiou"]

    first_list = function3_with_f(string)

    second_list = anon_function(string)

    f_filter = lambda string: list(filter(lambda x: x.lower() in "aeiou", string))

    third_list = f_filter(string)

    return first_list, second_list, third_list


def function4(*args, **kwargs):

    return_list = []

    for arg in args:
        if type(arg) == dict:
            if len(arg.keys()) >= 2 and any([True if type(key) == str and len(key) >= 3 else False
                                             for key in arg.keys()]):
                return_list.append(arg)

    for kw in kwargs.keys():
        if type(kwargs[kw]) == dict:
            if len(kwargs[kw].keys()) >= 2 and any([True if type(key) == str and len(key) >= 3 else False
                                             for key in kwargs[kw].keys()]):
                return_list.append(kwargs[kw])

    return return_list


def function5(lst):

    new_lst = []
    for el in lst:
        if type(el) in [int, float, complex]:
            new_lst.append(el)
    return new_lst


def function6(lst1, lst2):

    def function6_1(lst_1, lst_2):
        return_list = []
        for item in list(zip(lst1, lst2)):

            a = item[1][1] - item[0][1]
            b = item[0][0] - item[1][0]
            c = a * item[0][0] + b * item[0][1]
            return_list.append(tuple((a, b, -c)))
        return return_list

    def function6_2(lst_1, lst_2):

        def get_coord(point_a, point_b):

            a = point_b[1] - point_a[1]
            b = point_a[0] - point_b[0]
            c = a * point_a[0] + b * point_a[1]

            return tuple((a, b, -c))

        return list(map(get_coord, lst1, lst2))

    result_zip = function6_1(lst1, lst2)
    result_map = function6_2(lst1, lst2)

    return result_zip, result_map


def function7(integers):

    return list(zip([i for i in integers if i % 2 == 0], [i for i in integers if i % 2 != 0]))


def process(**kwargs):
    def Fibo(n):
        a = 0
        b = 1
        if n <= 0:
            print("Incorrect input")
            x = []
        elif n == 1:
            x = [b]
        else:
            x = [a, b]
            for i in range(2, n):
                c = a + b
                x += [c]
                a = b
                b = c
        return x
    fibo = Fibo(1000)
    if "filters" in kwargs.keys():
        fibo = [f for f in fibo if all([p(f) for p in kwargs["filters"]])]
    if "offset" in kwargs.keys():
        fibo = fibo[kwargs["offset"]:]
    if "limit" in kwargs.keys():
        return fibo[:kwargs["limit"]]
    return fibo

def multiply_by_two(x):
    return x * 2


def add_numbers(a, b):
    return a + b


def print_arguments(function):
    def f(*args,**kwargs):
        print(args,kwargs)
        return function(*args, **kwargs)
    return f

augmented_multiply_by_two = print_arguments(multiply_by_two)
x = augmented_multiply_by_two(10)
print(x)
augmented_add_numbers = print_arguments(add_numbers)
x = augmented_add_numbers(3, 4)
print(x)
#b


def multiply_output(function):
    def f(*args,**kwargs):
        return 2*function(*args,**kwargs)
    return f


def multiply_by_three(x):
    return x * 3


augmented_multiply_by_three = multiply_output(multiply_by_three)
x = augmented_multiply_by_three(10)  # this will return 2 * (10 * 3)
print(x)
#c


def augment_function(function,decorators):
    def f(*args,**kwargs):
        result = function
        for deco in decorators:
            result = deco(result)
        return result(*args, **kwargs)
    return f


decorated_function = augment_function(add_numbers, [print_arguments, multiply_output])
x=decorated_function(3,4)
print(x)


def function9(pairs):
    """
    :param pairs:
    :return:
    """
    return [{"sum": pair[0] + pair[1],
             "prod": pair[0]*pair[1],
             "pow": pair[0]**pair[1]} for pair in pairs]


if __name__ == '__main__':
    print(function2(1, 2, c=3, d=4))
    print(anom_function(1, 2, c=3, d=4))
    print(function3("Programming in Python is fun"))
    print(function4({1: 2, 3: 4, 5: 6}, {'a': 5, 'b': 7, 'c': 'e'}, {2: 3}, [1, 2, 3], {'abc': 4, 'def': 5},
                    3764, dictionar={'ab': 4, 'ac': 'abcde', 'fg': 'abc'}, test={1: 1, 'test': True}))
    print(function5([1  , "2", {"3": "a"}, {4, 5}, 5, 6, 3.0]))
    print(function6([(3,2),(2,6)],[(2,6),(3,2)]))
    print(function7([1, 3, 5, 2, 8, 7, 4, 10, 9, 2]))


    def sum_digits(x):
        return sum(map(int, str(x)))

    print(process(filters=[lambda item: item % 2 == 0,
                           lambda item: item == 2 or 4 <= sum_digits(item) <= 20],
                  limit=2,
                  offset=2))

    print(function9(pairs=[(5, 2), (19, 1), (30, 6), (2, 2)]))
