#include "Product.hpp"
#include <sstream>
#include "Match.hpp"
#include "Player.hpp"


Product* Product::create(std::string& data)
{															
	std::string name_of_type;
	std::istringstream(data) >> name_of_type;
	if (name_of_type == Player::product_type) return new Player(data);
	if (name_of_type == Team::product_type) return new Team(data);
	if (name_of_type == Match::product_type) return new Match(data);
	return nullptr;
}