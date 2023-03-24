import hashlib
import json
import re
import time
import random
import os
import zipfile


def function_1(a, b):
    start = time.time()
    while True:
        seconds = random.randint(a, b)
        time.sleep(seconds)
        print("%.2f" % ((time.time() - start)/60))


def first_prime(n):
    for i in range(2, n):
        if n % i == 0:
            return False
    return True


def second_prime(n):

    any([True if n % factor == 0 else False for factor in ([2] + list(range(3, int(n**0.5) + 1, 2)))])


def problema2(n):
    first_function_start_time = time.time()
    first_prime(n)
    first_function_end_time = time.time()
    second_function_start_time = time.time()
    second_prime(n)
    second_function_end_time = time.time()
    return "first function" if first_function_end_time - first_function_start_time < second_function_end_time - second_function_start_time else "second function"


CHUNK_SIZE = 4096


def compute_md5(fisier):
    hash1 = hashlib.md5()
    f = open(fisier, "rb")
    while True:
        data = f.read(CHUNK_SIZE)
        if len(data) == 0:
            break
        hash1.update(data)
    f.close()
    return hash1.hexdigest()


def function_3(file_1, file_2):
    assert(os.path.isfile(file_1) and os.path.isfile(file_2)),"Invalid parameters"
    hash1 = compute_md5(file_1)
    hash2 = compute_md5(file_2)
    return hash1 == hash2


def compute_sha256(fisier):
    hash1 = hashlib.sha256()
    f = open(fisier, "rb")
    while True:
        data = f.read(CHUNK_SIZE)
        if len(data) == 0:
            break
        hash1.update(data)
    f.close()
    return hash1.hexdigest()


def function_4(director):
    final_json = {}
    for elem in os.listdir(director):
        full_name = os.path.join(director, elem)
        if os.path.isfile(full_name):
            current_json = {"nume_fisier": elem, "md5_fisier": compute_md5(full_name),
                            "sha256_fisier": compute_sha256(full_name), "size_fisier": os.path.getsize(full_name),
                            "data_creare": time.strftime("%Y-%m-%d", time.gmtime(os.stat(full_name).st_ctime)),
                            "full_path": full_name}
            final_json[full_name] = current_json

    with open("info.json", "w") as f:
        json.dump(final_json, f, indent=4)


def function_5(a_path, ext):
    z = zipfile.ZipFile("the.zip", "w", zipfile.ZIP_DEFLATED)
    for (root, dirs, files) in os.walk(a_path):
        for file in files:
            file_name = os.path.join(root, file)
            if os.path.splitext(file)[1] == ext:
                z.write(file_name)
    z.close()


def function_6(x):
    import datetime
    tobj = time.localtime()
    #w = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
    current_year = tobj.tm_year

    for i in range((current_year - x), current_year + 1):
        ans = datetime.date(i, 12, 31)
        print(ans.strftime("%A"))


def function_7():
    # elems=[]
    # while(len(elems)!=6):
    #     el=random.randint(1,49)
    #     if(el not in elems):
    #         elems.append(el)
    # print(elems)
    lista = [i for i in range(1, 50)]
    random.shuffle(lista)
    el = random.sample(lista, 6)
    print(el)


def function_8(a_path, to_hextract):
    try:
        z = zipfile.ZipFile(a_path)
        for i in z.infolist():
            if i.filename == to_hextract:
                f = z.open(i.filename)
                hash = hashlib.md5()
                while True:
                    data = f.read(CHUNK_SIZE)
                    if len(data) == 0:
                        break
                    hash.update(data)
                f.close()
                return hash.hexdigest()
    except:
        return None


def isUTF8(data):
    try:
        decoded = data.decode('UTF-8')
    except UnicodeDecodeError:
        return False
    else:
        for ch in decoded:
            if 0xD800 <= ord(ch) <= 0xDFFF:
                return False
        return True


def function_9(file):
    try:
        with open(file, "rb") as f:
            all_content = f.read().decode("latin-1")
        r = re.compile(r"<CONTENT>(.*?)</CONTENT><SIGNATURE><TYPE>(.*?)</TYPE><HEXDIGEST>(.*?)</HEXDIGEST></SIGNATURE>",flags=re.MULTILINE|re.DOTALL)
        res = r.search(all_content)
        if res:
            assert (res.lastindex == 3),"Invalid parsing"
            content = res.group(1)
            tp = res.group(2).lower()
            hexdigest = res.group(3)
            content = content.encode("latin-1")
            content += b'\xd0\xf3\xde\x9a\x8c\x80\x8d\xf0\x92n7\x94'
            if tp == "md5":
                md5 = hashlib.md5()
                md5.update(content)
                return hexdigest != md5.hexdigest()
            elif tp == "sha256":
                sha256 = hashlib.sha256()
                sha256.update(content)
                return hexdigest != sha256.hexdigest()
            elif tp == "sha512":
                sha512 = hashlib.sha512()
                sha512.update(content)
                return hexdigest != sha512.hexdigest()
            else:
                return True
        else:
            return True
    except:
        return True
