#include"dglib2.h"
#include<time.h>
#include<math.h>
#include"Program\�}�N�����\����.h"
#include"Program\Stage.h"
#include"Program\Boss.h"
#include"Program\Enemy.h"
#include"Program\Player.h"
#include"Program\�֐�.h"
#include"Program\Robee.h"
#include"Program\Proc.h"

main()
{
	int eflg = 0;
	int *ef;
	ef = &eflg;

	dg_setscreen(0, 0, 1, 1, 0, "Auto Gear");
	if (MessageBox(NULL, "�t���X�N���[���ɂ��܂����H", "�m�F", MB_YESNO) == IDYES) {
		dg_setscreen(0, 0, 1280, 720, 2, "");
	}
	else {
		dg_setscreen(0, 0, 1280, 720, 0, "Auto Gear");
	}
	bb = dg_createBB();	//�o�b�N�o�b�t�@�ϐ��錾

	do {
		if (eflg == 0) { TitleProc(ef); }
		if (eflg == 1) {
			m = 1;
			GameProc(ef);
		}
		if (eflg == 2) {
			m = 2;
			BossProc(ef);
		}
		if (eflg == 99) { GameOver(ef); }
	} while (eflg != 999);
	/*�㏈��*/
	dg_deleteBB(bb);
}