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
    float effectMultiplier; // 19
    int fireBallDamage; // 20, 35
    float slowTimeTime; // 20, 35
    int shieldMaxCharges; // 22
    int multiBallEffectMultiplier; // 29, 31, 34
    float multiBallMultiplyChance; // 29, 31, 34

    TechTreePUEffects()
    {
        speed = 0.80f;
        shieldCharge = 0;
        startShield = false;
        biggerPadEffectMultiplier = 0;
        effectMultiplier = 0;
        fireBallDamage = 0;
        slowTimeTime = 0;
        shieldMaxCharges = 0;
        multiBallEffectMultiplier = 0;
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
        maxSize = 0;
    }
};

// Techs that affects ObjectManager
struct TechTreeUtilityEffects
{
    bool PUGiftEnabled; // 6
    float ballsCollideFuel; // 13
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
        ballsCollideFuel = 0;
        extraBallFuel = 0;
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
    bool stickyPadPUEnabled; // 9
    bool fireBallPUEnabled; // 16
    bool slowTimePUEnabled; // 18
    bool startNodePowerups; // Allows Shield, Multiball and Pad enlarge to be dropped

    TechTreeLevelEffects()
    {
        stickyPadPUEnabled = false;
        fireBallPUEnabled = false;
        slowTimePUEnabled = false;
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