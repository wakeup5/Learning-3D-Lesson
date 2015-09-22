#pragma once

class cMtlTex : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Material);
	//SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	LPDIRECT3DTEXTURE9 m_pTexture;
public:
	cMtlTex(void);
	~cMtlTex(void);

	void SetTexture(LPDIRECT3DTEXTURE9 t)
	{
		//m_pTexture->Release();

		m_pTexture = t;
		m_pTexture->AddRef();
	}

	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_pTexture;
	}
};

