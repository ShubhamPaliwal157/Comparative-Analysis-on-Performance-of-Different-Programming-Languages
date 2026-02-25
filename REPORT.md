# Comparative Analysis on Performance of Different Programming Languages

## Introduction

In this analysis report, I deep delve into the performance of various popular programming languages across various metrics. Performance evaluation is critical in selecting the most appropriate programming language for system-level, application-level and high computation tasks. While execution speed and memory consumption are considered the primary metrics for performance evaluation, startup overhead and concurrency efficiency also significantly influence the real-world deployment decisions. I should also mention that while the performance of hardware and languages is important, use of correct and optimal algorithms by the developer or designer is a significant factor as well and should be considered with more weight.

*The languages that this analysis includes are:*

- Python
- Java
- C++
- C
- JavaScript (Node)

There are certain architectural differences in these languages that make their performance vary from each other. Majority of those differences arise from how they are executed. C and C++ are compiled ahead of time and that usually makes their execution really fast and efficient, however this compilation process is heavy. Python (specifically CPython) is primarily interepreted, which means it is first converted into bytecode then executed line by line by an interpreter, this makes the execution slower and clunky but increases the speed of development as there is no heavy compile step. JavaScript, through the V8 engine in Node.js, employs just-in-time compilation, dynamically optimizing frequently executed code paths. Java utilizes a hybrid approach, as it's source code is first compiled into system independent bytecode that is then executed and optimized by the Java Virtual Machine (JVM).

---

## Experimental Setup

### Hardware

- CPU: Intel Core 1215U (1.20 GHz)
- RAM: 8 GB LPDDR4x (7.75 GB usable for Windows, 4GB for Linux)
- Storage Type: NVME PCIe 3.0
- Architecture: 64-bit operating system, x64-based processor

### Operating Systems

- Windows 11 Home 25H2
- Ubuntu (64-bit)

### Compiler & Runtime Versions

- GCC/G++ 6.3.0
- JDK 25.0.2
- Python 3.13.1
- Node v22.14.0

---

## Benchmark Methodology and Design

Each benchmark was executed 30 times. The first 10 runs were discarded to account for warmup and cache stabilization. The remaining 20 runs are analyzed. All measurements were taken using high-resolution timers. Memory usage was measured using process specific peak resident memory. System-wide memory usage was not considered as modern operating systems aggressively cache and pre-allocate unused memory.

### Algorithmic Microbenchmarks

#### Single Digit Sum (Recursive | Iterative | Constant-Math)

> for this program, since the time complexity would be really small and getting a big input to work would be tidius and would certainly add hidden overheads, I have opted to run this program multiple times and calculate the combined execution time.

Python

```python
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
```

Java

```java
public class singledigitsum {

static int tin = 98765432; //not 0 assumed.
static int iterations = 1_000_000;

    public static int sum (int n) {
        if(n<10) return n;
        int res = 0;
        while(n>0) {
            res += n % 10;
            n /= 10;
        }
        return sum(res);
    }
    public static void main(String[] args) {
        int res = 0;
        int temp = tin;
        int its = iterations;

        long start = System.nanoTime();// Start timer

        for(int i = 0; i < its; i++)  {
            //recursive algo
            res += sum(temp); 
        }

        long end = System.nanoTime();// Stop timer

        double executionTimeMs = (end - start) / 1_000_000.0; //convert to ms

        System.out.println("Checksum: " + res);
        System.out.printf("Execution Time Recursive: %.3f ms%n", executionTimeMs);

//--------------------------------------------------------------------

        res = 0;

        start = System.nanoTime();// Start timer
        
        for(int i = 0; i < its; i++)  {
            //iterative algo
            int temptemp = temp;
            while(temptemp >= 10) {
                int total = 0;
                while(temptemp>0) {
                    total += temptemp % 10;
                    temptemp /= 10;
                }
                temptemp = total;
            }
            res += temptemp;
        }

        end = System.nanoTime();// Stop timer

        executionTimeMs = (end - start) / 1_000_000.0; //convert to ms

        System.out.println("Checksum: " + res);
        System.out.printf("Execution Time Iterative: %.3f ms%n", executionTimeMs);

//--------------------------------------------------------------------

        res = 0;

        start = System.nanoTime();// Start timer
        
        for(int i = 0; i < its; i++)  {
            //math
            res += (1 + (temp - 1) % 9); 
        }

        end = System.nanoTime();// Stop timer

        executionTimeMs = (end - start) / 1_000_000.0; //convert to ms

        System.out.println("Checksum: " + res);
        System.out.printf("Execution Time Formula: %.3f ms%n", executionTimeMs);

    }
}
```

C++

```cpp
#include <iostream>
#include <chrono>

const int tin = 98765432;
const int iterations = 1000000;

using namespace std;

int sum(int n) {
    if(n<10) return n;
    int total = 0;
    while(n>0){
        total += n%10;
        n /= 10;
    }
    return sum(total);
}

int main(int argc, char** argv) {
    int temp = tin;
    const int its = iterations;
    int res = 0;

    auto start = std::chrono::high_resolution_clock::now(); //timer start

    for(int i{}; i < its; ++i) {
        //recursive
        res += sum(temp);
    }

    auto end = std::chrono::high_resolution_clock::now(); //timer stop

    auto duration = std::chrono::duration<double, std::milli>(end - start);

    cout << "Checksum: " << res << endl;
    cout << "Execution Time Recursive: " << duration.count() << "ms\n";

    //----------------------------------------------------------------------
    
    res = 0;
    start = std::chrono::high_resolution_clock::now(); //timer start

    for(int i{}; i < its; ++i) {
        //iterative
        int temptemp = temp;
        while(temptemp >= 10) {
            int total = 0;
            while(temptemp > 0) {
                total += temptemp % 10;
                temptemp /= 10;
            }
            temptemp = total;
        }
        res += temptemp;
    }

    end = std::chrono::high_resolution_clock::now(); //timer stop

    duration = std::chrono::duration<double, std::milli>(end - start);

    cout << "Checksum: " << res << endl;
    cout << "Execution Time Iterative: " << duration.count() << "ms\n";

    //------------------------------------------------------------------

    res  = 0;
    start = std::chrono::high_resolution_clock::now(); //timer start

    for(int i{}; i < its; ++i) {
        //formula
        res += (1 + (temp - 1) % 9);
    }

    end = std::chrono::high_resolution_clock::now(); //timer stop

    duration = std::chrono::duration<double, std::milli>(end - start);

    cout << "Checksum: " << res << endl;
    cout << "Execution Time Formula: " << duration.count() << "ms\n";

}
```

C

```c

```

Node

```js

```
