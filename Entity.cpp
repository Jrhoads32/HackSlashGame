/*********************
* @author Jake Rhoads, Branden Thome
* @class CS 3150
* @project Dungeon Crawler Competition
* @date 10/26/2020
*******/

#include <iostream>
#include <string>
#include "Entity.h"

using namespace std;


Entity::Entity(string name, int health, int strength)
{
	this->health = health;
	this->name = name;
	this->strength = strength;
	this->isAlive = Status::alive;

	maxHealth = health;
	xp = 0;
	xpToLevel = 50;
	level = 1;
}

std::string Entity::levelUp()
{
	strength += 2;
	health += 20;
	maxHealth += 20;
	xp = 0;
	level++;
	xpToLevel += 20;

	return "Leveled up! Strength +1, HP +10";
}

std::string Entity::battle( Entity& enemy)
{
	int damageTaken = 0;

	//keep going until enemy or hero is dead
	while( enemy.getHealth() > 0 && this -> health > 0 )
	{
		cout << enemy.getHealth() << endl;
		//Player hits enemy if it's alive
		if ( this -> health > 0)
		{
			enemy.setHealth( enemy.getHealth() - this-> strength );
		}

		

		//Enemy hits player if it's alive
		if (enemy.health > 0)
		{
			
			this->setHealth(this->getHealth() - enemy.strength);

			damageTaken += enemy.strength;
		}

	}


	return "You killed a " + enemy.getName() + ", taking " + std::to_string(damageTaken) + " damage." ;
}

//GETTERS AND SETTERS

int Entity::getHealth()
{
	return health;
}

int Entity::getMaxHealth()
{
	return maxHealth;
}

int Entity::getStrength()
{
	return strength;
}

std::string Entity::getName()
{
	return name;
}

int Entity::getXp()
{
	return xp;
}

int Entity::getXpToLevel()
{
	return xpToLevel;
}

int Entity::getLevel()
{
	return level;
}

bool Entity::heroStatus() {
	if (isAlive == Status::alive) {
		return true;
	}
	else
		return false;
}

void Entity::setHealth(int health)
{
	if (health < 0)
	{
		this->health = 0;
		isAlive = Status::dead;
	}
	else
		this->health = health;
}

void Entity::setStrength(int strength)
{
	this->strength = strength;
}

void Entity::setName( string name )
{
	this->name = name;
}

void Entity::setXp(int xp)
{
	
	this->xp = xp;
}

void Entity::setXpToLevel(int xpToLevel)
{
	this->xpToLevel = xpToLevel;
}

void Entity::setLevel(int level)
{
	this->level = level;
}