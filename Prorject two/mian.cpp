#include <bits/stdc++.h>
using namespace std;
// Class Weapon
class weapon{
protected:
    double power;
    double health;
    bool type;
public:
    weapon(double, double,bool);
    virtual double PowerAttacking() = 0;
    virtual void Defense(double) = 0;
    virtual string printInfo() = 0;
    virtual bool typeChild() = 0;
    void AdjustAbilities(double);
    bool RoundFight(weapon &);
    double getHealth();
};
weapon::weapon(double power, double health,bool type)
    : power(power), health(health),type(type){ }
bool weapon::RoundFight(weapon &weaponDefense) {
    if(weaponDefense.health <= power){
        return 1;
    }
    else
        return 0;
}
double weapon::getHealth(){
    return this->health;
}
void weapon::AdjustAbilities(double factor){
  this->power *= factor;
  this->health *= factor;
}
//  -----------------------------------------------------------
// Class sword
class Sword : public weapon{
private:
    int Sharpness;
public:
    Sword(int,double,double);
    double PowerAttacking();
    void Defense(double);
    void setSharpness(int);
    int getSharpness() const;
    void setHealth(double);
    void setPower(double);
    double getPower() const;
    string printInfo();
    bool typeChild();
};
Sword::Sword(int Sharpness, double power, double health)
    : Sharpness(Sharpness), weapon(power, health,true){
}
double Sword::PowerAttacking(){
    this->power = (this->power * Sharpness) / 100.0;
    return this->power;
}
void Sword::Defense(double hit){
    this->health -= hit;
}
void Sword::setSharpness(int sharpness){
    Sharpness = sharpness;
}
int Sword::getSharpness() const{
    return Sharpness;
}
void Sword::setHealth(double health){
    this->health = health;
}
void Sword::setPower(double power){
    this->power = power;
}
double Sword::getPower()const{
    return this->power;
}
string Sword::printInfo(){
    stringstream os;
    os << "Sword info :\n   Sharpness : ";
    os << getSharpness();
    os << "\n   Power : ";
    os << getPower();
    os << "\n   Health : ";
    os << getHealth();
    os << "\n";
    return os.str();
}
bool Sword::typeChild(){
    return type;
}
// ------------------------------------------------------------
// Class Shield
class Shield :public weapon{
private:
    char color;
    int hardness;
public:
    Shield(char, int, double, double);
    double PowerAttacking();
    void Defense(double);
    string printInfo();
    void setHealth(double);
    void setPower(double);
    double getPower() const;
    void setColor(char);
    char getColor() const;
    void setHardness(int);
    int getHardness() const;
    bool typeChild();
};
Shield::Shield(char color, int hardness, double power, double health)
    : color(color), hardness(hardness), weapon(power, health,0){};
double Shield::PowerAttacking(){
    power *= 0.1;
    return power;
}
void Shield::Defense(double hit){
    hit = (hit * hardness) / 100.0;
    this->health -= hit;
}
void Shield::setHealth(double health){
    this->health = health;
}
void Shield::setPower(double power){
    this->power = power;
}
double Shield::getPower() const{
    return this->power;
}
void Shield::setColor(char color){
    this->color = color;
}
char Shield::getColor() const{
    return this->color;
}
void Shield::setHardness(int hardness){
    this->hardness = hardness;
}
int Shield::getHardness() const{
    return hardness;
}
string Shield::printInfo(){
    stringstream os;
    os << "Shield info :\n   Color : ";
    os << getColor();
    os << "\n   Hardness : ";
    os << getHardness();
    os << "\n   Power : ";
    os << getPower();
    os << "\n   Health : ";
    os << getHealth();
    os << '\n';
    return os.str();
}
bool Shield::typeChild(){
    return type;
}
// -----------------------------------------------------------
int MAX = 1e5;
int CountSwords(weapon* parr[]){
    int cnt = 0;
    for (int i = 0; i < MAX;i++){
        cnt += (parr[i]->typeChild());
    }
    return cnt;
}
int CountShields(weapon* parr[]){
    int cnt = 0;
    for (int i = 0; i < MAX;i++){
        cnt += (!parr[i]->typeChild());
    }
    return cnt;
}
int Fight(weapon *pw1 ,weapon *pw2){
    bool ok = 1;
    double health1 = pw1->getHealth();
    double health2 = pw2->getHealth();
    double power1 = pw1->PowerAttacking();
    double power2 = pw2->PowerAttacking();
    while(health1> 0 && health2 > 0){
        if(ok){
            health1 -= (power1 + 1);
            ok = !ok;
        }
        else{
            health2 -= (power2 + 1);
            ok = !ok;
        }
    }
    return (health1 <= 0 ? -1 : 1);
}
int main(){
    MAX = 5;
    weapon *arr[MAX];
    Sword sword1(25, 10, 7);
    Sword sword2(40, 8, 5);
    Shield shield1('#',5, 0.5, 10);
    Shield shield2('#',73, 1.5, 15);
    Shield shield3('#',23, 1, 12);
    arr[0] = &sword1;
    arr[1] = &sword2;
    arr[2] = &shield1;
    arr[3] = &shield2;
    arr[4] = &shield3;
    for (int i = 0; i < MAX;i++){
        arr[i]->PowerAttacking();
    }
    printf("Number Of Sword = %d\nNumber Of Shield = %d\n", CountSwords(arr), CountShields(arr));
    printf("First Fight between Second Sword and Second Shield the winner is %s\n", (Fight(&sword2, &shield2) == -1 ? "First" : "Second"));
    shield2.AdjustAbilities(2.5);
    printf("First Fight between Second Sword and Second Shield the winner is %s\n", (Fight(&sword2, &shield2) == -1 ? "First" : "Second"));
    for (int i = 0; i < MAX;i++){
        cout << arr[i]->printInfo();
    }
    for (int i = 0; i < MAX;i++){
        arr[i]->AdjustAbilities(5);
    }
    for (int i = 0; i < MAX;i++){
        cout << arr[i]->printInfo();
    }
    return 0;
}

/**
 * output : -
    *Number Of Sword = 2
    Number Of Shield = 3
    First Fight between Second Sword and Second Shield the winner is First
    First Fight between Second Sword and Second Shield the winner is First
    Sword info :
        Sharpness : 25
        Power : 2.5
        Health : 7
    Sword info :
        Sharpness : 40
        Power : 0.512
        Health : 5
    Shield info :
        Color : #
        Hardness : 5
        Power : 0.05
        Health : 10
    Shield info :
        Color : #
        Hardness : 73
        Power : 0.00375
        Health : 37.5
    Shield info :
        Color : #
        Hardness : 23
        Power : 0.1
        Health : 12
    Sword info :
        Sharpness : 25
        Power : 12.5
        Health : 35
    Sword info :
        Sharpness : 40
        Power : 2.56
        Health : 25
    Shield info :
        Color : #
        Hardness : 5
        Power : 0.25
        Health : 50
    Shield info :
        Color : #
        Hardness : 73
        Power : 0.01875
        Health : 187.5
    Shield info :
        Color : #
        Hardness : 23
        Power : 0.5
        Health : 60
 *
 * **/