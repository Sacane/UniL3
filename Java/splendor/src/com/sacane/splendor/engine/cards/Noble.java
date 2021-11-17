package com.sacane.splendor.engine.cards;

import java.awt.*;
import java.util.*;


public record Noble(String name, HashMap<Color, Integer> neededColor, int numberPrestigeToGive) {


    public Noble{
        Objects.requireNonNull(name);
        Objects.requireNonNull(neededColor);

        if(numberPrestigeToGive < 0){
            throw new IllegalArgumentException("prestige point can't be negative");
        }
    }


}
