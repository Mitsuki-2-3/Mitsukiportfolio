#pragma once
#include"common.h"
#include"C3DPrism.h"

#define D_RADIAN 0.0174533f

class C3DSphere
{
private:
	VECTOR nowWorldPosi;		//���W
	VECTOR moveVector;			//�ړ���

	ST_Angle localAngle;		//�X��(���쒆)
	float radius;				//���a

	float gravity;				//�d��

	bool friction;				//���C(��)��ON/OFF
public:
	C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle);

	void Updata();			//�X�V

	void Draw()const;		//�`��

	VECTOR GetNowPosition() { return nowWorldPosi; }			//���W�̎擾
	VECTOR GetMoveVector() { return moveVector; }				//�ړ��ʂ̎擾
	void CheckHitWall(C3DPrism* data);							//�ǂƂ̓����蔻�菈��
	void CheckHitFloor(C3DPrism* data);							//���Ƃ̓����蔻�菈��
	bool CheckHitItem(C3DPrism* data);							//�A�C�e���擾����
	float GetRadius() { return radius; }						//���a�̎擾
	void SetNowPosi(VECTOR _data) { nowWorldPosi = _data; }		//���W�̏㏑��
};

