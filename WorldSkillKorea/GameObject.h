#pragma once
#include "VertexArray.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject() = delete;
	GameObject(GameObject&) = delete;
	GameObject(ID3D11Device* device, Texture* texture, float width, float height);
	virtual ~GameObject();

	virtual void draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) final;
	virtual void update(float deltaTime) = 0;

protected:
	virtual void setPosition(float x, float y, float z);
	virtual XMFLOAT3 getPosition() const;
	
	virtual void setAngle(float angle);
	virtual float getAngle() const;

	virtual void setScale(float x, float y);
	virtual XMFLOAT2 getScale() const;

	virtual void setTexture(Texture* texture);

private:
	void createMatrixBuffer(ID3D11Device* device);
	void fillMatrixBuffer(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix);

private:
	XMFLOAT3 m_Position;
	XMFLOAT2 m_Scale;
	float m_Angle;
	ID3D11Buffer* m_MatrixBuffer;
	VertexArray* m_VertexArray;
	Texture* m_Texture;
};