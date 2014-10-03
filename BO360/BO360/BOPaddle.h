#ifndef BOPADDLE_H_
#define BOPADDLE_H_
#include "BOObject.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include "BOPUSubscriber.h"
#include "BOPowerUpManager.h"

class BOPaddle : public BOObject, public BOSubscriber, public BOPUSubscriber
{
public:
	BOPaddle();
	~BOPaddle();

	void Update(double p_deltaTime);
	double GetRotation()const; // This returns the center of the first segment
    double GetStartRotation()const; // This returns the actual start of the paddle

	// Overloaded functions
	bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite);
	void Handle(InputMessages p_inputMessages);
	void Handle(PowerUpTypes p_type, bool p_activated);
	int GetSegments()const;
	void AddSegments(int p_segments);
	void RemoveSegments(int p_segments);
	double GetDegrees()const;
	void Draw();

	float2 GetBallSpawnPosition();

private:
	double m_rotation;
	double m_deltaRotation;
	bool m_movingLeft;
	bool m_movingRight;
	int m_segments;
	double m_totalDegrees;
	double m_segementDegree;
};
#endif
