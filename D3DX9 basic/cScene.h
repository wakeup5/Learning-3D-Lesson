#pragma once
class cScene
{
private:
	

public:
	cScene(void);
	~cScene(void);

	//4총사함수를 추상함수로......
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update( float timeDelta ) = 0;
	virtual void Render() = 0;

private:
};

