//マップ関数
void DrawStage(char *p_map, char_far MapChip, char_far Objectbmp, int stx, int sty, char_far *map_bmp, char_far Move_Floor, ENEMY *e, int *mfx, int *mfy);

void MapOpen(char **map);

//ステージ当たり判定関数
int StageCollision_LR(char *p_map, int *stx, int *sty, short *px, float *py, int k);
int StageCollision_UD(char *p_map, int *stx, int *sty, short *px, float *py, int k, int k2, int *BossStageFlag);

//マップアニメーション
void Animation(int *stx, int *sty, char_far map_bmp, IMG img, int kamerastart1, int kameraend1, int kamerastart2, int kameraend2, int kamerastart3, int kameraend3, float *ScrollCnt);
//フェード
void Fade(char_far map_bmp, IMG img, int x, int y, int flag, float *ScrollCnt);
//ギミック
void Gimmick(int sc, int *pjumpflg, char *p_map, int *stx, int *sty, char *life, int k, short kf, int k2, short k2f);
void Floor_Gimmick(int *k, short *kf, int *k2, short *k2f);
void GimmickDrawStage(char *p_map, char_far MapChip, char_far Objectbmp, char_far Move_Floor, int stx, int sty, int k, int *mfx, int *mfy, int k2);


//マップ関数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void DrawStage(char *p_map, char_far MapChip, char_far Objectbmp, int stx, int sty, char_far *map_bmp, char_far Move_Floor, ENEMY *e, int *mfx, int *mfy) {
	int i, j, k = 0, l = ENEMY_CNT;
	short s = 0;
	*map_bmp = dg_createbmp(BlockSIZE*StageW, BlockSIZE*(StageH + 5));
	dg_box(*map_bmp, 0, 0, BlockSIZE*StageW, BlockSIZE*(StageH + 5), 1, RGB(0, 0, 0));
	for (i = -StageMARGIN; i < StageH + StageMARGIN; i++) {
		for (j = -StageMARGIN; j < StageW + StageMARGIN; j++) {
			if (i < 0 || i >= StageH ||
				j < 0 || j >= StageW)
			{
				dg_drawbmp2(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 128);
			}
			else
			{
				switch (*(p_map + (StageW*i + j))) {

					// 足場のブロック==========================================
				case 0:
					break;
				case 2:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 0, 0, RGB(255, 0, 255));
					break;
				case 3:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 0, RGB(255, 0, 255));
					break;
				case 4:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 128, 0, RGB(255, 0, 255));
					break;
				case 5:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 192, 0, RGB(255, 0, 255));
					break;
				case 6:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 0, 64, RGB(255, 0, 255));
					break;
				case 7:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 64, RGB(255, 0, 255));
					break;
				case 8:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 128, 64, RGB(255, 0, 255));
					break;
				case 9:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 192, 64, RGB(255, 0, 255));
					break;
				case 10:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 0, 128, RGB(255, 0, 255));
					break;
				case 11:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 128, RGB(255, 0, 255));
					break;
				case 12:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 128, 128, RGB(255, 0, 255));
					break;
				case 13:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 192, 128, RGB(255, 0, 255));
					break;
				case 14:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 0, 192, RGB(255, 0, 255));
					break;
				case 15:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 192, RGB(255, 0, 255));
					break;
				case 16:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 128, 192, RGB(255, 0, 255));
					break;
				case 17:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 192, 192, RGB(255, 0, 255));
					break;
				case 18:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 0, 256, RGB(255, 0, 255));
					break;
				case 19:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 0, 320, RGB(255, 0, 255));
					break;
					// =====================================================
				case 20:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, Objectbmp, 192, 0, RGB(255, 0, 255));
					break;
				case 23:dg_box(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, 1, RGB(185, 160, 170));
					break;
				case 24:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 256, RGB(255, 0, 255));
					break;
				case 27:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 0, RGB(255, 0, 255));
					break;
				case 28:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 64, RGB(255, 0, 255));
					break;
				case 29:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 0, RGB(255, 0, 255));
					break;
				case 30:(e + k)->x = j * 64;
					(e + k)->y = ((i + 1) * BlockSIZE + BlockSIZE - 2680);
					k++;
					break;
				case 33:(e + l)->x = j * 64;
					(e + l)->y = ((i + 1) * BlockSIZE + ENEMY_H - 2680);
					l++;
					break;
				case 34:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, Objectbmp, 192, 0, RGB(255, 0, 255));
					break;
				case 36:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 0, RGB(255, 0, 255));
					break;
				case 37:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 64, RGB(255, 0, 255));
					break;
				case 38:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, Objectbmp, 192, 0, RGB(255, 0, 255));
					break;
				case 40:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 0, RGB(255, 0, 255));
					break;
				case 41:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, MapChip, 64, 64, RGB(255, 0, 255));
					break;
				case 42:dg_drawbmp3(*map_bmp, (j*BlockSIZE), s + ((i + 1)*BlockSIZE), BlockSIZE, BlockSIZE, Objectbmp, 192, 0, RGB(255, 0, 255));
					break;
				}
			}
		}
	}
}

void MapOpen(char **map)
{
	int i, j;
	FILE *fp;

	fopen_s(&fp, "map/map.txt", "r");
	if (fp == NULL) { return; }
	for (i = 0; i < StageH; i++) {
		for (j = 0; j < StageW; j++) {
			map[i][j] = fgetc(fp);
		}
	}

	fclose(fp);
	return;
}
//------------------------------------------------------------------------------------------------------------

//ステージ当たり判定関数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
int StageCollision_LR(char *p_map, int *stx, int *sty, short *px, float *py, int k) {
	int left = ((-(*stx) + (int)*px + CharaMARGIN) / 64);
	int right = ((-(*stx) + (int)*px + PlayerW - CharaMARGIN) / 64);
	int up = ((49 - (-(*sty) + PlayerH) / 64) * StageW);
	int down = ((49 - (-(*sty) + 64) / 64) * StageW);
	// 回復ボックス横判定
	if ((*(p_map + (left + up))) == 29 ||
		(*(p_map + (left + down))) == 29)
	{
		return 3;
	}
	if ((*(p_map + (left + up))) == 29 * 2 ||
		(*(p_map + (left + down))) == 29 * 2)
	{
		return 4;
	}
	if ((*(p_map + (left + up))) == 29 * 3 ||
		(*(p_map + (left + down))) == 29 * 3)
	{
		return 5;
	}
	if ((*(p_map + (left + up))) == 29 * 4 ||
		(*(p_map + (left + down))) == 29 * 4)
	{
		return 6;
	}
	if ((*(p_map + (right + up))) == 29 ||
		(*(p_map + (right + down))) == 29)
	{
		return 3;
	}
	if ((*(p_map + (right + up))) == 29 * 2 ||
		(*(p_map + (right + down))) == 29 * 2)
	{
		return 4;
	}
	if ((*(p_map + (right + up))) == 29 * 3 ||
		(*(p_map + (right + down))) == 29 * 3)
	{
		return 5;
	}
	if ((*(p_map + (right + up))) == 29 * 4 ||
		(*(p_map + (right + down))) == 29 * 4)
	{
		return 6;
	}
	// 左判定
	if ((*(p_map + (left + up))) == 9 ||
		(*(p_map + (left + down))) == 9)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 13 ||
		(*(p_map + (left + down))) == 13)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 17 ||
		(*(p_map + (left + down))) == 17)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 13 ||
		(*(p_map + (left + down))) == 13)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 50 ||
		(*(p_map + (left + down))) == 50)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 43 ||
		(*(p_map + (left + down))) == 43)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 30 ||
		(*(p_map + (left + down))) == 30)
	{
		return 0;
	}
	else if ((*(p_map + (left - (k / 64) + up))) == 31 ||
		(*(p_map + (left - (k / 64) + down))) == 31)
	{
		return 1;
	}
	else if ((*(p_map + (left + up))) == 31 ||
		(*(p_map + (left + down))) == 31)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 33 ||
		(*(p_map + (left + down))) == 33)
	{
		return 0;
	}
	else if ((*(p_map + (left + up))) == 44 ||
		(*(p_map + (left + down))) == 44)
	{
		return 0;
	}
	else if ((*(p_map + (left + up)))> 5 ||
		(*(p_map + (left + down)))> 5)
	{
		return 1;
	}
	// 右判定
	if ((*(p_map + (right + up))) == 9 ||
		(*(p_map + (right + down))) == 9)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 13 ||
		(*(p_map + (right + down))) == 13)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 17 ||
		(*(p_map + (right + down))) == 17)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 18 ||
		(*(p_map + (right + down))) == 18)
	{
		return 0;
	}

	else if ((*(p_map + (right + up))) == 30 ||
		(*(p_map + (right + down))) == 30)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 44 ||
		(*(p_map + (right + down))) == 44)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 50 ||
		(*(p_map + (right + down))) == 50)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 43 ||
		(*(p_map + (right + down))) == 43)
	{
		return 0;
	}
	else if ((*(p_map + (right - (k / 64) + up))) == 31 ||
		(*(p_map + (right - (k / 64) + down))) == 31)
	{
		return 2;
	}
	else if ((*(p_map + (right + up))) == 31 ||
		(*(p_map + (right + down))) == 31)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 33 ||
		(*(p_map + (right + down))) == 33)
	{
		return 0;
	}
	else if ((*(p_map + (right + up))) == 32 ||
		(*(p_map + (right + down))) == 32)
	{
		return 0;
	}
	else if ((*(p_map + (right + up)))>5 ||
		(*(p_map + (right + down)))>5)
	{
		return 2;
	}
	return 0;
}

int StageCollision_UD(char *p_map, int *stx, int *sty, short *px, float *py, int k, int k2, int *BossStageFlag) {
	int left = ((-(*stx) + (int)*px + CharaMARGIN) / 64);
	int right = ((-(*stx) + (int)*px + 64) / 64);
	int right2 = ((-(*stx) + (int)*px + PlayerW - CharaMARGIN) / 64);
	int up = ((49 - (-(*sty) + PlayerH + 64 - CharaMARGIN) / 64) * StageW);
	int down = ((49 - (-(*sty) + 64) / 64) * StageW);

	if ((*(p_map + ((left + up)))) == 44 ||
		(*(p_map + ((right + up)))) == 44 ||
		(*(p_map + ((right2 + up)))) == 44)
	{
		*BossStageFlag = 1;
	}
	if (*(p_map + (left + down)) == 44 ||
		*(p_map + (right + down)) == 44 ||
		*(p_map + (right2 + down)) == 44)
	{
		*BossStageFlag = 1;
	}
	if (*(p_map + (left + down)) == 20 ||
		*(p_map + (right + down)) == 20 ||
		*(p_map + (right2 + down)) == 20)
	{
		return 10;
	}
	if (*(p_map + (left + down)) == 34 ||
		*(p_map + (right + down)) == 34 ||
		*(p_map + (right2 + down)) == 34)
	{
		return 14;
	}
	if (*(p_map + (left + down)) == 38 ||
		*(p_map + (right + down)) == 38 ||
		*(p_map + (right2 + down)) == 38)
	{
		return 15;
	}
	if (*(p_map + (left + down)) == 19 ||
		*(p_map + (right + down)) == 19 ||
		*(p_map + (right2 + down)) == 19)
	{
		return 4;
	}
	//ベルコン右
	if (*(p_map + (left + down)) == 42 ||
		*(p_map + (right + down)) == 42 ||
		*(p_map + (right2 + down)) == 42)
	{
		return 7;
	}
	//ベルコン左
	else if (*(p_map + (left + down)) == 23 ||
		*(p_map + (right + down)) == 23 ||
		*(p_map + (right2 + down)) == 23)
	{
		return 8;
	}

	else if (*(p_map + (left + down)) == 29 ||
		*(p_map + (right + down)) == 29 ||
		*(p_map + (right2 + down)) == 29)
	{
		return 11;
	}
	else if (*(p_map + (left + down)) == 29 * 2 ||
		*(p_map + (right + down)) == 29 * 2 ||
		*(p_map + (right2 + down)) == 29 * 2)
	{
		return 17;
	}
	else if (*(p_map + (left + down)) == 29 * 3 ||
		*(p_map + (right + down)) == 29 * 3 ||
		*(p_map + (right2 + down)) == 29 * 3)
	{
		return 18;
	}
	else if (*(p_map + (left + down)) == 29 * 4 ||
		*(p_map + (right + down)) == 29 * 4 ||
		*(p_map + (right2 + down)) == 29 * 4)
	{
		return 19;
	}
	else if (*(p_map + (left + down)) == 18 ||
		*(p_map + (right + down)) == 18 ||
		*(p_map + (right2 + down)) == 18)
	{
		return 0;
	}

	else if (*(p_map + (left + down)) == 30 ||
		*(p_map + (right + down)) == 30 ||
		*(p_map + (right2 + down)) == 30)
	{
		return 0;
	}
	else if (*(p_map + (left + down)) == 50 ||
		*(p_map + (right + down)) == 50 ||
		*(p_map + (right2 + down)) == 50)
	{
		return 0;
	}
	else if (*(p_map + (left + down)) == 43 ||
		*(p_map + (right + down)) == 43 ||
		*(p_map + (right2 + down)) == 43)
	{
		return 0;
	}
	else if (*(p_map + (left + down)) == 33 ||
		*(p_map + (right + down)) == 33 ||
		*(p_map + (right2 + down)) == 33)
	{
		return 0;
	}
	else if (*(p_map + (left - (k / 64) + down)) == 31 ||
		*(p_map + (right - (k / 64) + down)) == 31 ||
		*(p_map + (right2 - (k / 64) + down)) == 31)
	{
		return 12;
	}

	else if (*(p_map + (left + down)) == 31 ||
		*(p_map + (right + down)) == 31 ||
		*(p_map + (right2 + down)) == 31)
	{
		return 0;
	}
	else if (*(p_map + (left + down)) == 32 ||
		*(p_map + (right + down)) == 32 ||
		*(p_map + (right2 + down)) == 32)
	{
		return 0;
	}

	//ただの床
	if ((*(p_map + ((left + down))))>5 && !(*(p_map + ((left + down))) == 44) ||
		(*(p_map + ((right + down))))>5 && !(*(p_map + ((right + down))) == 44) ||
		(*(p_map + ((right2 + down))))>5 && !(*(p_map + ((right2 + down))) == 44))
	{
		if ((*(p_map + ((left + down)))) == 9)
		{
			return 0;
		}
		else if ((*(p_map + ((left + down)))) == 13)
		{
			return 0;
		}
		else if ((*(p_map + ((left + down)))) == 17)
		{
			return 0;
		}

		return 4;
	}
	if ((*(p_map + ((left + up)))) == 30 ||
		(*(p_map + ((right + up)))) == 30 ||
		(*(p_map + ((right2 + up)))) == 30)
	{
		return 0;
	}
	if ((*(p_map + ((left - (k / 64) + up)))) == 31 ||
		(*(p_map + ((right - (k / 64) + up)))) == 31 ||
		(*(p_map + ((right2 - (k / 64) + up)))) == 31)
	{
		return 3;
	}
	else if (*(p_map + (left - (k / 64) + down)) == 900 ||
		*(p_map + (right - (k / 64) + down)) == 900 ||
		*(p_map + (right2 - (k / 64) + down)) == 900)
	{
		return 12;
	}
	if ((*(p_map + ((left + up)))) == 31 ||
		(*(p_map + ((right + up)))) == 31 ||
		(*(p_map + ((right2 + up)))) == 31)
	{
		return 0;
	}
	if ((*(p_map + ((left + up)))) == 32 ||
		(*(p_map + ((right + up)))) == 32 ||
		(*(p_map + ((right2 + up)))) == 32)
	{
		return 0;
	}
	if ((*(p_map + ((left + up)))) == 50 ||
		(*(p_map + ((right + up)))) == 50 ||
		(*(p_map + ((right2 + up)))) == 50)
	{
		return 0;
	}
	if ((*(p_map + ((left + up)))) == 43 ||
		(*(p_map + ((right + up)))) == 43 ||
		(*(p_map + ((right2 + up)))) == 43)
	{
		return 0;
	}
	if ((*(p_map + ((left + up)))) == 33 ||
		(*(p_map + ((right + up)))) == 33 ||
		(*(p_map + ((right2 + up)))) == 33)
	{
		return 0;
	}
	if ((*(p_map + ((left + up)))) > 5 && !(*(p_map + ((left + up))) == 44) ||
		(*(p_map + ((right + up))))>5 && !(*(p_map + ((right + up))) == 44) ||
		(*(p_map + ((right2 + up))))>5 && !(*(p_map + ((right2 + up))) == 44))
	{

		if ((*(p_map + ((left + up)))) == 9)
		{
			return 0;
		}
		else if ((*(p_map + ((left + up)))) == 13)
		{
			return 0;
		}
		else if ((*(p_map + ((left + up)))) == 17)
		{
			return 0;
		}
		return 3;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------------------


//マップアニメーション
void Animation(int *stx, int *sty, char_far map_bmp, IMG img, int kamerastart1, int kameraend1, int kamerastart2, int kameraend2, int kamerastart3, int kameraend3,float *ScrollCnt)
{
	int x = kamerastart1;
	int flag = 0;
	float height = 0;
	int  cnt = 100;
	float c = 100;
	char fadeflg = 0;

	//FPS制御
	unsigned long starttime;
	starttime = NOW;
	int static unsigned long st = 0, fpscnt = 0, scnt = 0;

	while (1) {
		c -= 0.1;
		if (c < 0) { fadeflg = 1; }



		//画面クリア
		dg_drawbmp2(bb, 0, 0, MapWIDTH, MapHEIGHT, img.Background, *ScrollCnt, 0);

		//FPS制御
		if (NOW - starttime < 1000 / 60) { continue; }
		starttime = NOW;
		if (NOW - st > 1000) {
			scnt = fpscnt;
			st = NOW;
			fpscnt = 0;
		}

		if (fadeflg == 1) {
			//画面上下の黒枠
			if (height <= 80 && flag == 0) {
				height += 1;
			}
			else {
				if (flag == 0) { flag = 1; }
			}

			//シーンチェンジ１
			if (flag == 1 && x < kameraend1) {
				x += 1;
				*ScrollCnt += 0.5;
				if (x == kameraend1) {
					Fade(map_bmp, img, x, *sty, 1,&*ScrollCnt);//最後の１はシーンチェンジにFadeを使うときのみ書く
					x = kamerastart2;
					flag = 2;
				}
			}

			//シーンチェンジ2
			if (flag == 2 && x < kameraend2) {
				*sty = -400;
				x += 1;
				*ScrollCnt += 0.5;
				cnt -= 3;//フェードインの速さ調節
				if (x == kameraend2) {
					Fade(map_bmp, img, x, *sty, 1, &*ScrollCnt);
					cnt = 100;
					x = kamerastart3;
					flag = 3;
				}
			}
			//シーンチェンジ3
			if (flag == 3 && x < kameraend3) {
				cnt -= 3;//フェードインの速さ調節
				x += 1;
				*ScrollCnt += 0.5;
				*sty -= 1;
				if (x == kameraend3) {
					flag = 4;
				}
			}

		}

		//マップ描画
		dg_drawbmp3(bb, 0, 0, 1280, 720, map_bmp, x, *sty + 2680, RGB(0, 0, 0));
		if (flag == 2 || flag == 3 && cnt > 0) {
			dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, cnt, -1);
		}
		//上下の枠描画
		dg_box(bb, 0, 0, 1280, height, 1, RGB(0, 0, 0));
		dg_box(bb, 0, 720, 1280, -height, 1, RGB(0, 0, 0));

		if (height > 30) {
			dg_printf2(bb, 0, 0, RGB(255, 255, 255), -1, "Sでスキップ");
		}

		dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, c, -1);

		//break処理
		if (flag == 4) {
			Fade(map_bmp, img, x, *sty, 1, &*ScrollCnt);
			break;
		}
		if (getch3('S')) { break; }
		if (getch3(VK_ESCAPE)) { break; }

		dg_flip(gvram, bb);
		ML();
	}
	return;
}


//フェード＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Fade(char_far map_bmp, IMG img, int x, int y, int flag,float *ScrollCnt)
{
	float invisible = 0;
	int i = 0;
	int j = 0;
	//FPS制御
	unsigned long starttime;
	starttime = NOW;
	int static unsigned long st = 0, fpscnt = 0, scnt = 0;

	while (1) {
		*ScrollCnt += 0.05;
		//画面クリア
		dg_drawbmp2(bb, 0, 0, MapWIDTH, MapHEIGHT, img.Background, *ScrollCnt, 0);
		j++;
		if (j % 30 == 0) {
			i--;
		}
		//FPS制御
		if (NOW - starttime < 1000 / 60) { continue; }
		starttime = NOW;
		if (NOW - st > 1000) {
			scnt = fpscnt;
			st = NOW;
			fpscnt = 0;
		}

		//
		invisible += 0.8;

		//マップ描画
		dg_drawbmp3(bb, 0 + i, 0, 1280 - i, 720, map_bmp, x - i, y + 2680, RGB(0, 0, 0));
		dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, invisible, -1);

		//Animation処理の時のみ描画
		if (flag == 1) {
			dg_box(bb, 0, 0, 1280, 80, 1, RGB(0, 0, 0));
			dg_box(bb, 0, 720, 1280, -80, 1, RGB(0, 0, 0));
			dg_printf2(bb, 0, 0, RGB(255, 255, 255), -1, "Sでスキップ");

		}

		//break処理
		if (invisible>100) { break; }
		if (getch3('S')) { break; }
		if (getch3(VK_ESCAPE)) { break; }
		dg_flip(gvram, bb);
		ML();
	}
	return;

}
//--------------------------------------------------------------------------------------------------------------


//ギミック＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Gimmick(int sc, int *pjumpflg, char *p_map, int *stx, int *sty, char *life, int k, short kf, int k2, short k2f)
{
	int i;

	if (sc == 8)
	{
		*pjumpflg = 0;
		*sty = ((*sty - 64) / 64) * 64;
		*stx += 6;
	}
	else if (sc == 10)
	{
		ds_play1("sound/heavy-e02.wav");
		for (i = 0; i < 20000; i++)
		{
			
			if (*(p_map + i) == 25 ||*(p_map + i) == 20 || *(p_map + i) == 27)
			{
				*(p_map + i) = 0;
			}
			if (*(p_map + i) == 28)
			{
				*(p_map + i) = 11;
			}
		}
	}
	else if (sc == 11)
	{
		ds_play1("sound/magic-status-cure1.wav");
		*life += 2;
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 29)
			{
				*(p_map + i) = 0;
			}
		}
	}
	else if (sc == 17)
	{
		ds_play1("sound/magic-status-cure1.wav");
		*life += 2;
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 29 * 2)
			{
				*(p_map + i) = 0;
			}
		}
	}
	else if (sc == 18)
	{
		ds_play1("sound/magic-status-cure1.wav");
		*life += 2;
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 29 * 3)
			{
				*(p_map + i) = 0;
			}
		}
	}
	else if (sc == 19)
	{
		ds_play1("sound/magic-status-cure1.wav");
		*life += 2;
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 29 * 4)
			{
				*(p_map + i) = 0;
			}
		}
	}
	else if (sc == 12)
	{
		*pjumpflg = 0;
		*sty = ((*sty - 64) / 64) * 64;
		if (k >= 640) { kf = 1; }
		if (k <= 0) { kf = 0; }
		if (kf == 0)
		{
			*stx -= 5;
		}
		else {
			*stx += 5;
		}
	}
	else if (sc == 13)
	{
		*sty = ((*sty - 64) / 64) * 64;
		*pjumpflg = 0;
		if (k2 >= 640) { k2f = 1; }
		if (k2 <= 0) { k2f = 0; }
		if (k2f == 0)
		{
			*sty -= 5;
		}
		else {
			*sty += 5;
		}
	}
	else if (sc == 14)
	{
		ds_play1("sound/heavy-e02.wav");
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 34 || *(p_map + i) == 35 || *(p_map + i) == 36)
			{
				*(p_map + i) = 0;
			}
			if (*(p_map + i) == 37)
			{
				*(p_map + i) = 11;
			}
		}
	}
	else if (sc == 15)
	{
		ds_play1("sound/heavy-e02.wav");
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 38 || *(p_map + i) == 39 || *(p_map + i) == 40)
			{
				*(p_map + i) = 0;
			}
			if (*(p_map + i) == 41)
			{
				*(p_map + i) = 11;
			}
		}
	}

	return;
}

void Floor_Gimmick(int *k, short *kf, int *k2, short *k2f)
{

	if (*k >= 640)
	{
		*kf = 1;
	}
	if (*k <= 0)
	{
		*kf = 0;
	}
	if (*kf == 0)
	{
		*k += 5;
	}
	else {
		*k -= 5;
	}

	if (*k2 >= 640)
	{
		*k2f = 1;
	}
	if (*k2 <= 0)
	{
		*k2f = 0;
	}
	if (*k2f == 0)
	{
		*k2 += 5;
	}
	else {
		*k2 -= 5;
	}

	return;
}

void GimmickDrawStage(char *p_map, char_far MapChip, char_far Objectbmp, char_far Move_Floor, int stx, int sty, int k, int *mfx, int *mfy, int k2)
{
	int i, j;
	short RBi = 1;
	short Mf = 0;
	short Mff = 0;
	short Mfff = 0;

	short s = 0;
	for (i = -StageMARGIN; i < StageH + StageMARGIN; i++) {
		for (j = -StageMARGIN; j < StageW + StageMARGIN; j++) {
			if (i < 0 || i >= StageH ||
				j < 0 || j >= StageW)
			{

			}
			else
			{
				switch (*(p_map + (StageW*i + j))) {
				case 0:Mfff = 0;
					Mf = 0;
					break;
				case 20:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 0, RGB(255, 0, 255));
					break;
				case 25:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 320, RGB(255, 0, 255));
					break;
				case 27:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 384, RGB(255, 0, 255));
					break;
				case 28:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 448, RGB(255, 0, 255));
					break;
				case 29:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 192, RGB(255, 0, 255));
					*(p_map + (StageW*i + j)) = 29 * RBi;
					RBi++;
					break;
				case 31:*mfx = (j*BlockSIZE) + stx + k;
					*mfy = ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty);
					if (Mff == 0)
					{
						dg_drawbmp3(bb, *mfx, *mfy - BlockSIZE, 256, 128, Move_Floor, 0, 0, RGB(255, 0, 255));
					}
					Mff += 1;
					if (Mff == 5)
					{
						*(p_map + (StageW*i + j)) = 900;
					}
					break;
				case 34:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 0, RGB(255, 0, 255));
					break;
				case 35:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 320, RGB(255, 0, 255));
					break;
				case 36:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 384, RGB(255, 0, 255));
					break;
				case 37:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 448, RGB(255, 0, 255));
					break;
				case 38:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 0, RGB(255, 0, 255));
					break;
				case 39:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 320, RGB(255, 0, 255));
					break;
				case 40:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 384, RGB(255, 0, 255));
					break;
				case 41:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, MapChip, 64, 448, RGB(255, 0, 255));
					break;
				case 58:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 192, RGB(255, 0, 255));
					break;
				case 87:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 192, RGB(255, 0, 255));
					break;
				case 116:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 192, RGB(255, 0, 255));
					break;
				case 42:dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty), BlockSIZE, BlockSIZE, Objectbmp, 128, 0, RGB(255, 0, 255));
					break;
				case 22:
					if (Mfff == 0)
					{
						dg_drawbmp3(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty) - BlockSIZE, 256, 128, Move_Floor, 0, 0, RGB(255, 0, 255));
					}
					Mfff = 1;
					break;
				case 43:
					if (Mf == 0)
					{
						dg_drawbmp5(bb, (j*BlockSIZE) + stx, ((i + 1)*BlockSIZE) - (StageH * BlockSIZE - 520 + sty) - BlockSIZE, 256, 128, Move_Floor, 0, 0, 256, 128, 50, RGB(255, 0, 255));
					}
					Mf = 1;
					break;
				}
			}
		}
	}
	return;
}
//-------------------------------------------------------------------------------------------------------------
