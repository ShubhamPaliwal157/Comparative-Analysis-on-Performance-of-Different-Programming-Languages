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
