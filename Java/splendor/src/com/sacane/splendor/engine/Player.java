package com.sacane.splendor.engine;

import com.sacane.splendor.engine.cards.CardsDevelopment;
import com.sacane.splendor.engine.cards.GameToken;
import com.sacane.splendor.engine.cards.Tiles;


import java.awt.*;
import java.util.*;
import java.util.List;

public final class Player {

    private final String userName;
    private int prestigePoint;
    private final List<Color> bonus = new ArrayList<>();
    private final int age;
    private final List<CardsDevelopment> reservedCards = new ArrayList<>();
    private final List<Tiles> visitedNobles = new ArrayList<>();
    private final Map<GameToken, Integer> tokens = new HashMap<>();

    public Player(String userName, int age){
        if(age < 0){
            throw new IllegalArgumentException("age can't be negative");
        }
        Objects.requireNonNull(userName);
        this.userName = userName;
        this.age = age;
        this.prestigePoint = 0;

    }


    public int getPrestigePoint() {
        return prestigePoint;
    }

    public void receiveNoble(Tiles noble){
        Objects.requireNonNull(noble);
        visitedNobles.add(noble);
    }

    public void addCardsInHand(CardsDevelopment cards){
        Objects.requireNonNull(cards);
        reservedCards.add(cards);
    }

}
