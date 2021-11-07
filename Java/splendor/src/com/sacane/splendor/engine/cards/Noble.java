package com.sacane.splendor.engine.cards;

import java.util.*;


record Noble(String name, ArrayList<GameToken> neededToken, int numberPrestigeToGive) {


    Noble{
        Objects.requireNonNull(name);
        Objects.requireNonNull(neededToken);
        if(numberPrestigeToGive < 0){
            throw new IllegalArgumentException("prestige point can't be negative");
        }
    }


}
