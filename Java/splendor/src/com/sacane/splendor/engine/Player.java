package com.sacane.splendor.engine;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public final class Player {

    private final String userName;
    private int prestigePoint;
    private int bonus;
    private final int age;
    private final List<Cards> reservedCards = new ArrayList<>();

    public Player(String userName, int age){
        Objects.requireNonNull(userName);
        this.userName = userName;
        this.age = age;
        this.bonus = 0;
        this.prestigePoint = 0;

    }

    public int getPrestigePoint() {
        return prestigePoint;
    }
    public void changePrestigePoint(){
        prestigePoint += 1;
    }

    public void addCardsInHand(Cards cards){
        Objects.requireNonNull(cards);
        reservedCards.add(cards);
    }

}
