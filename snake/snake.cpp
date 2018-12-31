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

/*
void processSnakeInput(GLFWwindow *window, Snake *snake) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        snake->setXVelocity(-1);
        std::cout << "left" << std::endl;
        std::cout << snake->xVelocity << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        snake->setXVelocity(1);
        std::cout << "right" << std::endl;
        std::cout << snake->xVelocity << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        snake->setYVelocity(-1);
        std::cout << "up" << std::endl;
        std::cout << snake->yVelocity << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        snake->setYVelocity(1);
        std::cout << "down" << std::endl;
        std::cout << snake->yVelocity << std::endl;
    }


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        std::cout << "before adding + 1" << std::endl;
        snake->addToTail();
        std::cout << "adding + 1" << std::endl;
        std::cout << "size is now: " << snake->tailLength << std::endl;
    }
}


        //TODO testing input capturing for small snake game
        //processSnakeInput(window, snake);


 */
