package com.sacane.splendor.engine.cards;
import java.awt.*;

record Development(int levelCards, Color gemColor, int whiteCost, int blueCost, int greenCost, int redCost, int blackCost) {

    Development{
        if(levelCards < 0 || levelCards > 3){
            throw new IllegalArgumentException("levelCards can't be under 0 or above 3");
        }
    }

}
