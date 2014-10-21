#ifndef BOPADDLE_H_
#define BOPADDLE_H_

#include "BOGlobals.h"
#include "BOAnimatedObject.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include "BOPUSubscriber.h"
#include "BOPowerUpManager.h"
#include "BOHUDManager.h"

class BOPaddle : public BOAnimatedObject, public BOSubscriber, public BOPUSubscriber
{
public:
	BOPaddle();
	~BOPaddle();

	void Update(double p_deltaTime);
	double GetRotation()const; // This returns the center of the first segment
    double GetStartRotation()const; // This returns the actual start of the paddle

	// Overloaded functions
    bool Initialize(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_numberOfFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite);
	void Handle(InputMessages p_inputMessages);
	void Handle(PowerUpTypes p_type, bool p_activated);
	int GetSegments()const;
	void AddSegments(int p_segments);
	void RemoveSegments(int p_segments);
	double GetDegrees()const;
	void Draw();

    bool GetStickyState()const;
    void SetStickyState(bool p_active);
    void SetStickyTimer(double p_time);
    double GetStickyTimer() const;
    double GetStickyTimeLeft() const;
    bool StickyGotRemoved() const;    

	float2 GetBallSpawnPosition();
    float2 GetBallStuckPosition(float angle);

	void ActivateMegaPad();
	void DeactivateMegaPad();

private:
	double m_deltaRotation;
	bool m_movingLeft;
	bool m_movingRight;
	int m_segments;
	int m_minSegments;
	int m_maxSegments;
	int m_preMegaSegments;
	double m_totalDegrees;
	double m_segementDegree;
    bool m_isSticky;
    bool m_isPrevSticky;
    double m_stickyMaxTimer;
    double m_stickyCurrentTimer;
	bool m_megaPadActive;
	double m_megaPadTimeElapsed;
	double m_megaPadTimeDuration;
	double m_megaPadCoolDown;

    SDL_Texture* m_stickyGlow;
};
#endif
