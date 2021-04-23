/*********************
* @author Jake Rhoads, Branden Thome
* @class CS 3150
* @project Dungeon Crawler Competition
* @date 10/26/2020
*******/

#ifndef ENTITY_H
#define ENTITY_H


enum class Status { dead, alive };

class Entity
{
	private:

		int strength;
		int health;
		int maxHealth;
		int xp;
		int xpToLevel;
		int level;
		std::string name;

	public:

		Entity(std::string name = "Billy", int = 10, int = 10);
		Status isAlive;
		std::string levelUp();
		std::string battle( Entity& );

		//getters and setters
		int getHealth();
		int getStrength();
		int getMaxHealth();
		int getXp();
		int getXpToLevel();
		int getLevel();
		bool heroStatus();
		std::string getName();

		void setHealth(int);
		void setStrength(int);
		void setName(std::string);
		void setXp(int);
		void setXpToLevel(int);
		void setLevel(int);


};

#endif