public static int closest_fibonacci_sum (int[] arr) {
        int sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }

        int fib1 = 0;
        int fib2 = 1;
        int fib3 = 1;
        while (fib3 < sum) {
            fib1 = fib2;
            fib2 = fib3;
            fib3 = fib1 + fib2;
        }

        int diff1 = fib3 - sum;
        int diff2 = sum - fib2;

        if (diff1 < diff2) {
            return diff1;
        } 
        else {
            return diff2;
        }
    }
