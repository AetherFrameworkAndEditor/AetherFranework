#include "Particle.h"
#include "Rectangle2D.h"
#include "Rectangle3D.h"
#include <random>
using namespace aetherClass;
Particle::Particle()
{
	m_2dParticle.clear();
	m_3dParticle.clear();
	m_renderMode = Particle::eMode::eUnknown;
}


Particle::~Particle()
{
}

//
bool Particle::Initialize(eMode renderMode, std::string texturePath, const int maxCount){
	m_renderMode = renderMode;
	if (renderMode == eMode::e2D)
	{
		// まだ2D対応できていないので２Dの場合でも３D
		Create3DParticle(texturePath, maxCount);
	}
	else if (renderMode == eMode::e3D)
	{
		Create3DParticle(texturePath, maxCount);
	}
	else
	{
		return false;
	}

	InitializeParticle();
	m_maxParticle = maxCount;

	m_minRange = 0.0f;
	m_maxRange = 0.0f;
	return true;
}


void Particle::Finalize(){

	// remove particle object array
	Remove2DParticle();
	Remove3DParticle();
}

//
void Particle::Render(ShaderBase* shader){

	// render particle
	Render2DParticle(shader);
	Render3DParticle(shader);

	return;
}

//
void Particle::Update(Vector3 frameVector,float flameTime){
	Update2DParticle(frameVector, flameTime);
	Update3DParticle(frameVector, flameTime);

	return;
}

bool Particle::InitializeParticle()
{
	// Set the random deviation of where the particles can be located when emitted.
	m_particleDeviation._x = 0.5f;
	m_particleDeviation._y = 0.1f;
	m_particleDeviation._z = 2.0f;

	// Set the speed and speed variation of particles.
	m_particleVelocity = 1.0f;
	m_particleVelocityVariation = 0.2f;
	// Set the number of particles to emit per second.
	m_particlesPerSecond = 250.0f;

	// Initialize the particle list.
	if (m_renderMode == eMode::e2D)
	{
		for (int i = 0; i<m_2dParticle.size(); i++)
		{
			m_2dParticle[i]._active = false;
		}
	}
	else if (m_renderMode == eMode::e3D)
	{
		for (int i = 0; i<m_3dParticle.size(); i++)
		{
			m_3dParticle[i]._active = false;
		}
	}
	
	m_maxActiveLength = 5;

	// Initialize the current particle count to zero since none are emitted yet.
	m_currentParticleCount = 0;

	// Clear the initial accumulated time for the particle per second emission rate.
	m_accumulatedTime = 0.0f;

	return true;
}


//
bool Particle::Create2DParticle(std::string texturePath, const int maxCount){
	m_2dParticle.resize(maxCount);
	bool result = false;
	for (int index = 0; index < m_2dParticle.size(); ++index)
	{
		// それぞれのオブジェクト作成
		m_2dParticle[index]._sprite = new aetherClass::Rectangle2D();
		result = m_2dParticle[index]._sprite->Initialize();
		if (!result)
		{
			return false;
		}
		// テクスチャー
		Texture* texture = new Texture();
		result = texture->Load(texturePath);
		if (!result)
		{
			return false;
		}

		m_2dParticle[index]._sprite->SetTexture(texture);
		m_2dParticle[index]._sprite->property._transform._translation._y = index*0.1;

	}
	return true;
}

// 
bool Particle::Create3DParticle(std::string texturePath, const int maxCount){
	m_3dParticle.resize(maxCount);
	bool result = false;

	for (int index = 0; index < m_3dParticle.size();++index)
	{
		// それぞれのオブジェクト作成
		m_3dParticle[index]._sprite = new aetherClass::Rectangle3D;
		result = m_3dParticle[index]._sprite->Initialize();
		if (!result)
		{
			return false;
		}
		// テクスチャー
		Texture* texture = new Texture();
		result = texture->Load(texturePath);
		if (!result)
		{
			return false;
		}

		m_3dParticle[index]._sprite->SetTexture(texture);
		m_3dParticle[index]._sprite->property._transform._translation._y = index*0.1;
		
	}
	return true;
}

//
void Particle::Render2DParticle(ShaderBase* shader){
	if (m_renderMode!=eMode::e2D)return;

	for (auto index : m_2dParticle)
	{
		if (index._sprite)
		{
			// 描画
			index._sprite->Render(shader);
		}

	}
	return;
}

//
void Particle::Render3DParticle(ShaderBase* shader){
	if (m_renderMode != eMode::e3D)return;
	
	for (auto index : m_3dParticle)
	{
		if (index._sprite)
		{
			index._sprite->Render(shader);
		}
	}
	return;
}

//
void Particle::Update2DParticle(Vector3 vector,float frameTime){
	if (m_renderMode != eMode::e2D)return;
	Kill2DParticle();
	Emit2DParticles(frameTime);
	// Each frame we update all the particles by making them move downwards using their position, velocity, and the frame time.
	for (auto& index : m_2dParticle)
	{
		if (index._sprite)
		{
			
			// 描画
			index._sprite->property._transform._translation._y = index._sprite->property._transform._translation._y - (index._velocity * frameTime * 0.001f);
		}

	}
}

//
void Particle::Update3DParticle(Vector3 vector,float frameTime){
	if (m_renderMode != eMode::e3D)return;

	vector=vector.Normalize();
	// 方向の取得
	m_direction = vector;

	Kill3DParticle();
	Emit3DParticles(frameTime);
	
	for (auto& index : m_3dParticle)
	{
		if (index._sprite)
		{
			
			auto direction = vector*(index._velocity * frameTime * 0.001f);
			index._sprite->property._transform._translation = index._sprite->property._transform._translation + direction;
		}
	}
	return;
}

// 
void Particle::Remove2DParticle(){
	if (m_2dParticle.size() <= 0)return;
	for (auto index : m_2dParticle)
	{
		if (index._sprite)
		{
			// それぞれのオブジェクト破棄
			index._sprite->Finalize();
			delete index._sprite;
			index._sprite = nullptr;
		}

	}

	m_2dParticle.clear();
	return;
}

//
void Particle::Remove3DParticle(){
	if (m_3dParticle.size() <= 0)return;

	for (auto& index : m_3dParticle)
	{
		if (index._sprite)
		{
			// それぞれのオブジェクト破棄
			index._sprite->Finalize();
			delete index._sprite;
			index._sprite = nullptr;
		}

	}

	m_3dParticle.clear();
	return;
}


void Particle::SetScale(Vector3 scale){
	if (m_2dParticle.size() > 0)
	{
		for (auto index : m_2dParticle)
		{
			if (index._sprite)
			{
				index._sprite->property._transform._scale = scale;
			}
			
		}
	}
	else if (m_3dParticle.size() > 0)
	{
		for (auto index : m_3dParticle)
		{
			if (index._sprite)
			{
				index._sprite->property._transform._scale = scale;
			}

		}
	}
	return;
}

//
void Particle::SetCamera(ViewCamera* camera){
	if (m_renderMode != eMode::e3D)return;
	for (auto index : m_3dParticle)
	{
		if (index._sprite)
		{
			index._sprite->SetCamera(camera);
		}
	}
	return;
}

void Particle::Emit2DParticles(float frameTime){
	bool emitParticle, found;
	float positionX, positionY, positionZ, velocity, red, green, blue;
	int index, i, j;


	// Increment the frame time.
	m_accumulatedTime += frameTime;

	// Set emit particle to false for now.
	emitParticle = false;

	// Check if it is time to emit a new particle or not.
	if (m_accumulatedTime > (1000.0f / m_particlesPerSecond))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}

	// If there are particles to emit then emit one per frame.
	if ((emitParticle == true) && (m_currentParticleCount < (m_maxParticle - 1)))
	{
		m_currentParticleCount++;

		// Now generate the randomized particle properties.
		positionX = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviation._x;
		positionY = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviation._y;
		positionZ = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviation._z;

		velocity = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) * m_particleVelocityVariation;

		red = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		green = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		blue = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;

		// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
		// We will sort using Z depth so we need to find where in the list the particle should be inserted.
		index = 0;
		found = false;
		while (!found)
		{
			if ((m_2dParticle[index]._active == false) || (m_2dParticle[index]._sprite->property._transform._translation._z < positionZ))
			{
				found = true;
			}
			else
			{
				index++;
			}
		}

		// Now that we know the location to insert into we need to copy the array over by one position from the index to make room for the new particle.
		i = m_currentParticleCount;
		j = i - 1;

		while (i != index)
		{
			m_2dParticle[i]._sprite->property._transform._translation._x = m_2dParticle[j]._sprite->property._transform._translation._x;
			m_2dParticle[i]._sprite->property._transform._translation._y = m_2dParticle[j]._sprite->property._transform._translation._y;
			m_2dParticle[i]._sprite->property._transform._translation._z = m_2dParticle[j]._sprite->property._transform._translation._z;
			m_2dParticle[i]._sprite->property._color._red = m_2dParticle[j]._sprite->property._color._red;
			m_2dParticle[i]._sprite->property._color._green = m_2dParticle[j]._sprite->property._color._green;
			m_2dParticle[i]._sprite->property._color._blue = m_2dParticle[j]._sprite->property._color._blue;
			m_2dParticle[i]._velocity = m_2dParticle[j]._velocity;
			m_2dParticle[i]._active = m_2dParticle[j]._active;
			i--;
			j--;
		}

		// Now insert it into the particle array in the correct depth order.
		m_2dParticle[index]._sprite->property._transform._translation._x = positionX;
		m_2dParticle[index]._sprite->property._transform._translation._y = positionY;
		m_2dParticle[index]._sprite->property._transform._translation._z = positionZ;
		m_2dParticle[index]._sprite->property._color._red = red;
		m_2dParticle[index]._sprite->property._color._green = green;
		m_2dParticle[index]._sprite->property._color._blue = blue;
		m_2dParticle[index]._velocity = velocity;
		m_2dParticle[index]._active = true;
	}

	return;
}

//
void Particle::Emit3DParticles(float frameTime){
	bool emitParticle;
	Vector3 position;
	float velocity, red, green, blue;
	int i, j;

	// Increment the frame time.
	m_accumulatedTime += frameTime;

	// Set emit particle to false for now.
	emitParticle = false;

	// Check if it is time to emit a new particle or not.
	if (m_accumulatedTime > (1000.0f / m_particlesPerSecond))
	{
		m_accumulatedTime = 0.0f;
		emitParticle = true;
	}

	// If there are particles to emit then emit one per frame.
	if ((emitParticle == true) && 
		(m_currentParticleCount < (m_maxParticle - 1)))
	{
		m_currentParticleCount++;

		std::random_device randam;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(randam());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> xCreate(m_minRange._x,m_maxRange._x);
		std::uniform_int_distribution<> yCreate(m_minRange._y, m_maxRange._y);
		std::uniform_int_distribution<> zCreate(m_minRange._z, m_maxRange._z);

		const float randamPositionX = xCreate(randam);
		const float randamPositionY = yCreate(randam);
		const float randamPositionZ = zCreate(randam);
		// Now generate the randomized particle properties.
		position._x = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviation._x + randamPositionX + m_particlePosition._x;
		position._y = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviation._y + randamPositionY + m_particlePosition._y;
		position._z = (((float)rand() - (float)rand()) / RAND_MAX) * m_particleDeviation._z + randamPositionZ + m_particlePosition._z;


		velocity = m_particleVelocity + (((float)rand() - (float)rand()) / RAND_MAX) * m_particleVelocityVariation;

		red = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		green = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;
		blue = (((float)rand() - (float)rand()) / RAND_MAX) + 0.5f;

		// Now since the particles need to be rendered from back to front for blending we have to sort the particle array.
		// We will sort using Z depth so we need to find where in the list the particle should be inserted.
		int index = 0;
		bool found = false;
		while (!found)
		{
			if ((m_3dParticle[index]._active == false) || (m_3dParticle[index]._sprite->property._transform._translation._z < position._z))
			{
				found = true;
			}
			else
			{
				index++;
			}
		}

		// Now that we know the location to insert into we need to copy the array over by one position from the index to make room for the new particle.
		i = m_currentParticleCount;
		j = i - 1;

		while (i != index)
		{
			m_3dParticle[i]._sprite->property._transform._translation._x = m_3dParticle[j]._sprite->property._transform._translation._x;
			m_3dParticle[i]._sprite->property._transform._translation._y = m_3dParticle[j]._sprite->property._transform._translation._y;
			m_3dParticle[i]._sprite->property._transform._translation._z = m_3dParticle[j]._sprite->property._transform._translation._z;
			m_3dParticle[i]._sprite->property._color._red = m_3dParticle[j]._sprite->property._color._red;
			m_3dParticle[i]._sprite->property._color._green = m_3dParticle[j]._sprite->property._color._green;
			m_3dParticle[i]._sprite->property._color._blue = m_3dParticle[j]._sprite->property._color._blue;
			m_3dParticle[i]._velocity = m_3dParticle[j]._velocity;
			m_3dParticle[i]._active = m_3dParticle[j]._active;
			i--;
			j--;
		}

		// Now insert it into the particle array in the correct depth order.
		m_3dParticle[index]._sprite->property._transform._translation = position;
		m_3dParticle[index]._sprite->property._color._red = red;
		m_3dParticle[index]._sprite->property._color._green = green;
		m_3dParticle[index]._sprite->property._color._blue = blue;
		m_3dParticle[index]._velocity = velocity;
		m_3dParticle[index]._active = true;
	}

}

//
void Particle::Kill2DParticle(){

	// Kill all the particles that have gone below a certain height range.
	for (int i = 0; i < m_maxParticle; i++)
	{
		if ((m_2dParticle[i]._active == true) &&
			(m_2dParticle[i]._sprite->property._transform._translation._y < -3.0f))
		{
			m_2dParticle[i]._active = false;
			m_currentParticleCount--;

			// Now shift all the live particles back up the array to erase the destroyed particle and keep the array sorted correctly.
			for (int j = i; j < m_maxParticle - 1; j++)
			{
				m_2dParticle[j]._sprite->property._transform._translation._x = m_2dParticle[j + 1]._sprite->property._transform._translation._x;
				m_2dParticle[j]._sprite->property._transform._translation._y = m_2dParticle[j + 1]._sprite->property._transform._translation._y;
				m_2dParticle[j]._sprite->property._transform._translation._z = m_2dParticle[j + 1]._sprite->property._transform._translation._z;
				m_2dParticle[j]._sprite->property._color._red = m_2dParticle[j + 1]._sprite->property._color._red;
				m_2dParticle[j]._sprite->property._color._green = m_2dParticle[j + 1]._sprite->property._color._green;
				m_2dParticle[j]._sprite->property._color._blue = m_2dParticle[j + 1]._sprite->property._color._blue;
				m_2dParticle[j]._velocity = m_2dParticle[j + 1]._velocity;
				m_2dParticle[j]._active = m_2dParticle[j + 1]._active;
			}
		}
	}
	return;
}


//
void Particle::Kill3DParticle(){


	// Kill all the particles that have gone below a certain height range.
	for (int i = 0; i < m_maxParticle; i++)
	{

		// 比較用の現在の位置
		Vector3 absPosition = Vector3(
			abs(m_3dParticle[i]._sprite->property._transform._translation._x),
			abs(m_3dParticle[i]._sprite->property._transform._translation._y),
			abs(m_3dParticle[i]._sprite->property._transform._translation._z));

		float absPositionLength = absPosition.GetVectorLength();
		Vector3 nowParticlePosition = m_3dParticle[i]._sprite->property._transform._translation;
		// 限界地点
		Vector3 border = Vector3(
			abs((m_direction._x) * m_maxActiveLength),
			abs((m_direction._y) * m_maxActiveLength),
			abs((m_direction._z) * m_maxActiveLength));
		
		// 正確な破棄する地点
		Vector3 kill = border + m_3dParticle[i]._sprite->property._transform._translation;
		float killBorderLength = kill.GetVectorLength();
		if ((m_3dParticle[i]._active == true) &&
			(absPositionLength>killBorderLength))
		{
			m_3dParticle[i]._active = false;
			m_currentParticleCount--;

			// Now shift all the live particles back up the array to erase the destroyed particle and keep the array sorted correctly.
			for (int j = i; j < m_maxParticle - 1; j++)
			{
				m_3dParticle[j]._sprite->property._transform._translation._x = m_3dParticle[j + 1]._sprite->property._transform._translation._x;
				m_3dParticle[j]._sprite->property._transform._translation._y = m_3dParticle[j + 1]._sprite->property._transform._translation._y;
				m_3dParticle[j]._sprite->property._transform._translation._z = m_3dParticle[j + 1]._sprite->property._transform._translation._z;
				m_3dParticle[j]._sprite->property._color._red = m_3dParticle[j + 1]._sprite->property._color._red;
				m_3dParticle[j]._sprite->property._color._green = m_3dParticle[j + 1]._sprite->property._color._green;
				m_3dParticle[j]._sprite->property._color._blue = m_3dParticle[j + 1]._sprite->property._color._blue;
				m_3dParticle[j]._velocity = m_3dParticle[j + 1]._velocity;
				m_3dParticle[j]._active = m_3dParticle[j + 1]._active;
			
			}
		}
	}
	return;
}

//
void Particle::SetActiveLength(const float activeLength){
	m_maxActiveLength = activeLength;
}

//
void Particle::SetRange(Vector3 min, Vector3 max){
	m_minRange = min;
	m_maxRange = max;

	return;
}

//
void Particle::SetPosition(Vector3 position){
	m_particlePosition = position;
	return;
}