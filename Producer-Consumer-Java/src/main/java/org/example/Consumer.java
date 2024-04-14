package org.example;

public class Consumer implements Runnable {
    private final Warehouse warehouse;
    private final Integer id;

    public Consumer(Warehouse warehouse, Integer id) {
        this.warehouse = warehouse;
        this.id = id;
    }

    @Override
    public void run() {
        while (!Thread.currentThread().isInterrupted() && !warehouse.isClosed()) {
            int productType = (int) (Math.random() * warehouse.getproductTypeCount());
            int quantity = (int) (Math.random() * 10) + 1;
            //System.out.println("Consumer " + id + " wants to remove " + quantity + " products of type " + productType + " from warehouse");
            Product product = ProductFactory.createProduct(productType, quantity, id);
            warehouse.removeProduct(product);
            try {
                Thread.sleep((int) (Math.random() * 5000) + 3000);
            } catch (InterruptedException ignored) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
