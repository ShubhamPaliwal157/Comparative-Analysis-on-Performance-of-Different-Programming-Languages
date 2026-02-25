import time

tin = 98765432 #not 0 assumed
iterations = 1_000_000

# Recursive
def SingleDigitSum (n) :
    if n < 10 : return n
    sum = 0
    while n > 0 :
        sum += n%10
        n //= 10
    return SingleDigitSum(sum)

res = 0

start = time.perf_counter() #start counter

for _ in range(iterations) :
    res = SingleDigitSum(tin)

end = time.perf_counter() #end counter

execution_time_ms = (end-start) * 1000
print(f"Execution Time Recursive: {execution_time_ms:.3f} ms")

#loop

start = time.perf_counter() #start counter

for _ in range(iterations) :
    temp = tin
    while temp > 10 :
        total = 0
        while temp > 0:
            total += temp % 10
            temp //= total
        temp = total
    res = temp

end = time.perf_counter() #end counter

execution_time_ms = (end-start) * 1000
print(f"Execution Time Iterative: {execution_time_ms:.3f} ms")

# Math o(1)-looped

start = time.perf_counter() #start counter

for _ in range(iterations) :
    res = 1 + (tin-1) % 9

end = time.perf_counter() #end counter

execution_time_ms = (end-start) * 1000
print(f"Execution Time Formula: {execution_time_ms:.3f} ms")
