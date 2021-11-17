package com.sacane.splendor.engine.cards;

import javax.swing.*;
import java.util.Objects;

public class CardsDevelopment implements Card, CardDisplayable {

    private final Development cardDevelopment;
    private int x;
    private int y;
    private boolean isHide;
    public CardsDevelopment(Development cardDevelopment, int x, int y) {
        Objects.requireNonNull(cardDevelopment);
        this.cardDevelopment = cardDevelopment;
        this.x = x;
        this.y = y;
        this.isHide = false;
    }

    @Override
    public int x() {
        return x;
    }

    @Override
    public int y() {
        return y;
    }

    @Override
    public ImageIcon image() {
        return null;
    }

    @Override
    public boolean isCardHide() {
        return isHide;
    }

    @Override
    public ImageIcon imageBack() {
        return null;
    }
}
