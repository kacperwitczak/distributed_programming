package org.example;

import org.apache.commons.lang3.tuple.Pair;

import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class Warehouse {
    private final int productTypeCount;
    private Map<Integer, Pair<Integer, Integer>> products;

    private volatile AtomicBoolean isClosed = new AtomicBoolean(false);

    public Warehouse(int productTypeCount) {
        this.productTypeCount = productTypeCount;
        this.products = new HashMap<>();

        for (int i = 0; i < productTypeCount; i++) {
            int maxQuantity = (int) (Math.random() * 100) + 1; //maxQuantity of product type in warehouse
            this.products.put(i, Pair.of(maxQuantity, 0)); //set quantity of each product type to 0
        }
    }

    //if there is space in warehouse, add product
    public synchronized void addProduct(Product product) {
        int productsToAdd = product.getQuantity();
        if (products.get(product.getType()).getRight() + productsToAdd <= products.get(product.getType()).getLeft()) {
            products.put(product.getType(), Pair.of(products.get(product.getType()).getLeft(), products.get(product.getType()).getRight() + productsToAdd));
            System.out.println("Producer " + product.getIdOfPC() + " added " + productsToAdd + " products of type " + product.getType() + " to warehouse");
            notifyAll();
        } else {
            System.out.println("Producer " + product.getIdOfPC() + " wanted to add " + productsToAdd + " products of type " + product.getType() + " to warehouse, but there is no space");
        }
    }
    
    public synchronized void removeProduct(Product product) {
        int productsToRemove = product.getQuantity();
        while (productsToRemove > 0 && !isClosed.get()) {
            while (products.get(product.getType()).getRight() <= 0) {
                try {
                    wait();
                } catch (InterruptedException ignored) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
            int productsToRemoveNow = Math.min(productsToRemove, products.get(product.getType()).getRight());
            products.put(product.getType(), Pair.of(products.get(product.getType()).getLeft(), products.get(product.getType()).getRight() - productsToRemoveNow));
            productsToRemove -= productsToRemoveNow;
            System.out.println("Consumer " + product.getIdOfPC() + " removed " + productsToRemoveNow + " products of type " + product.getType() + " from warehouse");
        }
    }
    
    public int getproductTypeCount() {
        return productTypeCount;
    }

    public synchronized void close() {
        isClosed.set(true);
        notifyAll();
    }

    public boolean isClosed() {
        return isClosed.get();
    }
}
