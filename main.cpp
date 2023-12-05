#include <iostream>
#include <raylib.h>

using namespace std; 

int player_score = 0;
int ai_score = 0;
class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;
	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}
	void Update() {
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}
		if (x + radius >= GetScreenWidth()) {
			player_score++;
			ResetBall();
		}
		if (x - radius <= 0()) {
			ai_score++;
			ResetBall();
		}
	} 
	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[2] = { -1, 1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
}; 
   
class Paddle {
protected:
	void LimitMov() {
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
	}

public:
	float x, y;
	float width, height;
	int speed_y;

	void draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}

	void Update() {
		if (IsKeyDown(KEY_UP)|| (IsKeyDown(KEY_W))) {
			y -= speed_y;
		}
		if (IsKeyDown(KEY_DOWN)|| (IsKeyDown(KEY_S))) {
			y += speed_y;
		}
		LimitMov();
	}
	
};

class AiPaddle : public Paddle {
public: 
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) {
			y -= speed_y;
		}
		if (y - height / 2 <= ball_y) {
			y += speed_y; 
		}
		LimitMov(); 
	}
};


Ball ball; 
Paddle player;
AiPaddle ai; 

int main()
{
	//SCREEN 
	const int ScY = 720;
	const int ScX = 1200; 
	InitWindow(ScX, ScY, "Pong"); 
	SetTargetFPS(240);
	//BALL
	ball.x = ScX / 2;
	ball.y = ScY / 2;
	ball.radius = 20; 
	ball.speed_x = 2;
	ball.speed_y = 2;

	//PLAYER
	player.width = 25;
	player.height = 120; 
	player.x = 25;
	player.y = ScY / 2 - player.height / 2;
	player.speed_y = 2;

	//AI
	ai.width = 25; 
	ai.height = 120; 
	ai.x = ScX - ai.width - 25;
	ai.y = ScY / 2 - ai.height / 2;
	ai.speed_y = 2;  

	//GAMELOOP
	while (WindowShouldClose() == false) {
		BeginDrawing();
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x,player.y, player.width,player.height })) {
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ ai.x,ai.y, ai.width,ai.height })) {
			ball.speed_x *= -1;
		}
		ball.Update();
		ClearBackground(BLACK);
		DrawLine(ScX / 2, 0, ScX / 2, 720, WHITE);  
		ball.Draw(); 
		ai.draw();
		ai.Update(ball.y);
		player.draw();
		player.Update();
		DrawText(TextFormat("%i", player_score), ScX / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", ai_score), 3 * ScX / 4 - 20, 20, 80, WHITE);
		EndDrawing();

	}



	CloseWindow();
}

