#include "StdAfx.h"
#include "cScene.h"


cScene::cScene(void)
{
}


cScene::~cScene(void)
{
}


/*

void cScene::Init()
{
	//���������� �ִ�
	m_VerticesLocal[0] = D3DXVECTOR3( -0.5f,  0.5f,  0.0f );
	m_VerticesLocal[1] = D3DXVECTOR3(  0.5f,  0.5f,  0.0f );
	m_VerticesLocal[2] = D3DXVECTOR3(  0.5f,  0.5f,  0.0f );
	m_VerticesLocal[3] = D3DXVECTOR3(  0.5f, -0.5f,  0.0f );
	m_VerticesLocal[4] = D3DXVECTOR3(  0.5f, -0.5f,  0.0f );
	m_VerticesLocal[5] = D3DXVECTOR3( -0.5f, -0.5f,  0.0f );
	m_VerticesLocal[6] = D3DXVECTOR3( -0.5f, -0.5f,  0.0f );
	m_VerticesLocal[7] = D3DXVECTOR3( -0.5f,  0.5f,  0.0f );


	m_Angle = 0.0f;

}

void cScene::Release()
{
}

void cScene::Update( float timeDelta )
{
	//�ޱ۰� ���� 
	m_Angle += ( 90.0f * ONE_RAD ) * timeDelta;

	//�ޱ۰��� ���� ȸ����� �غ�
	D3DXMATRIXA16 matRotation;
	D3DXVECTOR3 axis( 0, 0, 1 );
	D3DXMatrixRotationAxis( &matRotation, &axis, m_Angle );

	//ȸ�� ��� ����
	for( int i = 0 ; i < 8 ; i++ )
	{
		//D3DXVec3TransformCoord( &m_VerticesFinal[i], &m_VerticesLocal[i], &matRotation );
		D3DXVec3TransformNormal( &m_VerticesFinal[i], &m_VerticesLocal[i], &matRotation );

	}

}

void cScene::Render( HDC hdc )
{
	
	this->DrawVerticeLine( hdc, m_VerticesFinal, 8 );

}


*/
