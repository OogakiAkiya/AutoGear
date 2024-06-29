#include"dglib2.h"
#include<time.h>
#include<math.h>
#include"Program\マクロ＆構造体.h"
#include"Program\Stage.h"
#include"Program\Boss.h"
#include"Program\Enemy.h"
#include"Program\Player.h"
#include"Program\関数.h"
#include"Program\Robee.h"
#include"Program\Proc.h"

main()
{
	int eflg = 0;
	int *ef;
	ef = &eflg;

	dg_setscreen(0, 0, 1, 1, 0, "Auto Gear");
	if (MessageBox(NULL, "フルスクリーンにしますか？", "確認", MB_YESNO) == IDYES) {
		dg_setscreen(0, 0, 1280, 720, 2, "");
	}
	else {
		dg_setscreen(0, 0, 1280, 720, 0, "Auto Gear");
	}
	bb = dg_createBB();	//バックバッファ変数宣言

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
	/*後処理*/
	dg_deleteBB(bb);
}