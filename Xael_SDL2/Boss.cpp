
#include "Boss.h"




Boss::Boss(SDL_Renderer& renderer, std::string& spriteSheet, std::string& bName, char &symbol, float &level, float &health, int &endurance, int &money, float& yPos, float& xPos, int &zPos, int &bonusHeal) : Enemy(renderer, spriteSheet, symbol, bName, level, health, endurance, money, yPos, xPos, zPos, bonusHeal)
{
	bossTexture = TextureManager::LoadTexture(renderer, spriteSheet);
}


Boss::~Boss()
{
	SDL_DestroyTexture(bossTexture);
}


//How does the enemy move
bool Boss::move(Player *player, Zone *zone, GameManager *GM)
{
	int tmpZ = this->getZpos();
	int hitChance = (int)rand() % 100;  //get a random number
	bool doesHit = false;
	 //checking to see if the enemy is next to m_pPlayer.
	//will eventually add range in place of 1...
	if (player->getZpos() == this->getZpos() && GM->checkCollision(player->destRect, this->destRect))
	{//if the enemy is close we print the details
		//because enemy is next to you, he will not move but will attack you
		printEnemyDetails(player, zone);
		if (hitChance < 100) //enemy % chance to hit you...
		{
			doesHit = true;
			this->moveY = 0;
			this->moveX = 0;
		}
		else
			///return something indicating that the enemy isn't attacking.
			doesHit = false;
			hitChance = 0; // enemy doesn't move//attack
	}
	else // if enemy is not next to the Player, it justs moves
	{
		if (hitChance < 87)
		{//no move
			//nochange to movement, so enemy will move around a while.
		}
		else if (hitChance < 89)
		{//left
			this->moveX = -0.1f;
		}
		else if (hitChance < 91)
		{//right
			this->moveX = 0.1f;
		}
		else if (hitChance < 93)
		{//up
			this->moveY = -0.1f;
		}
		else if (hitChance < 95)
		{//down
			this->moveY = 0.1f;
		}
		else
		{
			this->moveY = 0;
			this->moveX = 0;
		}
	}

	//now we check it the enemy is moving in valid spot.
	if (doesHit)
		GM->battle(this);
	else
		this->checkEnemyMove(player, zone, GM, this->moveY, this->moveX);
	return doesHit;
}


//check the move before the move takes place


void Boss::update(Zone* zone)
{
	//width and height of each spot in a sprite.
	srcRect.h = 32;
	srcRect.w = 32;

	//start of sprite animation
	srcRect.x = 0;
	srcRect.y = 0;

	//where sprite will load on map
	destRect.x = (this->getPosX() * 32) - 16;
	destRect.y = (this->getPosY() * 32) - 31;

	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}
void Boss::render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, bossTexture, &srcRect, &destRect);
}