def function5(a):
    m = len(a)
    n = len(a[0])
    k = 0
    l = 0

    while (k < m and l < n):

        for i in range(l, n):
            print(a[k][i], end="")

        k += 1

        for i in range(k, m):
            print(a[i][n - 1], end="")

        n -= 1

        if (k < m):

            for i in range(n - 1, (l - 1), -1):
                print(a[m - 1][i], end="")

            m -= 1

        if (l < n):
            for i in range(m - 1, k - 1, -1):
                print(a[i][l], end="")

            l += 1


def function6(number):

    return str(number) == str(number)[::-1]


def function7(text):

    number_text = ""
    for i in range(len(text)):
        if text[i].isdigit():
            while i < len(text) and text[i].isdigit():
                number_text += text[i]
                i += 1
            break
    if not number_text:
        return "there are no numbers"
    return int(number_text)


def function8(number):

    # """iterative"""
    # bin_number = ""
    # while (number != 0):
    #     bin_number = str(number % 2) + bin_number
    #     number = number // 2
    # return bin_number.count("1")

    # """recursive"""
    # if number == 0:
    #     return ''
    # else:
    #     return function8(number//2) + str(number % 2)
    # """one liner"""
    # return bin(number).count("1")

    count = 0
    while (number):
        number = number & (number - 1)
        count += 1
    return count


def function9(text):
    # parcurse = "" #optional
    # max = 0
    # letter = ""
    # text = text.lower()
    # for el in text:
    #     if el >= "a" and el <= "z":
    #         count = text.count(el)
    #         if count > max:
    #             max = count
    #             letter = el
    # return letter

    return max([(el, text.count(el)) for el in text.lower() if el.isalpha()] if text else [("", 0)], key=lambda t: t[1])


def function10(text):

    count = 0
    words = text.split(" ")
    for word in words:
        if word:
            count += 1
    return count
    # return len([item for item in text.split(" ") if item])


x = ["firs", "n_lt", "oba_", "htyp"]

function5(x)
# print(function7("An apple is 123 USD"))
# print(function7("abc123abc"))
# print(function7("ala ceva"))
# print(function8(24).count("1"))
# print(function8(24))
print(function9("anaaa"))
# print(function10("I have Python exam"))

