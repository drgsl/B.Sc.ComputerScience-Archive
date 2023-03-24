import statistics

Y = [21, 20, 22, 23, 20, 19, 19, 18, 19, 20]

# Your code here
mean = sum(Y) / len(Y)

print("Celsius mean is: ", mean)
print("Celsius variance is: ", statistics.variance(Y))
print("and ", statistics.variance(Y), " is bigger then 8")

