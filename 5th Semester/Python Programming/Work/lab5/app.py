import utils

print("If you want to exit press q and enter")
while True:
    numb = input("Please enter a number:")
    if numb == 'q':
        print("Sorry to see you go!")
        break
    print(f"The next prime number after {numb} is: {utils.process_item(numb)}")