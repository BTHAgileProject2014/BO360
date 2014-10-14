#ifndef BOTECHTREEEFFECT_H_
#define BOTECHTREEEFFECT_H_

#include "BOComponent.h"

// Techs that affects the ball
struct TechTreeBallEffects
{
    float speed; // 4
    float gravity; // 5
    int damage; // 15, 17

    TechTreeBallEffects()
    {
        speed = 1.0f;
        gravity = 0;
        damage = 0;
    }
};

// Techs that affects powerups
struct TechTreePUEffects
{
    float speed; // 1, 7
    int shieldCharge; // 2
    bool startShield; // 8
    float biggerPadEffectMultiplier; // 11, 26
    //float effectMultiplier; // 19
    int fireBallDamage; // 20, 35
    float slowTimeTime; // 20, 35
    bool stackableShield; // 22
	int maxStackShield;
    //int multiBallEffectMultiplier; // 29, 31, 34//////////////////dafuq?
    float multiBallMultiplyChance; // 29, 31, 34
    float decreaseCD;

    TechTreePUEffects()
    {
        speed = 1.0f;
        shieldCharge = 1;
        startShield = false;
        biggerPadEffectMultiplier = 0;		// in precent for chance to get double effect, 0.33 for 33% 
        //effectMultiplier = 0;
        fireBallDamage = 0;
        slowTimeTime = 0;
        stackableShield = false;
		maxStackShield = 5;
        multiBallMultiplyChance = 1;
        decreaseCD = 1;
    }
};

// Techs that affects the paddle
struct TechTreePaddleEffects
{
    float speed; // 3
    int size; // 10, 23, 25
    int maxSize; // 12

    TechTreePaddleEffects()
    {
        speed = 1.0f;
        size = 0;
        maxSize = 0; // Nr to plus to standard maxsize // Standard is 5 atm
    }
};

// Techs that affects ObjectManager
struct TechTreeUtilityEffects
{
    bool PUGiftEnabled; // 6
    bool ballsCollideFuel; // 13
    float extraBallFuel; // 14
    bool megaPadEnabled; // 21
    int extraLifePerLevel; // 24
    bool giantBallEnabled; // 27
    int extraBallsFirstLaunch; // 28, 32
    bool superBouncy; // 30
    bool quantumFuelEnabled; // 33
    bool shockwaveEnabled;

    TechTreeUtilityEffects()
    {
        PUGiftEnabled = false;
        ballsCollideFuel = false;
        extraBallFuel = 0;					// fuel is 1 from start this is a value to add to that standard
        megaPadEnabled = false;
        extraLifePerLevel = 0;
        giantBallEnabled = false;
        extraBallsFirstLaunch = 0;
        superBouncy = false;
        quantumFuelEnabled = false;
        shockwaveEnabled = false;
    }
};

// Techs that affects the level - powerup drops for example
struct TechTreeLevelEffects
{
    float stickyPadPUDuration; // 9
    float fireBallPUDuration; // 16
    float slowTimePUDuration; // 18
    bool startNodePowerups; // Allows Shield, Multiball and Pad enlarge to be dropped

    TechTreeLevelEffects()
    {
        stickyPadPUDuration = 0.0f;
        fireBallPUDuration = 0.0f;
        slowTimePUDuration = 0.0f;
        startNodePowerups = false;
    }
};

class BOTechTreeEffects: public BOComponent
{
public:
    BOTechTreeEffects();
    ~BOTechTreeEffects();

    bool Initialize();
    void Shutdown();

    static TechTreeBallEffects BallEffects;
    static TechTreeLevelEffects LevelEffects;
    static TechTreePaddleEffects PaddleEffects;
    static TechTreePUEffects PUEffects;
    static TechTreeUtilityEffects UtilityEffects;
};

#endif