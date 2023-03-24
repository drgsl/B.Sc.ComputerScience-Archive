def process_item(x):
    x = int(x)
    while True:
        if x > 0:
            x += 1
            for i in range(2, (x//2)+1):
                if x % i == 0:
                    break
            else:
                return x
        else:
            x += 1