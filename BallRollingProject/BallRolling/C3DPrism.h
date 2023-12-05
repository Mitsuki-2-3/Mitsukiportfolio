#pragma once
#include"common.h"

class C3DPrism
{
protected:
	VECTOR nowWorldPosi;		//���݂̃��[���h���W

	VECTOR nowParentPosi;		//���݂̐e�̍��W
	VECTOR nowChildPosi;		//���݂̐e���猩�����W

	VECTOR* polyPosi;			//�|���S���̒��_
	ST_Angle* worldAngle;
	ST_Angle localAngle;		//���݂̎O�����p�x

	float size[3];				//�傫��

	int poly;					//�|���S����

	VECTOR* polygonDATA;		//�|���S���̍��W�f�[�^

	VECTOR direct[3];			//���݂̌X���Ă��镪

	ST_Surfaces* surface;		//��

	//�ʂ̒��_�֌W
	int idx[36] = {
		// -z
		2,0,6,
		4,0,6,
		// +x
		3,2,7,
		6,2,7,
		// -x
		0,1,4,
		5,1,4,
		// +z
		1,3,5,
		7,3,5,
		// +y
		4,5,6,
		7,5,6,
		// -y
		2,3,0,
		1,3,0,
	};

	//�@��
	VECTOR no[6] = {
		 { 0.0f, 0.0f, -1.0f },
		 { 1.0f, 0.0f,  0.0f },
		 {-1.0f, 0.0f,  0.0f },
		 { 0.0f, 0.0f,  1.0f },
		 { 0.0f, 1.0f,  0.0f },
		 { 0.0f,-1.0f,  0.0f }
	};

public:
	C3DPrism(VECTOR parentposi,VECTOR localposi, ST_Angle* _worldangle,ST_Angle _localangle, VECTOR _size);

	~C3DPrism();

	virtual void Updata();
	void Draw(int i)const;

	VECTOR* GetPolyPosi() { return polyPosi; }
	VECTOR* Getdic() { return direct; }
	float* GetSize() { return size; }
	VECTOR GetNowPosi() { return nowWorldPosi; }
	ST_Angle GetAngle() { return localAngle; }
	ST_Surfaces* GetSuface() { return surface; }
};