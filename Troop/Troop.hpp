#pragma once
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace GameEntities {

	enum class TroopType {
		Melee,
		Ranged,
		Miner,
		Tank
	};

	class Troop {
	private:
		int health;
		int damage;
		int speed;
		sf::Vector2f position;

	public:
		Troop(int health, int damage, int speed, const sf::Vector2f& position)
			: health(health), damage(damage), speed(speed), position(position) {
		}
		virtual ~Troop() = default;

		int getHealth() const { return health; }
		int getDamage() const { return damage; }
		int getSpeed() const { return speed; }
		sf::Vector2f getPosition() const { return position; }

		void setHealth(int newHealth) { health = newHealth; }
		void setDamage(int newDamage) { damage = newDamage; }
		void setSpeed(int newSpeed) { speed = newSpeed; }
		void setPosition(const sf::Vector2f& newPosition) { position = newPosition; }

		virtual std::string toString() const {
			std::ostringstream oss;
			oss << "Troop: Health=" << health
				<< ", Damage=" << damage
				<< ", Speed=" << speed
				<< ", Position=(" << position.x << ", " << position.y << ")";
			return oss.str();
		}

	};


	class TroopCreator {
	public:
		static std::unique_ptr<Troop> createTroop(TroopType type, const sf::Vector2f& spawnPosition);
	};

	class Melee : public Troop { using Troop::Troop; };

	class Miner : public Troop {
		int gatherRate;
	public:
		Miner(int health, int damage, int speed, int gatherRate, const sf::Vector2f& position)
			: Troop(health, damage, speed, position), gatherRate(gatherRate) {
		}

		int getGatherRate() const { return gatherRate; }
		void setGatherRate(int newGatherRate) { gatherRate = newGatherRate; }

		std::string toString() const override {
			std::ostringstream oss;
			oss << Troop::toString() << ", GatherRate=" << gatherRate;
			return oss.str();
		}
	};

	class Ranged : public Troop {
		int range;
	public:
		Ranged(int health, int damage, int speed, int range, const sf::Vector2f& position)
			: Troop(health, damage, speed, position), range(range) {
		}
		int getRange() const { return range; }
		void setRange(int newRange) { range = newRange; }

		std::string toString() const override {
			std::ostringstream oss;
			oss << Troop::toString() << ", Range=" << range;
			return oss.str();
		}
	};

	class Tank : public Troop {
		int armor;
	public:
		Tank(int health, int damage, int speed, int armor, const sf::Vector2f& position)
			: Troop(health, damage, speed, position), armor(armor) {
		}
		int getArmor() const { return armor; }
		void setArmor(int newArmor) { armor = newArmor; }

		std::string toString() const override {
			std::ostringstream oss;
			oss << Troop::toString() << ", Armor=" << armor;
			return oss.str();
		}
	};

}