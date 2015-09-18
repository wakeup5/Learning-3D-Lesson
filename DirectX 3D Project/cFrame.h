#pragma once

#include "cMtlTex.h"

class cFrame : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(std::vector<PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocalTM, LocalTM);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	std::vector<cFrame*> m_vecChild;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	int m_nNumTri;

public:
	cFrame(void);
	~cFrame(void);
	void Update(int nKeyFrame, D3DXMATRIXA16* pmatParent);
	void Render();
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalcOriginLocalTM(D3DXMATRIXA16* pmatParent);
	void CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matR);

	void BuildVB(std::vector<PNT_VERTEX> &vecVertex);
};

