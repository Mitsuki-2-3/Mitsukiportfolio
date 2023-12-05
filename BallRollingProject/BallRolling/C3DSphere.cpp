#include "C3DSphere.h"
#include "CheckHit.h"
#include <iostream>
#include <cmath>

C3DSphere::C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle)
{
	//À•W
	nowWorldPosi = firstposi;
	//”¼Œa
	radius = _radius;
	//ŒX‚«
	localAngle = _angle;
	//d—Í
	gravity = -0.1f;
	//ˆÚ“®—Ê‚Ì‰Šú‰»
	moveVector = VGet(0,0,0);

	//‚È‚ñ‚¿‚á‚Á‚Ä–€C‚ÌON/OFF
	friction = false;	
}

void C3DSphere::Updata()
{
	//ˆÚ“®—Ê‚Éd—Í‚Ì’Ç‰Á
	moveVector.y += gravity;

	//ŒÃ‚¢À•W‚ÖŒ»İ‚ÌˆÚ“®—Ê‚Ì‰ÁZ
	nowWorldPosi += moveVector;

	////‚È‚ñ‚¿‚á‚Á‚Ä–€C
	if (friction) {
		moveVector -= moveVector * 0.02f;
	}
}

void C3DSphere::Draw() const
{
	//‹…‚Ì•`‰æ
	DrawSphere3D(nowWorldPosi, radius, 32, 0x0000FF, 0x00ff00, TRUE);
}

//•Ç‚Æ‚Ì“–‚½‚è”»’èˆ—
void C3DSphere::CheckHitWall(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };
	//—§•û‘Ì‚Æ‚Ì“–‚½‚è”»’è
	hit1 = Check3DQuadrangularPrism(data, this);
	//‚±‚±‚Å“–‚½‚è”»’è‚Æ“–‚½‚Á‚½‚ÌÀ•W
	if (hit1.hit == true)
	{
		//“–‚½‚Á‚½‚çˆÚ“®—Ê‚ğ‹t‚É‚µ‚Ä’µ‚Ë•Ô‚·
		moveVector = moveVector - (hit1.normalize * VDot(moveVector, hit1.normalize) * 1.15f);
		//‚±‚±‚Å‚ß‚è‚İ–h~
		saves1 = (hit1.hitposi + hit1.normalize * (GetRadius() / 100.0f)) - nowWorldPosi;
		//‚ß‚è‚ñ‚Å‚é•ª–ß‚·
		nowWorldPosi += saves1;
	}

}

//°‚Æ‚Ì“–‚½‚è”»’èˆ—
void C3DSphere::CheckHitFloor(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };

	hit1 = Check3DQuadrangularPrism(data, this);
	//‚±‚±‚Å“–‚½‚è”»’è‚Æ“–‚½‚Á‚½‚ÌÀ•W
	if (hit1.hit == true)
	{
		//“–‚½‚Á‚½‚çˆÚ“®—Ê‚ğ‹t‚É‚·‚é
		moveVector = moveVector - (hit1.normalize * VDot(moveVector, hit1.normalize));
		//‚±‚±‚Å‚ß‚è‚İ–h~
		saves1 = (hit1.hitposi) - nowWorldPosi;
		//‚ß‚è‚ñ‚Å‚é•ª–ß‚·
		nowWorldPosi += saves1;
	}
}

bool C3DSphere::CheckHitItem(C3DPrism* data)
{
	//ƒAƒCƒeƒ€‚Æ‚Ìˆ—
	if (OBBPrism(data, this))
	{
		DrawString(200, 200, "HIT ITEM", 0xffffff);
		return true;
	}
	return false;
}

