#pragma once


enum GameModeType {

	Server,Client

};

class GameMode
{
public:

	void SetGameType(GameModeType type);
	virtual void BeginGame();
	virtual void UpdateGame();


private:

	GameModeType GameType;



};


