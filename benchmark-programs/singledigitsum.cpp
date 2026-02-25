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
        //recursive
        res += (1 + (temp - 1) % 9);
    }

    end = std::chrono::high_resolution_clock::now(); //timer stop

    duration = std::chrono::duration<double, std::milli>(end - start);

    cout << "Checksum: " << res << endl;
    cout << "Execution Time Formula: " << duration.count() << "ms\n";

}