package org.example;
import java.util.*;
import java.util.concurrent.*;

public class JavaExercise2 {


    private static class CachingPrimeChecker {
        // TODO: dokończ implementację cachu
        // (ustal typ przechowywanej wartości oraz rodzaj wykorzystywanej mapy)
        private final Map<Long, Boolean> cache = new ConcurrentHashMap<>();


        public boolean isPrime(final long x) {
            // TODO: dokończ implementację sprawdzania czy liczba x jest liczbą pierwszą
            // Należy zagwarantować, że dla każdej unikalnej liczby obliczenia zostaną wykonane tylko 1 raz
            // Ponowne (w tym równoległe) sprawdzenie czy dana liczba jest liczbą pierwszą powinny wykorzystać cache

            return cache.computeIfAbsent(x, this::computeIfIsPrime);
        }

        // Funkcja sprawdzająca czy dana liczba jest liczbą pierwszą, należy jej użyć do wykonywania obliczeń
        // Nie należy jej w żaden sposób modyfikować!
        private boolean computeIfIsPrime(long x) {
            final String currentThreadName = Thread.currentThread().getName();
            System.out.printf("\t[%s] Running computation for: %d%n", currentThreadName, x);
            try {
                // symulacja długich obliczeń
                Thread.sleep(TimeUnit.SECONDS.toMillis(10));
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            if (x < 2) {
                return false;
            }
            for (long i = 2; i * i <= x; i++) {
                if (x % i == 0) {
                    return false;
                }
            }
            return true;
        }
    }

    public static void main(String[] args) {
        // TODO: zaimplementuj pętlę główną programu

        int n = 4;
        ExecutorService calculationPool = Executors.newFixedThreadPool(n);
        CachingPrimeChecker cachingPrimeChecker = new CachingPrimeChecker();

        Scanner sc = new Scanner(System.in);
        String input = "";
        boolean running = true;
        while (true) {
            List<Long> toCompute = new ArrayList<>();
            System.out.println("Enter 4 numbers, q to quit");
            for (int i = 0; i<n;i++) {
                input = sc.nextLine();
                if (input.equals("q")) {
                    running = false;
                    break;
                }
                try {
                    Long in = Long.parseLong(input);
                    toCompute.add(in);
                } catch (NumberFormatException e) {
                    System.out.println("Invalid input");
                }
            }

            if (!running) {
                break;
            }

            CountDownLatch mainBarrier = new CountDownLatch(toCompute.size());
            CyclicBarrier threadBarrier = new CyclicBarrier(toCompute.size());
            toCompute.forEach(x -> calculationPool.submit(() -> {
                try {
                    threadBarrier.await();
                } catch (InterruptedException | BrokenBarrierException ignored) {
                }

                boolean result = cachingPrimeChecker.isPrime(x);
                System.out.println(x + " is " + (result ? "prime" : "not prime"));
                mainBarrier.countDown();

            }));
            try {
                mainBarrier.await();
            } catch (InterruptedException ignored) {
            }
        }

        calculationPool.shutdown();
        sc.close();
    }
}
