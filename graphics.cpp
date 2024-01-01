#include <iostream>
#include <graphics.h>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <stdio.h> // For input in Arrows Key
using namespace std; 

// Function to read the high score from a file
int readHighScore()
{
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        int highscore;
        file >> highscore;
        file.close();
        return highscore;
    }
    return 0;
}

// Function to write the high score to a file
void writeHighScore(int score)
{
    std::ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << score;
        file.close();
    }
}

int main()

{
    // for graph variables
    int gd = DETECT, gm, key_dir, foodX, foodY, snakeX[200], snakeY[200];  //gd is graph driver, graph mode is gm
    initgraph(&gd, &gm, (char *)"");
    initgraph(&gd, &gm, (char *)"");
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const int SIZE = 20;
    bool playAgain = true;

    char welcome1[] = "WELCOME TO SNAKE GAME...!!!";
    char welcome2[] = "PRESS SPACE TO START.";
    char welcome3[] = "Press 'Right Key' for instructions.";

    char instructions1[] = "Press 'UP Arrow' to Move the Snake Upwards.";
    char instructions2[] = "Press 'DOWN Arrow' to Move the Snake Downwards.";
    char instructions3[] = "Press 'Right Arrow' to Move the Snake towards Right.";
    char instructions4[] = "Press 'Left Arrow' to Move the Snake towards Left.";
    char instructions5[] = "Press 'LEFT ARROW' to Go Back to Main Menu.";

    char score[50] = "";   // writes SCORE
    int score1;            // write integer score

    char highscore[50] = "";
    int highscore1 = readHighScore();  // reads highscore by file handling

main_menu:
    closegraph();
    initwindow(630, 470, "Snake Game");  // width x height , window name: Snake Game
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, 630, 470); // BLACK BACKGROUND
    setfillstyle(SOLID_FILL, RED);
    bar(0, 0, 630, 10);  // RED BOUNDARY
    bar(0, 0, 10, 470);
    bar(0, 470, 630, 460);
    bar(620, 10, 630, 470);
    setfillstyle(SOLID_FILL, WHITE);  // WHITE TEXT
    outtextxy(170, 190, welcome1);
    outtextxy(170, 210, welcome2);
    outtextxy(170, 230, welcome3);

    getch();
    if (GetAsyncKeyState(VK_SPACE))  // DIRECTLY STARTS THE GAME
    {

        goto playagain;   // skips instructions
    }
    getch();
    if (GetAsyncKeyState(VK_RIGHT))   // INSTRUCTIONS
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, 0, 630, 470); // BLACK BACKGROUND
        setfillstyle(SOLID_FILL, RED);
        bar(0, 0, 630, 10);  // RED BOUNDARY
        bar(0, 0, 10, 470);
        bar(0, 470, 630, 460);
        bar(620, 10, 630, 470);
        setfillstyle(SOLID_FILL, WHITE);  // WRITES TEXT
        outtextxy(150, 180, instructions1);
        outtextxy(150, 200, instructions2);
        outtextxy(150, 220, instructions3);
        outtextxy(150, 240, instructions4);
        outtextxy(20, 400, instructions5);
        getch();
        if (GetAsyncKeyState(VK_LEFT))
        {
            goto main_menu;
        }
    }

    // Initialization
playagain:
    while (playAgain)
    {

        int score2 = 0;
        int delayTime = 100;
        int food = 0;     // to check how many foods eaten
        int boody = 500;  // body length can be anything
        int p_dir = 1;    // previous direction of snake pressed
        int length = 1;   // length of snake
        bool game = true; // game ongoing

        for (int i = 0; i < 200; i++)
        {
            snakeX[i] = 0;
            snakeY[i] = 0;
        }

        snakeX[0] = 200, snakeY[0] = 200;
        foodX = 200, foodY = 200;
        key_dir = 1;

        // Drawing Game Panel

        while (game)
        {

            score1 = food - 1;
            sprintf(score, "SCORE : %d ", score1); // PRINTS SCORE ON TOP

            setfillstyle(SOLID_FILL, LIGHTGRAY);
            bar(0, 0, 630, 470); // BACKGROUND
            setfillstyle(SOLID_FILL, BLUE);
            bar(0, 0, 630, 10); // BOUNDARY
            bar(0, 0, 10, 470);
            bar(0, 470, 630, 460);
            bar(620, 10, 630, 470);

            setcolor(CYAN);
            outtextxy(10, 0, score);

            sprintf(highscore, "HIGHSCORE : %d ", highscore1);
            setcolor(CYAN);
            outtextxy(100, 0, highscore);

            setfillstyle(SOLID_FILL, RED);

            if (snakeX[0] == foodX && snakeY[0] == foodY)
            {
                length = length + 1;
                food = food + 1;
                delayTime = delayTime - 2; // Snake Speed Gets faster as loop time decreases

                bar(foodX, foodY, foodX + 10, foodY+10);

                do
                {
                    foodX = (10 + rand() % 600);
                    foodY = (10 + rand() % 450);
                } while (getpixel(foodX, foodY) != 0 && foodX > 10 && foodY > 10);

                foodX = foodX / 10;
                foodX = foodX * 10;
                foodY = foodY / 10;
                foodY = foodY * 10;

                if (foodX == 10)
                {
                    foodX = rand() % 10 + 5;
                    foodX = foodX * 10;
                }
                else if (foodY == 10)
                {
                    foodY = rand() % 10 + 5;
                    foodY = foodY * 10;
                }
            }

            bar(foodX, foodY, foodX + 10, foodY+10);

            setfillstyle(SOLID_FILL, MAGENTA);

            if (GetAsyncKeyState(VK_RIGHT))
            {
                key_dir = 1;
            }

            else if (GetAsyncKeyState(VK_LEFT))
            {
                key_dir = 2;
            }

            else if (GetAsyncKeyState(VK_UP))
            {
                key_dir = 3;
            }

            else if (GetAsyncKeyState(VK_DOWN))
            {
                key_dir = 4;
            }
            else
            {
                key_dir = 0;
            }

            switch (key_dir)
            {
            case 0:
            {
                if (p_dir == 1)
                {
                    snakeX[0] = snakeX[0] + 10;
                }
                else if (p_dir == 2)
                {
                    snakeX[0] = snakeX[0] - 10;
                }
                else if (p_dir == 3)
                {
                    snakeY[0] = snakeY[0] - 10;
                }
                else if (p_dir == 4)
                {
                    snakeY[0] = snakeY[0] + 10;
                }
                else
                {
                    key_dir = 0;
                }
                break;
            }

            case 1:
            {
                snakeX[0] = snakeX[0] + 10;
                p_dir = 1;
                break;
            }
            case 2:
            {
                snakeX[0] = snakeX[0] - 10;
                p_dir = 2;
                break;
            }
            case 3:
            {
                snakeY[0] = snakeY[0] - 10;
                p_dir = 3;
                break;
            }
            case 4:
            {
                snakeY[0] = snakeY[0] + 10;
                p_dir = 4;
                break;
            }
            }

            // displaying snake
            for (int i = 0; i < length; i++)
            {
                bar(snakeX[i], snakeY[i], snakeX[i] + 10, snakeY[i] + 10);
            }

            // body of snake

            for (int i = 199; i > 0; i--)  // FOR BODY OF SNAKE TO FOLLOW ITS HEAD
            {
                snakeX[i] = snakeX[i - 1];
                snakeY[i] = snakeY[i - 1];
            }
            // Bumping into body
            for (int i = 2; i < length; i++)
            {
                if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
                {
                    boody = i; // KIS JAGAH BUMP HUA HA
                    break;
                }
            }
            delay(delayTime);

            if (snakeX[0] >= 615 || snakeX[0] <= 5 || snakeY[0] <= 5 || snakeY[0] >= 455)
            {
                cout << "Snake bumped into wall!!" << endl;
                game = false;
            }

            if (snakeX[0] >= snakeX[boody] && snakeY[0] >= snakeY[boody])
            {
                cout << "Snake bumped itself!!" << endl;
                game = false;
            }
        }

        cleardevice();
        score2 = score1;
        // Draw score
        char scoreStr[10];
        sprintf(scoreStr, "Score: %d", score2);
        outtextxy(10, 10, scoreStr);

        // Display the window
        delay(100);

        // Game over logic
        // ...

        char str2[20];
        strcpy(str2, "Game Over !!");

        char str1[50];
        strcpy(str1, "Press Space to play again");

        if (score1 > highscore1)
        {
            highscore1 = score1;
            writeHighScore(highscore1);
        }

        // Read the high score from the file
        highscore1 = readHighScore();
        cout << "Highest score :)"
             << "  " << highscore1 << endl;

        outtextxy((WIDTH / 2 - 200) + 20, HEIGHT / 4, str2);
        outtextxy((WIDTH / 2 - 200) + 20, HEIGHT / 4 + 20, scoreStr);
        outtextxy((WIDTH / 2 - 250) + 23, HEIGHT / 4 + 40, str1);

        while (true)
        {
            if (kbhit())
            {
                char key = getch();
                if (key == ' ')
                {
                    score2 = 0;
                    playAgain = true;
                    break;
                }
            }
        }
    }

    closegraph();

    getch();

    return 0;
}