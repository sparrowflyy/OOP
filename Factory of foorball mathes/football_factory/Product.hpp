#pragma once
#include  <string>

class Player;
class Team;
class Match;

class Product
{
public:
	virtual int get_id() const = 0;
	static Product* create(std::string& data);
	virtual std::string& serialize() const = 0;
	virtual int get_type() const = 0;
};

