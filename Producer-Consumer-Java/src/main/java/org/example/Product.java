package org.example;

public class Product {
    private int type;
    private int quantity;

    //id of producer or consumer
    private Integer idOfPC;

    public Product(int type, int quantity, Integer idOfPC) {
        this.type = type;
        this.quantity = quantity;
        this.idOfPC = idOfPC;
    }

    public int getType() {
        return type;
    }

    public int getQuantity() {
        return quantity;
    }

    public Integer getIdOfPC() {
        return idOfPC;
    }
}
