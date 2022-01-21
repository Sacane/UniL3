package com.sacane.splendor.utils;
import com.sacane.splendor.engine.cards.CardsDevelopment;
import com.sacane.splendor.engine.cards.GameToken;
import com.sacane.splendor.engine.cards.Noble;
import com.sacane.splendor.engine.cards.Tiles;

import java.awt.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

class GameObjectFactory {

    //map : key(name of noble) -> value(noble)
    private final Map<String, Tiles> nobleTiles = new HashMap<>();
    private final HashSet<CardsDevelopment> cards = new HashSet<>();


    private static void initColours(){
        HashMap<Color, Integer> catherine = new HashMap<>();
        HashMap<Color, Integer> elisabeth = new HashMap<>();
        HashMap<Color, Integer> Isabella= new HashMap<>();
        HashMap<Color, Integer> Niccolo = new HashMap<>();
        HashMap<Color, Integer> Suleiman = new HashMap<>();
        HashMap<Color, Integer> Anne = new HashMap<>();
        HashMap<Color, Integer> CharlesV = new HashMap<>();
        HashMap<Color, Integer> Francis = new HashMap<>();
        HashMap<Color, Integer> HenriVII = new HashMap<>();
        HashMap<Color, Integer> Stuart = new HashMap<>();


        catherine.put(Color.green, 3);
        catherine.put(Color.blue, 3);
        catherine.put(Color.red, 3);


    }

    void initTiles(){

        //var Catherine = new Noble("Catherine de Medici", );

    }


}
