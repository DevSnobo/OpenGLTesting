//
// Created by snobo on 12/24/18.
//

#include <cstdint>

class Square {
    int height = 18;
    int width = 18;
};

class Snake {

public:
    //TODO change velocity to only run along x and y axis, currently setting xVelocity does not reset yVelocity
    int velocity = 5;
    int xVelocity = 0;
    int yVelocity = 0;

    int tailLength = 0;

    //FIXME currently does not work with Square, find other solution/work with bool array?
    //Square **tail = nullptr;
    bool tail[20] = {false};

public:
    void addToTail() {

        if (tailLength <= 20) {
            //this->tail[tailLength] = new Square;
            this->tail[tailLength] = true;
            this->tailLength++;
            increaseVelocity();
            setVelocity();
        } else {
            increaseVelocity();
            increaseVelocity();
            setVelocity();
        }
    }

    void increaseVelocity() {
        this->velocity++;
    }

    void setVelocity() {
        if (xVelocity < 0)
            this->xVelocity = -velocity;
        else
            this->xVelocity = velocity;

        if (yVelocity < 0)
            this->yVelocity = -velocity;
        else
            this->yVelocity = velocity;
    }

    void setXVelocity(int value) {
        switch (value) {
            case -1:
                this->xVelocity = -velocity;
                break;
            case 1:
                this->xVelocity = velocity;
                break;
            default:
                break;
        }
    }

    void setYVelocity(int value) {
        switch (value) {
            case -1:
                this->yVelocity = -velocity;
                break;
            case 1:
                this->yVelocity = velocity;
                break;
            default:
                break;
        }
    }

    //TODO is a tick method needed? need to find answer
    void tick() {

    }


};
