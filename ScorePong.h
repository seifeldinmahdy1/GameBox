//
// Created by Seif Mahdy on 24/05/2023.
//

#ifndef GAMEBOX_SCOREPONG_H
#define GAMEBOX_SCOREPONG_H
#pragma once

class ScorePong {
    int score=0;
public:
    int getScore() {
        return score;
    }
    void addScore() {
        score += 20;
    }
    void makeScoreZero() {
        score = 0;
    }
};


#endif //GAMEBOX_SCOREPONG_H
