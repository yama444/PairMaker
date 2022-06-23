#include <windows.h>
#include "common.h"

int alpha = 0, add = 4 ;

int ChangeScreen(){
	if(alpha >= 255)
	{
		alpha = 0;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );
		return 1;
	}
	alpha += add;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha );
	return 0;
}
