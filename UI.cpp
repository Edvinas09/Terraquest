#include "Terrain/Terrain.h"
#include "Troop/Troop.hpp"
#include "Buildings/Building.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "UI.hpp"

namespace UI {
	//Define static variables
	int Resources::wood = 0;
	int Resources::rock = 0;
	int Resources::iron = 0;

	void Resources::setWood(int amount) {
		wood += amount;
	}
	void Resources::setRock(int amount) {
		rock += amount;
	}
	void Resources::setIron(int amount) {
		iron += amount;
	}
	int Resources::getWood() {
		return wood;
	}
	int Resources::getRock() {
		return rock;
	}
	int Resources::getIron() {
		return iron;
	}
}