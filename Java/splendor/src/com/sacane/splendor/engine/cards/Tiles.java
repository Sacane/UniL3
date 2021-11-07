package com.sacane.splendor.engine.cards;

import javax.swing.*;
import java.util.Objects;

public class Tiles implements Card{

    private final Noble noble;
    private int x;
    private int y;

    public Tiles(Noble noble, int x, int y){
        Objects.requireNonNull(noble);
        this.noble = noble;
        this.x = x;
        this.y = y;
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
        return false;
    }
}
