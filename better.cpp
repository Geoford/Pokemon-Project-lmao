#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// Character struct with stats
struct Character {
    string type;
    int health;
    int speed;
    int skill;
    int morale;
    bool stunned = false;
    bool stunnedNextTurn = false;
};

// Get character stats
Character getCharacterStats(const string& choice) {
    if (choice == "1") return {"Aqua", 39, 39, 35, 27};
    if (choice == "2") return {"Beast", 31, 35, 31, 43};
    if (choice == "3") return {"Plant", 43, 31, 31, 35};
    return {"Invalid", 0, 0, 0, 0};
}

// Scale character stats
Character createCharacter(const Character& base) {
    return {base.type, base.health * 5, base.speed, base.skill, base.morale};
}

// Get random enemy
Character getRandomEnemy() {
    int enemyType = rand() % 3 + 1;
    return createCharacter(getCharacterStats(to_string(enemyType)));
}

// Display stats
void displayStats(const Character& character) {
    cout << character.type << " Stats:\n";
    cout << "Health: " << character.health << "\n";
    cout << "Speed: " << character.speed << "\n";
    cout << "Skill: " << character.skill << "\n";
    cout << "Morale: " << character.morale << "\n\n";
}

// Critical hit function
bool isCriticalHit(int morale) {
    return (rand() % 100) < (morale / 1.2);
}

// Get user action
string getAction() {
    string choice;
    cout << "Choose your action:\n";
    cout << "[1] Attack\n[2] Stun\n[3] Block\n[4] Heal\n";
    cin >> choice;
    if (choice == "1") return "Attack";
    if (choice == "2") return "Stun";
    if (choice == "3") return "Block";
    if (choice == "4") return "Heal";
    return "Invalid";
}

// Get random enemy action
string getEnemyAction() {
    int action = rand() % 4 + 1;
    if (action == 1) return "Attack";
    if (action == 2) return "Stun";
    if (action == 3) return "Block";
    if (action == 4) return "Heal";
    return "Invalid";
}

// Battle function
void battle(Character& player, Character& enemy) {
    vector<string> eventLog;
    int turnCounter = 1; // Turn counter for event log

    while (player.health > 0 && enemy.health > 0) {
        system("cls");

        cout << player.type << " HP: " << player.health << " | " 
             << enemy.type << " HP: " << enemy.health << "\n\n";

        // Print out event log for the turn
        cout << "=================\n";
        cout << "Turn " << turnCounter << "\n";

        if (!eventLog.empty()) {
            for (const string& event : eventLog) {
                cout << event << "\n";
            }
        }

        // Display stats
        cout << "=================\n\n";

        eventLog.clear(); // Clear previous turn logs

        // Handle stun status
        if (player.stunned) {
            eventLog.push_back("You are stunned and miss this turn!");
            player.stunned = false;
        }
        if (enemy.stunned) {
            eventLog.push_back("Enemy is stunned and misses this turn!");
            enemy.stunned = false;
        }

        if (player.stunnedNextTurn) {
            player.stunnedNextTurn = false;
            player.stunned = true;
        }
        if (enemy.stunnedNextTurn) {
            enemy.stunnedNextTurn = false;
            enemy.stunned = true;
        }

        // Get player's and enemy's action
        string playerAction = player.stunned ? "Skip" : getAction();
        string enemyAction = enemy.stunned ? "Skip" : getEnemyAction();

        eventLog.push_back("You chose: " + playerAction);
        eventLog.push_back("Enemy chose: " + enemyAction);

        int attackDamage = 10;
        int stunDamage = 5;
        int healAmount = 10;

        // Apply conditions for Block > Stun or Stun > Block
        if (playerAction == "Stun" && enemyAction == "Block") {
            stunDamage = 0;
            player.stunnedNextTurn = true;  // Player will be stunned next turn
            eventLog.push_back("You stunned the enemy, but they blocked it! You will be stunned next turn.");
        }
        if (enemyAction == "Stun" && playerAction == "Block") {
            stunDamage = 0;
            enemy.stunnedNextTurn = true;  // Enemy will be stunned next turn
            eventLog.push_back("Enemy stunned you, but you blocked it! Enemy will be stunned next turn.");
        }

        // If both player and enemy use Stun
        if (playerAction == "Stun" && enemyAction == "Stun") {
            // Compare speed: faster character stuns this turn and the next one
            if (player.speed > enemy.speed) {
                enemy.stunned = true;
                enemy.stunnedNextTurn = true;
                eventLog.push_back("You stunned the enemy and they will be stunned next turn!");
            } else {
                player.stunned = true;
                player.stunnedNextTurn = true;
                eventLog.push_back("Enemy stunned you and you will be stunned next turn!");
            }
            stunDamage = 0;  // No stun damage if both characters stun
        }

        // If player attacks and enemy blocks
        if (playerAction == "Attack" && enemyAction == "Block") {
            attackDamage = 0;
            eventLog.push_back("Enemy blocked your attack! No damage dealt.");
        }

        // If enemy attacks and player blocks
        if (enemyAction == "Attack" && playerAction == "Block") {
            attackDamage = 0;
            eventLog.push_back("You blocked the enemy's attack! No damage received.");
        }

        // Critical hits and heal mechanics
        if (playerAction == "Attack" && isCriticalHit(player.morale)) {
            attackDamage *= 1.5;
            eventLog.push_back("Critical Hit! Attack dealt " + to_string(attackDamage) + " damage!");
        }
        if (enemyAction == "Attack" && isCriticalHit(enemy.morale)) {
            attackDamage *= 1.5;
            eventLog.push_back("Enemy landed a Critical Hit! Attack dealt " + to_string(attackDamage) + " damage!");
        }

        // Apply actions
        if (playerAction == "Attack" && enemyAction != "Block") {
            enemy.health -= attackDamage;
            eventLog.push_back("You dealt " + to_string(attackDamage) + " damage!");
        }

        if (enemyAction == "Attack" && playerAction != "Block") {
            player.health -= attackDamage;
            eventLog.push_back("Enemy dealt " + to_string(attackDamage) + " damage!");
        }

        if (playerAction == "Stun" && enemyAction != "Block") {
            enemy.health -= stunDamage;
            enemy.stunned = true;
            eventLog.push_back("You stunned the enemy and dealt " + to_string(stunDamage) + " damage!");
        }

        if (playerAction == "Heal") {
            player.health += healAmount;
            eventLog.push_back("You healed " + to_string(healAmount) + " HP!");
        }

        if (playerAction == "Block") {
            eventLog.push_back("You are in block stance!");
        }

        // End of turn update
        cout << "\nPress Enter to continue...\n";
        cin.ignore();
        cin.get();

        turnCounter++;  // Increment turn number
    }

    system("cls");
    if (player.health > 0) {
        cout << "You won the battle!\n";
    } else {
        cout << "You lost! Try again next time.\n";
    }
}

// Main function
int main() {
    srand(time(0));

    string userChoice;
    Character player, enemy;

    while (true) {
        cout << "Pick Your Type:\n[1] Aqua\n[2] Beast\n[3] Plant\n";
        cin >> userChoice;
        Character baseStats = getCharacterStats(userChoice);
        
        if (baseStats.type != "Invalid") {
            system("cls");
            player = createCharacter(baseStats);
            cout << "You picked " << player.type << "!\n\n";
            displayStats(player);
            break;
        } else {
            cout << "Invalid Type. Try again.\n\n";
        }
    }

    enemy = getRandomEnemy();
    cout << "Enemy picked " << enemy.type << "!\n\n";
    displayStats(enemy);

    cout << "Battle begins!\nPress Enter to continue...\n";
    cin.ignore();
    cin.get();

    battle(player, enemy);

    return 0;
}
