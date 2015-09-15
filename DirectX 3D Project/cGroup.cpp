#include "StdAfx.h"
#include "cGroup.h"


cGroup::cGroup(void)
	: m_pMtlTex(NULL)
{
}

cGroup::~cGroup(void)
{
	SAFE_RELEASE(m_pMtlTex);
}

void cGroup::Render()
{
	if(m_pMtlTex)
	{
		DEVICE->SetTexture(0, m_pMtlTex->GetTexture());
		DEVICE->SetMaterial(&m_pMtlTex->GetMaterial());
	}
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	DEVICE->SetFVF(PNT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3, 
		&m_vecVertex[0], 
		sizeof(PNT_VERTEX));
}
