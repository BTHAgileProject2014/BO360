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
	double GetRotation();

	// Overloaded functions
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName);
	void Handle(InputMessages p_inputMessages);
	void Handle(PowerUpTypes p_type, bool p_activated);
	void SetSegments(int p_segments);
	int GetSegments();
	void AddSegments(int p_segments);
	void RemoveSegments(int p_segments);
	double GetDegrees();
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
