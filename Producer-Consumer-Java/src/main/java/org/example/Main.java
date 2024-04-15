package org.example;

import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        int n = 5;
        Warehouse warehouse = new Warehouse(n);
        ExecutorService producerPool = Executors.newFixedThreadPool(n);
        ExecutorService consumerPool = Executors.newFixedThreadPool(n);

        int nextId = 0;
        for (int i = 0; i < n; i++) {
            producerPool.submit(new Producer(warehouse, nextId++));
            consumerPool.submit(new Consumer(warehouse, nextId++));
        }

        String input = "";
        Scanner sc = new Scanner(System.in);

        do {
            input = sc.nextLine();
        } while (!input.isEmpty());

        warehouse.close();

        producerPool.shutdownNow();
        consumerPool.shutdownNow();
    }
}