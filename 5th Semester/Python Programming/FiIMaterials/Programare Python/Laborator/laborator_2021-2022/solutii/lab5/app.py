import utils


def main():
    while True:
        x = input("Enter number: ")
        if x == "q":
            return
        try:
            x=int(x)
        except Exception as e:
            print("Wrong Input")
        else:
            print(utils.process_item(x))


if __name__ == '__main__':
    main()