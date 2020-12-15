#pragma once

enum GAME_STATE
{
	MAINMENU,
	GAME,
	SETTINGS
};

class Game
{
public:
	Game();
	~Game();

	void Init();

	//setters & getters
	void SetGameState(GAME_STATE gS) { gameState = gS; }
	GAME_STATE GetGameState() { return gameState; }

private:
	GAME_STATE gameState;
};

