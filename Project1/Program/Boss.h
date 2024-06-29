//ボス　マップ
void BossMapOpen(char **map);
//ボス
void Boss(IMG *img, char *map, BOSS *boss, PLAYER *player, int stx);//ボス移動
int BossCloss(BOSS *boss, PLAYER *player, int *stx, int *sty);//ボスと自機の当たり判定
void Direction(BOSS *boss, PLAYER *player, int stx);//ボス方向
void BossBomAtack(IMG *img, BOSS *boss, PLAYER *player, BOM *bom, int *stx, int *sty, BULLET *pb, float *pgravity);
void BossGearAtack(IMG *img, BOSS *boss, GEAR *gear, PLAYER *player, BOM *bom, int *stx, int *sty, BULLET *pb, float *pgravity);
int BulletBossHit(BULLET *pb, BOSS *boss, PLAYER *player, int *stx, int *sty);
int BulletBOMHit(BULLET *pb, BOM *bom, PLAYER *player, int *stx, int *sty,int j);
int BulletGearHit(BULLET *pb, GEAR *gear, PLAYER *player, int *stx, int *sty);
int BulletBossHitdeadly(BULLET *pb, BOSS *boss, PLAYER *player, int *stx, int *sty);//必殺用
int BulletBOMHitdeadly(BULLET *pb, BOM *bom, PLAYER *player, int *stx, int *sty, int j);
int BulletGearHitdeadly(BULLET *pb, GEAR *gear, PLAYER *player, int *stx, int *sty);
void BossFinish(IMG *img, BOSS *boss, PLAYER *player, int *stx, int *sty, int *flg);


void BossMapOpen(char **map)
{
	int i, j;
	FILE *fp;

	fopen_s(&fp, "map/bossmap.txt", "r");
	if (fp == NULL) { return; }
	for (i = 0; i < StageH; i++) {
		for (j = 0; j < StageW; j++) {
			map[i][j] = fgetc(fp);
		}
	}

	fclose(fp);
	return;
}

//移動処理
void Boss(IMG *img, char *map, BOSS *boss, PLAYER *player, int stx)
{
	int i;

	//move処理
	if (boss->cnt < 200) {
		for (i = 0; i < 2; i++) {
			if (boss->x + 153< player->x - stx&&boss->x + 155 > player->x - stx||player->deadlyflg>3) { break; }//この範囲に入ったらボスが移動をやめる
			if (boss->x + 154 < player->x - stx) {
				boss->x += boss->kasoku + 0.5;
			}
			else {
				boss->x -= boss->kasoku + 0.5;
			}
		}
		boss->cnt++;
	}
	//減速
	if (boss->cnt > 160) { boss->kasoku -= 0.04; }

	//stop処理
	if (boss->cnt >= 200) { boss->cnt++; }
	//移動用変数初期化
	if (boss->cnt > 300) {
		boss->cnt = 0;
		boss->kasoku = 1.4;
	}

	if (boss->x < BOSSMIN) { boss->x = BOSSMIN; }
	if (boss->x > BOSSMAX) { boss->x = BOSSMAX; }
	return;
}
//ボス当たり判定
int BossCloss(BOSS *boss, PLAYER *player, int *stx, int *sty)
{
	if (-boss->y - *sty < player->y + 128 && -boss->y - *sty + 530 > player->y) {
		if (boss->x + 203 < player->x + 128 - *stx&&boss->x + 246 > player->x - *stx&&boss->flg == 0) {
			boss->flg = 1;
			return 1;
		}
	}
	else {
		boss->flg = 0;

	}

	return 0;
}

//方向判別
void Direction(BOSS *boss, PLAYER *player, int stx)
{
	if (boss->x + stx + 188 < player->x + 64) { boss->direction = 1; }//向きが右
	if (boss->x + stx + 188 > player->x + 64) { boss->direction = 0; }//向きが左
	return;
}

//ボム攻撃
void BossBomAtack(IMG *img, BOSS *boss, PLAYER *player, BOM *bom, int *stx, int *sty, BULLET *pb, float *pgravity)
{
	int i, flg = 3;

	//ボムを４つ出す管理処理
	if (boss->attack < 4) {
		flg = 1;
		boss->bomcnt++;
		if (boss->bomcnt > 121) { boss->bomcnt = 0; }

	}

	//ボムが重ならないようにする判定
	for (i = 0; i < 6; i++) {
		if (boss->x + 193 + *stx < (bom + i)->x + *stx + 64 && boss->x + 350 + 64 + *stx >(bom + i)->x + *stx - 64 || boss->bomcnt < 120) {
			flg = 0;
			break;
		}
	}

	//ボム出現位置の設定
	if (flg == 1) {
		for (i = 0; i < 6; i++) {
			if ((bom + i)->flag == 0) {
				(bom + i)->flag = 1;
				(bom + i)->x = 220 + boss->x;
				(bom + i)->y = BOSSY - 110;
				boss->bomcnt = 0;
				boss->attack += 1;
				break;
			}
		}
	}


	//ボム移動処理
	for (i = 0; i < 6; i++) {
		//落下
		if ((bom + i)->flag == 1) {
			(bom + i)->kasoku += 0.12;
			(bom + i)->y += (bom + i)->kasoku;
			//高さ設定
			if ((bom + i)->y > 490 - 34) {
				(bom + i)->y = 490 - 34;
				(bom + i)->cnt += 1;
				if ((bom + i)->cnt == 1) {
					if (player->deadlyflg <= 3) {
						ds_play1("sound/着地.wav");
					}
				}

			}

			//時間による爆発設定
			if ((bom + i)->cnt > 700) {
				(bom + i)->kasoku = 0;
				(bom + i)->cnt = 0;
				(bom + i)->flag = 2;

			}
			//自機との当たり判定
			if (player->deadlyflg < 3) {
				if ((bom + i)->x + *stx + 14 < player->x + 114 && (bom + i)->x + *stx + 50 > player->x + 14 && (bom + i)->y - (*sty) + 14 < player->y + 105 && (bom + i)->y - (*sty) + 50 > player->y + 23 && player->InvincibleCnt == 0 && player->flg == 0) {
					(bom + i)->kasoku = 0;
					(bom + i)->cnt = 0;
					(bom + i)->flag = 2;
					player->life--;

					*pgravity = JUMPPOWER / 1.1;
					player->flg = 2;
					if (player->life == 0) {
						ds_play1("sound/ko1.wav");
					}
				}
			}
			//ボム描画
			if (BulletBOMHit(pb, bom, player, stx, sty, i) == 0) {
				if ((bom + i)->cnt % 30<15) {
					dg_drawbmp5(bb, (bom + i)->x + *stx, 490 + 20 - (*sty), 64, 10, img->shadow, 0, 0, 86, 10, (bom + i)->kasoku * 10, RGB(255, 0, 255));
					dg_drawbmp5(bb, (bom + i)->x + *stx, (bom + i)->y - (*sty), 64, 64, img->bom, 64, 0, 64, 64, 100, RGB(255, 0, 255));

				}
				else {
					dg_drawbmp5(bb, (bom + i)->x + *stx, 490 + 20 - (*sty), 64, 10, img->shadow, 0, 0, 86, 10, (bom + i)->kasoku * 10, RGB(255, 0, 255));
					dg_drawbmp5(bb, (bom + i)->x + *stx, (bom + i)->y - (*sty), 64, 64, img->bom, 0, 0, 64, 64, 100, RGB(255, 0, 255));
				}
			}
			else {
				dg_drawbmp5(bb, (bom + i)->x + *stx, (bom + i)->y - (*sty), 64, 64, img->bom, 0, 0, 64, 64, 70, RGB(255, 0, 255));
				dg_drawbmp5(bb, (bom + i)->x + *stx - 20 + rand() % 30, (bom + i)->y - (*sty) - rand() % 20, 64, 64, img->Damage_Effect, 0, 0, 64, 64, 100, RGB(255, 0, 255));

			}
			if (player->deadlyflg == 5)
			{
				if (BulletBOMHitdeadly(pb, bom, player, stx, sty, i) == 0) {
					if ((bom + i)->cnt % 30<15) {
						dg_drawbmp5(bb, (bom + i)->x + *stx, 490 + 20 - (*sty), 64, 10, img->shadow, 0, 0, 86, 10, (bom + i)->kasoku * 10, RGB(255, 0, 255));
						dg_drawbmp5(bb, (bom + i)->x + *stx, (bom + i)->y - (*sty), 64, 64, img->bom, 64, 0, 64, 64, 100, RGB(255, 0, 255));

					}
					else {
						dg_drawbmp5(bb, (bom + i)->x + *stx, 490 + 20 - (*sty), 64, 10, img->shadow, 0, 0, 86, 10, (bom + i)->kasoku * 10, RGB(255, 0, 255));
						dg_drawbmp5(bb, (bom + i)->x + *stx, (bom + i)->y - (*sty), 64, 64, img->bom, 0, 0, 64, 64, 100, RGB(255, 0, 255));
					}
				}
				else {
					dg_drawbmp5(bb, (bom + i)->x + *stx, (bom + i)->y - (*sty), 64, 64, img->bom, 0, 0, 64, 64, 70, RGB(255, 0, 255));
					dg_drawbmp5(bb, (bom + i)->x + *stx - 20 + rand() % 30, (bom + i)->y - (*sty) - rand() % 20, 64, 64, img->Damage_Effect, 0, 0, 64, 64, 100, RGB(255, 0, 255));

				}
			}
		}

		//ボスを倒したとき
		if ((bom + i)->flag == 2) {
			if ((bom + i)->cnt == 0) {
				if (player->deadlyflg <= 3) {
					ds_play1("sound/爆発1.wav");
				}
			}
			dg_drawbmp3(bb, (bom + i)->x + *stx - 30, (bom + i)->y - (*sty) - 30, 94, 94, img->explosion, 96 * (bom + i)->cnt, 0, RGB(255, 0, 255));
			(bom + i)->kasoku++;
			if ((bom + i)->kasoku > 4) {
				(bom + i)->cnt++;
				(bom + i)->kasoku = 0;
			}
			if ((bom + i)->cnt > 8) {
				(bom + i)->kasoku = 0;
				(bom + i)->cnt = 0;
				(bom + i)->flag = 0;
				(bom + i)->x = 0;
			}
		}

	}
	if (player->InvincibleCnt) {
		player->InvincibleCnt++;
		player->InvincibleCnt = player->InvincibleCnt % 120;
	}

	return;


}
void BossGearAtack(IMG *img, BOSS *boss, GEAR *gear, PLAYER *player, BOM *bom, int *stx, int *sty, BULLET *pb, float *pgravity)
{
	int i, j, flg = 3;
	static char gflg = 1;
	if (boss->attack == 4) {
		flg = 1;
		boss->gearcnt++;
		if (boss->gearcnt > 121) { boss->gearcnt = 0; }

	}

	//ギアが重ならないようにする判定
	for (i = 0; i < 2; i++) {
		if (boss->x + 183 + *stx < (bom + i)->x + *stx + 64 && boss->x + 360 + *stx >(bom + i)->x + *stx || boss->gearcnt < 120) {
			flg = 0;
			break;

		}
	}

	//ギア出現位置の設定
	if (flg == 1) {
		for (i = 0; i < 2; i++) {
			if ((gear + i)->flag == 0) {
				(gear + i)->flag = 1;
				(gear + i)->x = 220 + boss->x;
				(gear + i)->y = BOSSY - 160;
				boss->gearcnt = 0;
				boss->attack = 0;
				break;
			}
		}

	}
	//ギア移動処理
	for (i = 0; i < 2; i++) {
		//移動
		if ((gear + i)->flag == 1) {
			(gear + i)->kasoku += 0.06;
			(gear + i)->y += (gear + i)->kasoku;

			//高さ設定
			if ((gear + i)->y > 490 - 34 - 32) {
				(gear + i)->y = 490 - 34 - 32;
				(gear + i)->kasoku = 0;
				if (player->deadlyflg <= 3) {
					ds_play1("sound/歯車着地.wav");
				}
				if (boss->x + *stx + 240 < player->x + 64) {
					(gear + i)->direction = 0;
				}
				else {
					(gear + i)->direction = 1;

				}
				(gear + i)->flag = 2;
			}
		}

		if ((gear + i)->flag == 2 || (gear + i)->flag == 4) {
			if ((gear + i)->direction == 1) {
				(gear + i)->kasoku -= 0.06;
				(gear + i)->skasoku -= 0.04;
				(gear + i)->cnt += (gear + i)->skasoku;

			}
			else {
				(gear + i)->kasoku += 0.06;
				(gear + i)->skasoku += 0.04;
				(gear + i)->cnt += (gear + i)->skasoku;
			}
			(gear + i)->x += (gear + i)->kasoku;

			//リセット設定
			if ((gear + i)->x + *stx <640 + *stx || (gear + i)->x + *stx + 32 >BOSSMAX + 300 + *stx) {
				(gear + i)->kasoku = 0;
				(gear + i)->cnt = 0;
				(gear + i)->flag = 0;
				(gear + i)->x = 0;
				(gear + i)->skasoku = 0;
				(gear + i)->life = 8;
				(gear + i)->attack = 0;
			}
		}

		//自機当たり判定
		if ((gear + i)->flag == 1 || (gear + i)->flag == 2) {
			if ((gear + i)->x + *stx + 14 < player->x + 114 && (gear + i)->x + *stx + 82 > player->x + 14 && (gear + i)->y - (*sty) + 14 < player->y + 105 && (gear + i)->y - (*sty) + 82 > player->y + 23 && player->InvincibleCnt == 0&&player->deadlyflg<4) {
				if ((gear + i)->attack == 0) {
					player->life--;
					player->InvincibleCnt++;
					(gear + i)->attack = 1;
				}
				*pgravity = JUMPPOWER / 2;
				player->flg = 1;
				if (player->life == 0) {
					if (player->deadlyflg <= 3) {
						ds_play1("sound/ko1.wav");
					}
				}
			}
		}
		//攻撃ではじかれた処理
		if ((gear + i)->flag == 5) {
			if ((gear + i)->direction == 1) {
				(gear + i)->kasoku -= 0.5;
				(gear + i)->skasoku -= 0.04;
				(gear + i)->y -= (gear + i)->kasoku;
				(gear + i)->y -= (gear + i)->kasoku;
				(gear + i)->cnt -= (gear + i)->skasoku;
				(gear + i)->x += 8;
				//影描画
				dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, (gear + i)->kasoku * 60, RGB(255, 0, 255));
				if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
				if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
				if (gflg % 4 != 0) {
					dg_drawbmp6(bb, (gear + i)->x + *stx, (gear + i)->y - (*sty), 96, 96, img->gear, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));
					gflg++;

				}
				else {
					gflg++;
				}


			}
			else {
				(gear + i)->kasoku -= 0.5;
				(gear + i)->skasoku -= 0.04;
				(gear + i)->y -= (gear + i)->kasoku;
				(gear + i)->y -= (gear + i)->kasoku;
				(gear + i)->cnt -= (gear + i)->skasoku;
				(gear + i)->x -= 8;
				//影描画
				dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, (gear + i)->kasoku * 60, RGB(255, 0, 255));
				if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
				if (gflg % 4 != 0) {
					dg_drawbmp6(bb, (gear + i)->x + *stx, (gear + i)->y - (*sty), 96, 96, img->gear, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));
					gflg++;

				}
				else {
					gflg++;
				}

			}

			if (gflg > 40) { gflg = 0; }

			(gear + i)->life--;
			if ((gear + i)->life < -28) {
				(gear + i)->life = 8;
				(gear + i)->kasoku = 0;
				(gear + i)->cnt = 0;
				(gear + i)->flag = 0;
				(gear + i)->x = 0;
				(gear + i)->skasoku = 0;

			}

		}
		//歯車描画
		if ((gear + i)->flag != 0 && (gear + i)->flag != 5) {
			if (BulletGearHit(pb, gear, player, stx, sty) == 0) {
				dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, (gear + i)->kasoku * 60, RGB(255, 0, 255));
				if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
				dg_drawbmp6(bb, (gear + i)->x + *stx, (gear + i)->y - (*sty), 96, 96, img->gear, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));
			}
			else {
				dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 76, 10, (gear + i)->kasoku * 60, RGB(255, 0, 255));
				if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
				dg_drawbmp6(bb, (gear + i)->x + *stx, (gear + i)->y - (*sty), 96, 96, img->gear, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));
				dg_drawbmp6(bb, (gear + i)->x + *stx - 30 + rand() % 40, (gear + i)->y - (*sty) - 20 + rand() % 30, 64, 64, img->Damage_Effect, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));

			}
			if (player->deadlyflg == 5)
			{
				if (BulletGearHitdeadly(pb, gear, player, stx, sty) == 0) {
					dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, (gear + i)->kasoku * 60, RGB(255, 0, 255));
					if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
					dg_drawbmp6(bb, (gear + i)->x + *stx, (gear + i)->y - (*sty), 96, 96, img->gear, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));
				}
				else {
					dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 76, 10, (gear + i)->kasoku * 60, RGB(255, 0, 255));
					if ((gear + i)->flag == 2) { dg_drawbmp5(bb, (gear + i)->x + *stx + 10, 490 + 20 - (*sty), 76, 10, img->shadow, 0, 0, 86, 10, 100, RGB(255, 0, 255)); }
					dg_drawbmp6(bb, (gear + i)->x + *stx, (gear + i)->y - (*sty), 96, 96, img->gear, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));
					dg_drawbmp6(bb, (gear + i)->x + *stx - 30 + rand() % 40, (gear + i)->y - (*sty) - 20 + rand() % 30, 64, 64, img->Damage_Effect, 0, 0, 64, 64, (gear + i)->cnt, RGB(255, 0, 255));

				}
			}
		}

	}
	if (player->InvincibleCnt) {
		player->InvincibleCnt++;
		player->InvincibleCnt = player->InvincibleCnt % 120;
	}

	return;


}


int BulletBossHit(BULLET *pb, BOSS *boss, PLAYER *player, int *stx, int *sty)
{
	int i, j;

	//弾とボスの当たり判定
	for (i = 0; i < TMAX; i++) {
		if (pb[i].flg == 4 || pb[i].flg == 5) {
			if (pb[i].x + Bullet_W > boss->x + *stx && pb[i].x < boss->x + *stx + 500 && pb[i].y + Bullet_H  >-boss->y - *sty && pb[i].y < -boss->y - *sty + 530) {
				pb[i].flg = 3;
				boss->life--;
				if (boss->life < 0) { boss->flg = 3; }
				return 1;
			}
		}
	}

	if (boss->life < 0) {
		boss->flg = 3;
		boss->cnt = 0;
	} 
	
	return 0;
}

int BulletBossHitdeadly(BULLET *pb, BOSS *boss, PLAYER *player, int *stx, int *sty)
{
	int i, j;

	//ボムと必殺の当たり判定
	if (player->direction == 0)
	{
			if (player->x < boss->x + *stx&& player->y < -boss->y - *sty + 570) {
				boss->life -= 100;
				if (boss->life < 0) {
					boss->flg = 3; 
					boss->cnt = 0;

				}
				return 1;
			}
	}
	if (player->direction == 1)
	{
			if (player->x > boss->x + *stx&& player->y < -boss->y - *sty + 570) {
				boss->life -= 100;
				if (boss->life < 0) {
					boss->flg = 3;
					boss->cnt = 0;

				}
				return 1;
			}
	}

	if (boss->life < 0) {
		boss->flg = 3;
		boss->cnt = 0;
	}
	return 0;
}

int BulletBOMHit(BULLET *pb, BOM *bom, PLAYER *player, int *stx, int *sty, int j)
{
	int i, flg = 0;

	//ボムと弾の当たり判定
	for (i = 0; i < TMAX; i++) {

		if (pb[i].flg == 4 || pb[i].flg == 5) {
			if (pb[i].x + Bullet_W >(bom + j)->x + *stx && pb[i].x < (bom + j)->x + *stx + 64 && pb[i].y + Bullet_H  >(bom + j)->y - (*sty) - 30 && pb[i].y <(bom + j)->y - (*sty) + 80) {
				pb[i].flg = 1;
				(bom + j)->life--;
				if ((bom + j)->life == 0) {
					(bom + j)->life = 10;
					(bom + j)->kasoku = 0;
					(bom + j)->cnt = 0;
					(bom + j)->flag = 2;
					if (player->deadlyflg == 0) {
						player->deadlyflg = 1;
					}

				}
				return 1;
			}
		}
	}
	return 0;
}

int BulletGearHit(BULLET *pb, GEAR *gear, PLAYER *player, int *stx, int *sty)
{
	int i, j;
	//歯車と弾の当たり判定
	for (i = 0; i < TMAX; i++) {
		for (j = 0; j < 2; j++) {
			if (pb[i].flg == 4 || pb[i].flg == 5) {
				if (pb[i].x + Bullet_W >(gear + j)->x + *stx && pb[i].x < (gear + j)->x + *stx + 64 && pb[i].y + Bullet_H  >(gear + j)->y - (*sty) - 10 && pb[i].y <(gear + j)->y - (*sty) + 50) {
					pb[i].flg = 1;
					(gear + j)->life--;
					if ((gear + j)->life == 0) {
						(gear + j)->flag = 5;
						(gear + j)->skasoku = 1;
						(gear + j)->kasoku = 7.5;
					}
					return 1;
				}
			}
		}
	}
	return 0;

}
int BulletBOMHitdeadly(BULLET *pb, BOM *bom, PLAYER *player, int *stx, int *sty, int j)
{
	int i;

	//ボムと必殺の当たり判定
	if (player->direction == 1) {
		if (player->x + 128 > (bom + j)->x + *stx&&player->y<(bom + j)->y + 64 && player->y + PlayerH>(bom + j)->y) {
			(bom + j)->life -= 3;
			if ((bom + j)->life <= 0) {
				(bom + j)->life = 10;
				(bom + j)->kasoku = 0;
				(bom + j)->cnt = 0;
				(bom + j)->flag = 2;
				if (player->deadlyflg == 0) {
					player->deadlyflg = 1;
				}
			}
			return 1;

		}
	}
	else {
		if (player->x < (bom + j)->x + *stx&&player->y<(bom + j)->y + 64 && player->y + PlayerH>(bom + j)->y) {
			(bom + j)->life -= 3;
			if ((bom + j)->life <= 0) {
				(bom + j)->life = 10;
				(bom + j)->kasoku = 0;
				(bom + j)->cnt = 0;
				(bom + j)->flag = 2;
				if (player->deadlyflg == 0) {
					player->deadlyflg = 1;
				}
			}
			return 1;
		}

	}
	return 0;
}

int BulletGearHitdeadly(BULLET *pb, GEAR *gear, PLAYER *player, int *stx, int *sty)
{
	int i, j;

	//歯車と必殺の当たり判定
	for (j = 0; j < 2; j++) {
		if (player->direction == 0)
		{
			if (player->x  <(gear + j)->x + *stx&&player->y<(gear + j)->y + ENEMY_H&&player->y + PlayerH>(gear + j)->y) {
				(gear + j)->life--;
				if ((gear + j)->life <= 0) {
					(gear + j)->flag = 5;
					(gear + j)->skasoku = 1;
					(gear + j)->kasoku = 7.5;
				}
				return 1;
			}
		}
		if (player->direction == 1)
		{
			if (player->x>(gear + j)->x + *stx&&player->y<(gear + j)->y + ENEMY_H&&player->y + PlayerH>(gear + j)->y) {
				(gear + j)->life--;
				if ((gear + j)->life <= 0) {
					(gear + j)->flag = 5;
					(gear + j)->skasoku = 1;
					(gear + j)->kasoku = 7.5;
				}
				return 1;
			}
		}
	}
	return 0;

}

void BossFinish(IMG *img, BOSS *boss, PLAYER *player, int *stx, int *sty, int *flg) {
	int i;

	static int a = 7;
	static int b = 3;
	static int f = 0;
	static int j = 0;

	//落下中のボスの爆発処理
	j++;	
	if (j % 3 == 0 && boss->flg == 3) {
		a = a*-1;
		b = b*-1;
		*stx -= a;
		*sty -= b;
		player->y += a*-1;
	}
	if (*flg == 1) {
		for (i = 0; i < 8; i++) {
			if (boss->cnt < 30 && boss->explosion[i] == 0) {
				boss->explosion[i] = 1;
				boss->explosionx[i] = rand() % 250 + 50;
				boss->explosiony[i] = rand() % 400 + 50;
				boss->explosionr[i] = rand() % 200 - 50;
				break;
			}
			if (boss->explosion[i] > 0) {
				if (boss->cnt % 5 == 0) {
					boss->explosion[i]++;
				}
			}
			if (boss->explosion[i] > 8) {
				boss->explosion[i] = 0;
			}
		}
		if (boss->cnt > 30) { boss->cnt = 0; }
		boss->y -= 2;
	}
	if (boss->cnt > 300) {
		*flg = 1;
	}
	boss->cnt++;

}
