#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>


using namespace std;    

int main(){
    string userChoice, userType, EnemyType;
    int userHealthPoints, userSpeed, userSkill, userMorale; 
    int enemyHealthPoints, enemySpeed, enemySkill, enemyMorale;

    // userSkill, Energy, SLP, BreedCount, BreedSpeed, BreedMorale, BreedSkill, BreedEnergy, BreedSLP;
    while (true){
        cout<<"Pick Your Type:\n[1] Aqua\n[2] Beast\n[3]Plant\n";
        cin>>userChoice;
        
        if (userChoice=="1"){
            userType="Aqua";
            system("cls");
            cout<<"You picked Aqua\n\n";
            userHealthPoints=39;
            userSpeed=39;
            userSkill=35;
            userMorale=27;
            break;
        }else if (userChoice=="2"){
            system("cls");
            userType="Beast";
            userHealthPoints=31;
            userSpeed=35;
            userSkill=31;
            userMorale=43;
            cout<<"You picked Beast\n\n";
            break;
        }else if (userChoice=="3"){
            system("cls");
            userType="Plant";
            userHealthPoints=43;
            userSpeed=31;
            userSkill=31;
            userMorale=35;
            cout<<"You picked Plant\n\n";
            break;
        }else{
            cout<<"Invalid Type.\n\n";
            continue;
        }
    }
    // Enemy Type Randomizer
    int enemyTypeRandomizer = rand() % 3 + 1;
    if (enemyTypeRandomizer==1){
        EnemyType="Plant";
        enemyHealthPoints=43;
        enemySpeed=31;
        enemySkill=31;
        enemyMorale=35;
        cout<<"The enemy picked Plant\n\n";
    }else if (enemyTypeRandomizer==2){
        EnemyType="Aqua";
        enemyHealthPoints=39;
        enemySpeed=39;
        enemySkill=35;
        enemyMorale=27;
        cout<<"The enemy picked Aqua\n\n";
    }else{
        EnemyType="Beast";
        enemyHealthPoints=31;
        enemySpeed=35;
        enemySkill=31;
        enemyMorale=43;
        cout<<"The enemy picked Beast\n\n";
    }

}