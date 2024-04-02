#include "sprite.h"

class Player
{
public:

    float velocity; 
    bool isCrouch; 
    bool isProtect;
    bool isDie;
    bool lastDirectionLeft;

 
    float HP;
    float maxHP;


    int jumps;
    bool isZPressed;
    bool wasZPressed;
    bool isJumping;
    
    int powerUp;
   
    bool isRunning;
    bool isRunningL;


    float attackDamage;


    bool isAttack1;
    bool isAttack2;
   

};

class ClassicMonster
{
public:

    float velocity; 
    bool isDie;
    bool lastDirectionLeft;

    float HP;
    float maxHP;
   
    bool isRunning;
    bool isRunningL;

    float attackDamage;

    bool isAttack1;

};

class MiniBoss
{
public:

    float velocity;  
    bool isProtect;
    bool isDie;
    bool lastDirectionLeft;

 
    float HP;
    float maxHP;
   
    bool isRunning;
    bool isRunningL;


    float attackDamage;


    bool isAttack1;
    bool isAttack2;
    bool isSpecial1;

};

class LevelBoss
{
public:

    float velocity; 
    bool isProtect;
    bool isDie;
    bool lastDirectionLeft;

 
    float HP;
    float maxHP;


    int jumps;
    bool isZPressed;
    bool wasZPressed;
    bool isJumping;
    
    int power;
   
    bool isRunning;
    bool isRunningL;


    float attackDamage;


    bool isAttack1;
    bool isAttack2;
    bool isSpecial1;
    bool isSpecial2;

};

class FinalBoss
{
public:

    float velocity; 
    bool isProtect;
    bool isDie;
    bool lastDirectionLeft;

 
    float HP;
    float maxHP;


    int jumps;
    bool isJumping;
    
    int powerUp;
   
    bool isRunning;
    bool isRunningL;

    float attackDamage;

    bool isAttack1;
    bool isAttack2;
    bool isSpecial1;
    bool isSpecial2;
    bool isUlt;

};


 