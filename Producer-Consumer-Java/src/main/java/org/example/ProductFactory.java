package org.example;

public class ProductFactory {
    public static Product createProduct(int type, int quantity, Integer idOfPC) {
        return new Product(type, quantity, idOfPC);
    }
}
