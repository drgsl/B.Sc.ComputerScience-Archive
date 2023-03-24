import os
import re
def function_1(text):
    """
        Write a function that extracts the words from a given text as a parameter.
        A word is defined as a sequence of alpha-numeric characters.
    """
    return re.findall("[a-z0-9]+",text,flags=re.IGNORECASE)


def function_2(r,text,x):
    """
    Write a function that receives as a parameter a regex string,
    a text string and a whole number x
    :return: those long-length x substrings that match the regular expression
    """
    return list(filter(lambda el:len(el)==x, re.findall(r,text)))


def function_3(text_chars,list_of_re):
    """
    Write a function that receives as a parameter a string of text characters and a list of regular expressions
    :param text:
    :param list_of_re:
    :return: a list of strings that match on at least one regular expression given as a parameter.
    """
    return [el for el in text_chars if any([re.search(r,el) for r in list_of_re])]


def function_4(path_to_xml,attrs, function):
    """
    Write a function that receives as a parameter the path to an xml document
    and an attrs dictionary.
    For example, if attrs={"class": "url", "name": "url-form", "data-id": "item"}
    the items selected will be those tags whose attributes are class="url" si name="url-form" si data-id="item".
    <class="url" name="url_form">    
    :param path_to_xml:
    :param attrs:
    :return: those elements that have as attributes
    all the keys in the dictionary and values the corresponding values
    """
    result = []
    with open(path_to_xml,"r") as f_d:
        for el in re.findall("<\w+.*?>",f_d.read()):
            if(all([re.search(item[0]+"\s*=\s*\""+item[1] + "\"",el,flags=re.I) for item in attrs.items()])):
                result+=[el]
    return result


def function_5(path_to_xml, attrs):
    result = []
    with open(path_to_xml, "r") as f_d:
        for el in re.findall("<\w+.*?>", f_d.read()):
            if (any([re.search(item[0] + "\s*=\s*\"" + item[1] + "\"", el, flags=re.I) for item in attrs.items()])):
                result += [el]
    return result


def cenzurare(s):
    low_s = s.group(0).lower()
    if not (low_s[0] in "aeiou" and low_s[-1] in "aeiou"):
        return s.group(0)
    return "".join([ch if idx%2 == 0 else '*' for idx,ch in enumerate(s.group(0))])


def function_6(text):
    return re.sub("\w+",cenzurare,text)


def function_7(string):
    return re.match(r"[1256]\d\d(0[1-9]|1[0-2])(0[1-9]|[12]\d|3[01])\d{6}$",string) != None


def function_8(directory,reg):
    result = []
    for root,dirs,files in os.walk(directory):
        for f in files:
            file_name = os.path.join(root,f)
            r = re.search(reg,f)
            if r:
                result += [f]
            try:
                with open(file_name, "r") as f_d:
                        string = f_d.read()
                        if (re.search(reg, string)):
                            if r:
                                result[-1] = "<<" + result[-1]
                            else:
                                result+=[f]
            except:
                pass
    return result