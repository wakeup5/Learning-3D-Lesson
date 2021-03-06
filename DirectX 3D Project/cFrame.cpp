#include "StdAfx.h"
#include "cFrame.h"

cFrame::cFrame(void)
	: m_pMtlTex(NULL)
	, m_pVB(NULL)
	, m_nNumTri(0)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cFrame::~cFrame(void)
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVB);
}

void cFrame::Update( int nKeyFrame, D3DXMATRIXA16* pmatParent )
{
	D3DXMATRIXA16 matR, matT;
	CalcLocalR(nKeyFrame, matR);
	CalcLocalT(nKeyFrame, matT);
	m_matLocalTM = matR * matT;

	m_matWorldTM = m_matLocalTM;
	if(pmatParent)
	{
		m_matWorldTM *= (*pmatParent);
	}

	for each(auto c in m_vecChild)
	{
		c->Update(nKeyFrame, &m_matWorldTM);
	}
}

void cFrame::Render()
{
	if(m_pMtlTex)
	{
		DEVICE->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		//DEVICE->SetTexture(0, m_pMtlTex->GetTexture());
		//DEVICE->SetTexture(0, NULL);
		DEVICE->SetMaterial(&m_pMtlTex->GetMaterial());
		//DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
		DEVICE->SetFVF(PNT_VERTEX::FVF);

		DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(PNT_VERTEX));
		DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);
		/*
		DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 
			m_vecVertex.size() / 3, 
			&m_vecVertex[0], 
			sizeof(PNT_VERTEX));
		*/
		//DEVICE->SetTexture(0, NULL);
	}
	

	for each(auto c in m_vecChild)
	{
		c->Render();
	}
}

void cFrame::AddChild( cFrame* pChild )
{
	m_vecChild.push_back(pChild);
}

void cFrame::Destroy()
{
	for each(auto c in m_vecChild)
	{
		c->Destroy();
	}
	this->Release();
}

void cFrame::CalcOriginLocalTM( D3DXMATRIXA16* pmatParent )
{
	// WTM = LTM * PWTM
	// LTM = WTM * InvPWTM
	m_matLocalTM = m_matWorldTM;
	if(pmatParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, 0, pmatParent);
		m_matLocalTM = m_matWorldTM * matInvParent;
	}

	for each(auto c in m_vecChild)
	{
		c->CalcOriginLocalTM(&m_matWorldTM);
	}
}

void cFrame::CalcLocalT( IN int nKeyFrame, OUT D3DXMATRIXA16& matT )
{
	D3DXMatrixIdentity(&matT);
	if (m_vecPosTrack.empty())
	{
		matT._41 = m_matLocalTM._41;
		matT._42 = m_matLocalTM._42;
		matT._43 = m_matLocalTM._43;
		return;
	}
	
	if(nKeyFrame <= m_vecPosTrack.front().n)
	{
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;
	}

	if(nKeyFrame >= m_vecPosTrack.back().n)
	{
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return;
	}

	int nNextIndex = 0;
	for (size_t i = 0; i < m_vecPosTrack.size(); ++i)
	{
		if(nKeyFrame < m_vecPosTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecPosTrack[nPrevIndex].n) / 
		(float)(m_vecPosTrack[nNextIndex].n - m_vecPosTrack[nPrevIndex].n);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].v, &m_vecPosTrack[nNextIndex].v, t);
	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

void cFrame::CalcLocalR( IN int nKeyFrame, OUT D3DXMATRIXA16& matR )
{
	D3DXMatrixIdentity(&matR);
	if (m_vecRotTrack.empty())
	{
		matR = m_matLocalTM;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}

	if(nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}

	if(nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nNextIndex = 0;
	for (size_t i = 0; i < m_vecRotTrack.size(); ++i)
	{
		if(nKeyFrame < m_vecRotTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecRotTrack[nPrevIndex].n) / 
		(float)(m_vecRotTrack[nNextIndex].n - m_vecRotTrack[nPrevIndex].n);

	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrevIndex].q, &m_vecRotTrack[nNextIndex].q, t);
	D3DXMatrixRotationQuaternion(&matR, &q);
}

void cFrame::BuildVB(std::vector<PNT_VERTEX> &vecVertex)
{
	m_nNumTri = vecVertex.size() / 3;

	DEVICE->CreateVertexBuffer(vecVertex.size() * sizeof(PNT_VERTEX), 0, PNT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);

	PNT_VERTEX* pV = NULL;

	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0); //LPVOID;

	memset(pV, NULL, sizeof(PNT_VERTEX) * vecVertex.size());
	for (int i = 0; i < vecVertex.size(); i++)
	{
		pV[i] = PNT_VERTEX(vecVertex[i]);
	}

	m_pVB->Unlock();
}