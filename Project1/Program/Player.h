//プレイヤー関連関数
char Draw_Player(PLAYER *p, IMG img, char *Animation_CNT, int jumpFlg, int Frame, int Bullet_CNT);
void Player_Move(PLAYER *p, int jump_Flg, IMG *img, int Bullet_CNT, int Frame, char *Animation_CNT,
	char *p_map, int *stx, int *sty, int jumpflg, float *ScrollCnt, int k, ROBEE *robee, int *save_x);
void Player_Gravity(PLAYER *p, int *p_pushflg, int *pjumpflg, float *pGkasoku, float *pgravity,
	char *p_map, int *stx, int *sty, int k, short kf, int k2, short k2f, int *pflg, int *save_y, int *BossStageFlag);
void Atari_Judge(PLAYER *p, ENEMY *e, int *Player_Get_Damage, IMG img, char *Animation_CNT, int *stx, int *sty, float *pgravity, char *p_map, float *ScrollCnt);
void Shadow(char *p_map, int *stx, int *sty, short *px, float *py, char_far shadow, int k);



//弾関数
void Bullet_Move(BULLET *pb, char *p_map, int stx, int sty, IMG img, PLAYER p);
void Bullet_Reload(PLAYER p, BULLET *pb, int *pFrame, int *pBulletCNT);
void Bullet_Atari_Judge(BULLET *pb, ENEMY *e, int ib);
void Bullet_Atari_Judge2(PLAYER pb, ENEMY *e, int ib);
void Bullet_Shot2(PLAYER p, BULLET *pb, int *pBullet_CNT, int Frame, IMG img, int Jump_flg);
void B_init(BULLET *pb);
int SnapInto_LR(char *p_map, int stx, int sty, short px, short py);

char CutinCNT = 0;

//プレイヤー関連関数=============================================================================================================
char Draw_Player(PLAYER *p, IMG img, char *Animation_CNT, int jumpFlg, int Frame, int Bullet_CNT)
{

	static char animation = 0;
	static char flg = 0;
	static char cnt = 0;

	if (flg == 1) {
		if (Frame%ANIMATION_INTERVAL == 0) {
			if (CutinCNT == 0) {
				animation++;
			}
		}
		if (animation > 28) {
			animation = 0;
			flg = 0;
			p->deadly = 60;
			p->deadlycnt = 0;
			p->deadlyflg = 0;
		}
	}

	//必殺技発動
	if (p->deadlyflg == 2 || p->deadlyflg == 3) {
		if (jumpFlg == 0 && p->life>0) {
			if (getch3('F') == 1) {
				ds_play1("sound/super-arts-motion1.wav");
				flg = 1;
				p->deadlyflg = 4;
				CutinCNT = 1;
			}
		}
	}


	if (flg == 0) {
		if (!(p->InvincibleCnt % 5)) {
			if (getch3(VK_LEFT) == 0 && getch3(VK_RIGHT) == 0) {
				if (p->direction == DIRECTION_RIGHT) {
					if (p->flg == 1) {
						if (p->life <= 0) {
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, 0, PlayerH * 15, RGB(255, 0, 255));
						}
						else {
							if (*Animation_CNT > 1) { *Animation_CNT = 0; }
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW* *Animation_CNT, PlayerH * 12, RGB(255, 0, 255));
						}
					}
					//ボムやられ:右
					else if (p->flg == 2) {
						if (p->life <= 0) {
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, 0, PlayerH * 15, RGB(255, 0, 255));
						}
						else {
							if (*Animation_CNT > 1) { *Animation_CNT = 0; }
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, 0, PlayerH * 14, RGB(255, 0, 255));
						}
					}
					else if (jumpFlg != 0) {
						//ジャンプ撃ちモーション
						if (getch3('D') == 1 && Bullet_CNT > 0 && Frame > 100) {
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 10, RGB(255, 0, 255));
							if (*Animation_CNT > 3) { *Animation_CNT = 2; }
						}
						else {
							//ジャンプモーション描画（右）
							if (*Animation_CNT > 4) { *Animation_CNT = 1; }
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 8, RGB(255, 0, 255));
						}
					}
					else if (getch3('D') == 1 && Bullet_CNT != 0 && Frame > 100) {
						//立ち撃ちモーション描画（右）
						if (*Animation_CNT > 4) { *Animation_CNT = 3; }
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 4, RGB(255, 0, 255));
					}
					else {
						//立ちモーション描画（右）
						if (*Animation_CNT > PLAYER_STAND_BY_MOTION) { *Animation_CNT = 0; }
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, 0, RGB(255, 0, 255));
					}
				}
				else {
					if (p->flg == 1) {
						if (p->life <= 0) {
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, 128, PlayerH * 15, RGB(255, 0, 255));
						}
						else {
							if (*Animation_CNT > 1) { *Animation_CNT = 0; }
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW* *Animation_CNT, PlayerH * 13, RGB(255, 0, 255));
						}
					}
					//ボムやられ;左
					if (p->flg == 2) {
						if (p->life <= 0) {
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, 128, PlayerH * 15, RGB(255, 0, 255));
						}
						else {
							if (*Animation_CNT > 1) { *Animation_CNT = 0; }
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW, PlayerH * 14, RGB(255, 0, 255));
						}
					}
					else if (jumpFlg != 0) {
						if (getch3('D') == 1 && Bullet_CNT > 0 && Frame > 100) {
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 11, RGB(255, 0, 255));
							if (*Animation_CNT > 3) { *Animation_CNT = 2; }
						}
						else {
							//ジャンプモーション描画（左）
							if (*Animation_CNT > 4) { *Animation_CNT = 1; }
							dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 9, RGB(255, 0, 255));
						}
					}
					else if (getch3('D') == 1 && Bullet_CNT != 0 && Frame > 100) {
						//立ち撃ちモーション描画（左）
						if (*Animation_CNT > 4) { *Animation_CNT = 3; }
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 5, RGB(255, 0, 255));
					}
					else {
						//立ちモーション描画（左）
						if (*Animation_CNT > PLAYER_STAND_BY_MOTION) { *Animation_CNT = 0; }
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 1, RGB(255, 0, 255));
					}
				}
			}
			else
			{
				if (p->direction == DIRECTION_RIGHT) {
					if (p->flg == 0) {
						if (jumpFlg != 0) {
							//ジャンプ中移動（右）
							if (getch3('D') == 1 && Bullet_CNT > 0 && Frame > 100) {
								dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 10, RGB(255, 0, 255));
								if (*Animation_CNT > 3) { *Animation_CNT = 2; }
							}
							else {
								if (*Animation_CNT > 4) { *Animation_CNT = 1; }
								dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 8, RGB(255, 0, 255));
							}
						}
					}
				}
				else {
					if (p->flg == 0) {
						if (jumpFlg != 0) {
							if (getch3('D') == 1 && Bullet_CNT > 0 && Frame > 100) {
								dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 11, RGB(255, 0, 255));
								if (*Animation_CNT > 3) { *Animation_CNT = 2; }
							}
							else {
								//ジャンプ中移動（左）
								if (*Animation_CNT > 4) { *Animation_CNT = 1; }
								dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img.Player_Animation, PlayerW * *Animation_CNT, PlayerH * 9, RGB(255, 0, 255));
							}
						}
					}
				}
			}
		}
	}

	if (animation == 8) { ds_play1("sound/qigong2.wav"); }
	if (animation == 1) { ds_play1("sound/robot-footstep1.wav"); }

	if (flg) {
		if (p->direction == DIRECTION_RIGHT) {
			if (animation < 9) {
				dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, animation * 128, 16 * 128, RGB(255, 0, 255));
				if (animation > 6) {
					dg_drawbmp3(bb, p->x + 112, p->y + 16, 96, 96, img.Robee_sp, (animation - 6) * 96, 0, RGB(255, 0, 255));
				}
			}
			else if (animation < 18) {
				dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, (animation - 9) * 128, 17 * 128, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x + 112, p->y + 16, 96, 96, img.Robee_sp, (animation - 6 < 12) ? (animation - 6) * 96 : 12 * 96, 0, RGB(255, 0, 255));
			}
			else {
				if (animation < 23) {
					dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, (animation - 18) * 128, 18 * 128, RGB(255, 0, 255));
				}
				else {
					dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, (animation < 26) ? 5 * 128 : (animation - 22) * 128, 18 * 128, RGB(255, 0, 255));
				}
				if (animation < 25) {
					dg_drawbmp3(bb, p->x + 112, p->y + 16, 96, 96, img.Robee_sp, (animation < 22) ? 13 * 96 : (animation - 10) * 96, 0, RGB(255, 0, 255));
				}
				else {
					dg_drawbmp3(bb, p->x + 112, p->y + 16, 96, 96, img.Robee_sp, 0, 0, RGB(255, 0, 255));
				}

			}

			if (animation > 20) {
				dg_drawbmp3(bb, p->x + 112 + 32, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 0, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x + 112 + 32 + 112, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x + 112 + 32 + 112 + 128, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x + 112 + 32 + 112 + 256, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x + 112 + 32 + 112 + 384, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
			}

		}
		else {
			if (animation < 9) {
				dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, animation * 128, 19 * 128, RGB(255, 0, 255));
				if (animation > 6) {
					dg_drawbmp3(bb, p->x - 80, p->y + 16, 96, 96, img.Robee_sp, (animation - 6) * 96, 96, RGB(255, 0, 255));
				}
			}
			else if (animation < 18) {
				dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, (animation - 9) * 128, 20 * 128, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x - 80, p->y + 16, 96, 96, img.Robee_sp, (animation - 6 < 12) ? (animation - 6) * 96 : 12 * 96, 96, RGB(255, 0, 255));
			}
			else {
				if (animation < 23) {
					dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, (animation - 18) * 128, 21 * 128, RGB(255, 0, 255));
				}
				else {
					dg_drawbmp3(bb, p->x, p->y, 128, 128, img.Player_Animation, (animation < 26) ? 5 * 128 : (animation - 22) * 128, 21 * 128, RGB(255, 0, 255));
				}
				if (animation < 25) {
					dg_drawbmp3(bb, p->x - 80, p->y + 16, 96, 96, img.Robee_sp, (animation < 22) ? 13 * 96 : (animation - 10) * 96, 96, RGB(255, 0, 255));
				}
				else {
					dg_drawbmp3(bb, p->x - 80, p->y + 16, 96, 96, img.Robee_sp, 0, 96, RGB(255, 0, 255));
				}
			}

			if (animation > 20) {
				dg_drawbmp3(bb, p->x - 112 - 32, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 128, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x - 112 - 32 - 112, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x - 112 - 32 - 112 - 128, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x - 112 - 32 - 112 - 256, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
				dg_drawbmp3(bb, p->x - 112 - 32 - 112 - 384, p->y, 128, 128, img.Buster_Effect, (animation - 20) * 128, 256, RGB(255, 0, 255));
			}

		}
	}

	return flg;
}

void Player_Move(PLAYER *p, int jump_Flg, IMG *img, int Bullet_CNT, int Frame, char *Animation_CNT,
	char *p_map, int *stx, int *sty, int jumpflg, float *ScrollCnt, int k, ROBEE *robee, int *save_x)
{
	static int Save_x = 0;
	int i;
	static char flg = 0;
	static char flg2 = 0;
	static int save = 0;
	static char Effect_Animation = 0;

	if (getch3(VK_RIGHT) == 1 || getch3(VK_LEFT) == 1) {
		if (flg == 0) {
			flg = 1;
			flg2 = 1;
		}
	}

	if (flg2 == 1) {
		if (Frame%ANIMATION_INTERVAL == 0) {
			Effect_Animation++;
			if (Effect_Animation > 4) {
				flg2 = 0;
				Effect_Animation = 0;
			}
		}
	}




	if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) != 2) {
		if (p->direction == DIRECTION_RIGHT) {
			if (flg2 == 1) {
				if (jumpflg == 0) {
					dg_drawbmp3(bb, p->x - save - 32, p->y + 64, PlayerW, PlayerH / 2, img->Dash_Effect, Effect_Animation * 128, 0, RGB(255, 0, 255));
				}
			}
		}
	}

	if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) != 1) {
		if (p->direction == DIRECTION_LEFT) {
			if (flg2 == 1) {
				if (jumpflg == 0) {
					dg_drawbmp3(bb, p->x - save + 32, p->y + 64, PlayerW, PlayerH / 2, img->Dash_Effect, Effect_Animation * 128, 64, RGB(255, 0, 255));
				}
			}
		}
	}

	if (p->life != 0) {
		if (getch3(VK_RIGHT) == 1 && getch3(VK_LEFT) == 0) {
			*stx -= Player_MOVE_SPEED;
			if(*stx < 0) {
				
			}
			if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 2) {
				//stxが512～約-12000の範囲で移動する際に0が入り、
				//マイナスの値が1少なくなるので判定を分けています
				if (*stx > 0) {
					*stx = ((*stx + 64) / 64) * 64 - CharaMARGIN + 1;
				}
				else {
					*stx = (*stx / 64) * 64 - CharaMARGIN + 1;
				}
			}
			else {
				save += Player_MOVE_SPEED;
				*save_x -= Player_MOVE_SPEED;
				robee->x -= 8;
				if (p->x - robee->x > 150) {
					robee->x = 425;
				}
				if (p->flg == 0) {
					*ScrollCnt += SCROLLSPEED;
				}
			}

			p->direction = DIRECTION_RIGHT;

			//立ち撃ちモーション
			if (p->flg == 1) {
				if (*Animation_CNT > 1) { *Animation_CNT = 0; }
				if (!(p->InvincibleCnt % 5)) {
					dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW* *Animation_CNT, PlayerH * 12, RGB(255, 0, 255));
				}
			}
			else if (p->flg == 2) {
				if (*Animation_CNT > 1) { *Animation_CNT = 0; }
				if (!(p->InvincibleCnt % 5)) {
					dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, 0, PlayerH * 14, RGB(255, 0, 255));
				}
			}
			else if (jump_Flg == 0) {
				if ((getch3('D') == 1 && Bullet_CNT != 0 && Frame > 100)) {
					if (*Animation_CNT > 7) { *Animation_CNT = 0; }
					if (!(p->InvincibleCnt % 5)) {
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW * *Animation_CNT, PlayerH * 6, RGB(255, 0, 255));
					}
				}
				else {
					if (*Animation_CNT > 7) { *Animation_CNT = 0; }
					if (!(p->InvincibleCnt % 5)) {
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW * *Animation_CNT, PlayerH * 2, RGB(255, 0, 255));
					}
				}
			}
			//	}
		}
		if (getch3(VK_RIGHT) == 0 && getch3(VK_LEFT) == 0) {
			Save_x = 0;

			if (flg2 == 0) {
				save = 0;
				flg = 0;
				Effect_Animation = 0;
			}
		}

		//if (p->flg == 0) {
		if (getch3(VK_LEFT) == 1) {
			*stx += Player_MOVE_SPEED;
			if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 1) {

				//stxが512～約-12000の範囲で移動する際に0が入り、
				//マイナスの値が1少なくなるので判定を分けています
				if (*stx > 0) {
					*stx = (*stx / 64) * 64 + CharaMARGIN;
				}
				else {
					*stx = ((*stx - 64) / 64) * 64 + CharaMARGIN;
				}
			}
			else {
				save -= Player_MOVE_SPEED;
				if (p->x - robee->x < -250) {
					robee->x = 825;
				}
				*save_x += Player_MOVE_SPEED;
				robee->x += 8;
				if (p->flg == 0) {
					*ScrollCnt -= SCROLLSPEED;
				}
			}

			p->direction = DIRECTION_LEFT;
			if (p->flg == 1) {
				if (*Animation_CNT > 1) { *Animation_CNT = 0; }
				if (!(p->InvincibleCnt % 5)) {
					dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW* *Animation_CNT, PlayerH * 13, RGB(255, 0, 255));
				}
			}
			else if (p->flg == 2) {
				if (*Animation_CNT > 1) { *Animation_CNT = 0; }
				if (!(p->InvincibleCnt % 5)) {
					dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW, PlayerH * 14, RGB(255, 0, 255));
				}
			}
			else if (jump_Flg == 0) {
				//ジャンプ撃ち
				if ((getch3('D') == 1 && Bullet_CNT != 0 && Frame > 100)) {
					if (*Animation_CNT > 7) { *Animation_CNT = 0; }
					if (!(p->InvincibleCnt % 5)) {
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW * *Animation_CNT, PlayerH * 7, RGB(255, 0, 255));
					}
				}
				else {
					if (*Animation_CNT > 7) { *Animation_CNT = 0; }
					if (!(p->InvincibleCnt % 5)) {
						dg_drawbmp3(bb, p->x, p->y, PlayerW, PlayerH, img->Player_Animation, PlayerW * *Animation_CNT, PlayerH * 3, RGB(255, 0, 255));
					}
				}
			}
		}
	}


	return;
}


//ジャンプ関数
void JumpFunc(int *p_pushflg, int *pjumpflg, float *pgravity, IMG img, PLAYER p, int frame, int *save_x, int *save_y)
{
	static int Animation = 0;
	static char flg = 0;

	if (flg == 1) {
		if (frame%ANIMATION_INTERVAL == 0) { Animation++; }
		if (Animation > 3) {
			Animation = 0;
			flg = 0;
		}
	}

	if (getch3(VK_SPACE)) {
		if (*p_pushflg == 0)
		{
			if (*pjumpflg == 0) {
				ds_play1("sound/jump1.wav");
				*pgravity = JUMPPOWER;
				*pjumpflg = 1;
			}
			else if (*pjumpflg == 1) {
				*save_x = p.x;
				*save_y = p.y;
				ds_play1("sound/jump1.wav");
				*pgravity = JUMPPOWER*JUMPPOWER2;
				*pjumpflg = 2;
				flg = 1;
			}
		}
		*p_pushflg = 1;
	}
	else {
		*p_pushflg = 0;
	}
	if (flg) { dg_drawbmp3(bb, *save_x, *save_y + 128, 128, 64, img.Jump_Effect, 128 * Animation, 0, RGB(255, 0, 255)); }

	return;
}

void Player_Gravity(PLAYER *p, int *p_pushflg, int *pjumpflg, float *pGkasoku, float *pgravity,
	char *p_map, int *stx, int *sty, int k, short kf, int k2, short k2f, int *pflg, int *save_y, int *BossStageFlag) {
	int  sc;
	int ssc;
	int i;
	static int cnt = 0;
	static int cntf = 0;
	static int cnt2 = 0;
	*sty += *pgravity;
	*save_y -= *pgravity;

	sc = StageCollision_UD(p_map, stx, sty, &p->x, &p->y, k, k2, BossStageFlag);
	ssc = StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k);
	if (p->life>10)
	{
		p->life = 10;
	}
	if (cntf == 1)
	{
		cnt++;
		if (cnt >= 330)
		{
			for (i = 0; i < 20000; i++)
			{
				if (*(p_map + i) == 50)
				{
					*(p_map + i) = 42;
				}
				if (*(p_map + i) == 22)
				{
					*(p_map + i) = 43;
				}
			}
			cnt = 0;
			cntf = 0;
		}
	}

	switch (ssc)
	{
	case 3:sc = 11;
		break;
	case 4:sc = 17;
		break;
	case 5:sc = 18;
		break;
	case 6:sc = 19;
		break;
	}

	if (sc == 4) {
		*pjumpflg = 0;
		*sty = ((*sty - 64) / 64) * 64;
	}
	else if (sc == 3) {
		*sty = ((*sty / 64) * 64) - CharaMARGIN + 10;
		*pgravity = PLAYER_GRAVITY_MAX;
	}
	else if (sc == 0 && *pjumpflg == 0) {
		*pjumpflg = 1;
	}
	if (*BossStageFlag)
	{
		*pflg = 2;
	}
	else if (sc == 7)
	{
		*pjumpflg = 0;
		*sty = ((*sty - 64) / 64) * 64;
		ds_play1("sound/heavy-e02.wav");
		cntf = 1;
		for (i = 0; i < 20000; i++)
		{
			if (*(p_map + i) == 42)
			{
				*(p_map + i) = 50;
			}
			if (*(p_map + i) == 43)
			{
				*(p_map + i) = 22;
			}
		}
	}
	else
	{
		Gimmick(sc, pjumpflg, p_map, stx, sty, &p->life, k, kf, k2, k2f);
	}


	if (p->flg == 2) {
		cnt2++;
		if (cnt2 > ANIMATION_INTERVAL * 2) {
			*pgravity += 1;
		}
		cnt2 = cnt2 % (ANIMATION_INTERVAL * 5);
	}

	*pgravity += PLAYER_GRAVITY_SPEED;

	if (*pgravity > PLAYER_GRAVITY_MAX && p->flg != 2) { *pgravity = PLAYER_GRAVITY_MAX; }
	return;
}

//自機と敵機のあたり判定
void Atari_Judge(PLAYER *p, ENEMY *e, int *Player_Get_Damage, IMG img, char *Animation_CNT, int *stx, int *sty, float *pgravity, char *p_map, float *ScrollCnt)
{
	int i, n;
	int k = 2;
	static short j = 0;
	if (p->life > 0) {
		if (p->flg == 0) {
			for (i = 0; i < ENEMY_CNT + ENEMY_CNT2; i++) {
				if ((e + i)->apper == 1) {
					if (p->x + PlayerW >(e + i)->x && p->x < (e + i)->x + ENEMY_W && p->y + PlayerH>(e + i)->y && p->y < (e + i)->y + ENEMY_H && !(p->InvincibleCnt)) {
						if ((e + i)->atari_flg == 0) {
							(e + i)->atari_flg = 1;
							if (p->life > 0) {
								p->life--;
							}
							*Animation_CNT = 0;
							p->flg = 1;
							(e + i)->atari_flg = 0;
							*pgravity = JUMPPOWER / 2;
							if (p->life == 0) {
								ds_play1("sound/ko1.wav");
							}
							else {
								ds_play1("sound/punch-high1.wav");
							}
							return;
						}
					}
				}
				if (p->x + PlayerW > (e + i)->bx && p->x < (e + i)->bx + 20 && p->y + PlayerH >(e + i)->by && p->y + CharaMARGIN < (e + i)->by + 20 && !(p->InvincibleCnt) && (e + i)->bflg) {
					if ((e + i)->atari_flg == 0) {
						(e + i)->atari_flg = 1;
						if (p->life > 0) {
							p->life--;
						}
						*Animation_CNT = 0;
						p->flg = 1;
						(e + i)->atari_flg = 0;
						*pgravity = JUMPPOWER / 2;
						if (p->life == 0) {
							ds_play1("sound/ko1.wav");
						}
						else {
							ds_play1("sound/punch-high1.wav");
						}
						(e + i)->bflg = 0;
						(e + i)->bcnt = 0;
						return;
					}
				}

			}
		}
		else
			if (p->flg == 1) {
				if (j < ANIMATION_INTERVAL * 3) {
					*Animation_CNT++;
					j++;
					if (p->direction == DIRECTION_LEFT) {
						*stx -= 15;
						if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 2) {
							//stxが512～約-12000の範囲で移動する際に0が入り、
							//マイナスの値が1少なくなるので判定を分けています
							if (*stx > 0) {
								*stx = ((*stx + 64) / 64) * 64 - CharaMARGIN + 1;
							}
							else {

								*stx = (*stx / 64) * 64 - CharaMARGIN + 1;
							}
						}
						else {
							*ScrollCnt += 3;
						}
					}
					else {
						*stx += 15;
						if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 1) {
							//stxが512～約-12000の範囲で移動する際に0が入り、
							//マイナスの値が1少なくなるので判定を分けています
							if (*stx > 0) {
								*stx = (*stx / 64) * 64 + CharaMARGIN;
							}
							else {
								*stx = ((*stx - 64) / 64) * 64 + CharaMARGIN;
							}
						}
						else {
							*ScrollCnt -= 3;
						}
					}
				}
				else {
					p->flg = 0;
					j = 0;
					*Animation_CNT = 0;
					p->InvincibleCnt = 1;
				}
			}
			else
				if (p->flg == 2) {
					if (j < ANIMATION_INTERVAL * 5) {
						*Animation_CNT++;
						j++;
						if (j < ANIMATION_INTERVAL * 2) {
							if (p->direction == DIRECTION_LEFT) {
								*stx -= 15;
								if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 2) {
									//stxが512～約-12000の範囲で移動する際に0が入り、
									//マイナスの値が1少なくなるので判定を分けています
									if (*stx > 0) {
										*stx = ((*stx + 64) / 64) * 64 - CharaMARGIN + 1;
									}
									else {

										*stx = (*stx / 64) * 64 - CharaMARGIN + 1;
									}
								}
								else {
									*ScrollCnt += 3;
								}
							}
							else {
								*stx += 15;
								if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 1) {
									//stxが512～約-12000の範囲で移動する際に0が入り、
									//マイナスの値が1少なくなるので判定を分けています
									if (*stx > 0) {
										*stx = (*stx / 64) * 64 + CharaMARGIN;
									}
									else {
										*stx = ((*stx - 64) / 64) * 64 + CharaMARGIN;
									}
								}
								else {
									*ScrollCnt -= 3;
								}
							}
						}
						else {
							if (p->direction == DIRECTION_LEFT) {
								*stx -= 15;
								if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 2) {
									//stxが512～約-12000の範囲で移動する際に0が入り、
									//マイナスの値が1少なくなるので判定を分けています
									if (*stx > 0) {
										*stx = ((*stx + 64) / 64) * 64 - CharaMARGIN + 1;
									}
									else {

										*stx = (*stx / 64) * 64 - CharaMARGIN + 1;
									}
								}
								else {
									*ScrollCnt += 3;
								}
							}
							else {
								*stx += 15;
								if (StageCollision_LR(p_map, stx, sty, &p->x, &p->y, k) == 1) {
									//stxが512～約-12000の範囲で移動する際に0が入り、
									//マイナスの値が1少なくなるので判定を分けています
									if (*stx > 0) {
										*stx = (*stx / 64) * 64 + CharaMARGIN;
									}
									else {
										*stx = ((*stx - 64) / 64) * 64 + CharaMARGIN;
									}
								}
								else {
									*ScrollCnt -= 3;
								}
							}
						}
					}
					else {
						p->flg = 0;
						j = 0;
						*Animation_CNT = 0;
						p->InvincibleCnt = 1;
					}
				}
	}
	if (p->InvincibleCnt) {
		p->InvincibleCnt++;
		p->InvincibleCnt = p->InvincibleCnt % 120;
	}
}



void Shadow(char *p_map, int *stx, int *sty, short *px, float *py, char_far shadow, int k)
{
	int i, j;
	int Shadow_Deviated = 21;

	for (j = 0; j < 42; j++) {
		for (i = 0; i < 200; i += 5)  //動きが重たいなって思ったらここの+=2の2を5等に増やしてください。少しは軽くなるはずです。
		{
			if (*(p_map + (((-(*stx - j * 2) + (int)*px + Shadow_Deviated) / 64) + ((49 - (-(*sty + i) + 64) / 64) * StageW))) == 22)
			{
				dg_drawbmp5(bb, Shadow_Deviated + *px + j * 2, *py + PlayerH + i - 5, 2, 10, shadow, 2 * j, 0, 2, 10, 100 - 20 - i / 4, RGB(255, 0, 255));
				break;
			}
			if (*(p_map + (((-(*stx - j * 2) + (int)*px + Shadow_Deviated) / 64) + ((49 - (-(*sty + i) + 64) / 64) * StageW))) == 6)
			{
				dg_drawbmp5(bb, Shadow_Deviated + *px + j * 2, *py + PlayerH + i - 5, 2, 10, shadow, 2 * j, 0, 2, 10, 100 - 20 - i / 4, RGB(255, 0, 255));
				break;
			}
			if (*(p_map + (((-(*stx - j * 2) + (int)*px + Shadow_Deviated) / 64) + ((49 - (-(*sty + i) + 64) / 64) * StageW))) == 7)
			{
				dg_drawbmp5(bb, Shadow_Deviated + *px + j * 2, *py + PlayerH + i - 5, 2, 10, shadow, 2 * j, 0, 2, 10, 100 - 20 - i / 4, RGB(255, 0, 255));
				break;
			}
			if (*(p_map + (((-(*stx - j * 2) + (int)*px + Shadow_Deviated) / 64) + ((49 - (-(*sty + i) + 64) / 64) * StageW))) == 8)
			{
				dg_drawbmp5(bb, Shadow_Deviated + *px + j * 2, *py + PlayerH + i - 5, 2, 10, shadow, 2 * j, 0, 2, 10, 100 - 20 - i / 4, RGB(255, 0, 255));
				break;
			}
			if (*(p_map + (((-(*stx - j * 2) + (int)*px + Shadow_Deviated) / 64) + ((49 - (-(*sty + i) + 64) / 64) * StageW))) == 19)
			{
				dg_drawbmp5(bb, Shadow_Deviated + *px + j * 2, *py + PlayerH + i - 5, 2, 10, shadow, 2 * j, 0, 2, 10, 100 - 20 - i / 4, RGB(255, 0, 255));
				break;
			}
			if (*(p_map + (((-(*stx - j * 2) + (int)*px + Shadow_Deviated-k) / 64)  + ((49 - (-(*sty + i) + 64) / 64) * StageW))) == 31)
			{
				dg_drawbmp5(bb, Shadow_Deviated + *px + j * 2 - (k / 64), *py + PlayerH + i - 5, 2, 10, shadow, 2 * j, 0, 2, 10, 100 - 20 - i / 4, RGB(255, 0, 255));
				break;
			}

		}
	}
}
//-------------------------------------------------------------------------------------------------------------

//弾関数===========================================================================================================================
//弾移動＆描画関数
void Bullet_Move(BULLET *pb, char *p_map, int stx, int sty, IMG img, PLAYER p)
{
	int i;

	static int Animation_CNT = 0;
	//最後までアニメーションしたら0に
	if (Animation_CNT > 7) { Animation_CNT = 0; }

	for (i = 0; i < TMAX; i++) {
		if (pb[i].flg == 4) {
			pb[i].x += BulletSPEED;
			if (pb[i].x >= MapWIDTH) { pb[i].flg = 6; }
			pb[i].y += pb[i].vy;
			//弾と壁のあたり判定
			if (SnapInto_LR(p_map, stx, sty, pb[i].x + 80, 0) != 0) {
				dg_drawbmp3(bb, pb[i].x + 32, pb[i].y - 32, 64, 64, img.Damage_Effect, 0, 0, RGB(255, 0, 255));
				pb[i].flg = 6;

			}
		}
		else if (pb[i].flg == 5) {
			pb[i].x -= BulletSPEED;
			if (pb[i].x <= 0) { pb[i].flg = 6; }
			pb[i].y += pb[i].vy;
			if (SnapInto_LR(p_map, stx, sty, pb[i].x - 40, 0) != 0) {
				dg_drawbmp3(bb, pb[i].x - 32, pb[i].y - 32, 64, 64, img.Damage_Effect, 0, 0, RGB(255, 0, 255));
				pb[i].flg = 6;
			}
		}
		//弾描画
		if (pb[i].flg == 4 || pb[i].flg == 5) {
			if (p.direction == DIRECTION_RIGHT) {
				dg_drawbmp3(bb, pb[i].x + 55, pb[i].y - 15, 32, 32, img.Bullet, 32 * Animation_CNT, 0, RGB(255, 0, 255));
			}
			else {
				dg_drawbmp3(bb, pb[i].x - 55, pb[i].y - 15, 32, 32, img.Bullet, 32 * Animation_CNT, 32, RGB(255, 0, 255));
			}
		}
	}
	Animation_CNT++;

	return;
}

//マシンガンリロード関数
void Bullet_Reload(PLAYER p, BULLET *pb, int *pFrame, int *pBulletCNT)
{
	int i;
	int reloadflg;

	if (pb->flg != 0) {
		if (getch3('S') == 1) {
			ds_play1("sound/gun-ready01.wav");
			*pFrame = FRAME_DEFAULT;
			reloadflg = RELOAD_NOW;
			*pBulletCNT = TMAX;
			for (i = 0; i < TMAX; i++) {
				pb[i].flg = 0;
				if (p.direction == DIRECTION_RIGHT) {
					pb[i].x = p.x + PlayerW;
					if (i % 2 == 0) {
						pb[i].y = p.y + PlayerH / 2 - 5;
					}
					else {
						pb[i].y = p.y + PlayerH / 2;
					}
				}
				else {
					pb[i].x = p.x;
					if (i % 2 == 0) {
						pb[i].y = p.y + PlayerH / 2 - 5;
					}
					else {
						pb[i].y = p.y + PlayerH / 2;
					}
				}
			}
		}
	}
	if (*pFrame == 0) { reloadflg = RELOAD_NOT; }
	return;
}

//弾と敵機のあたり判定
void Bullet_Atari_Judge(BULLET *pb, ENEMY *e, int ib)
{
	int i = ib, j;

	for (j = 0; j < ENEMY_CNT + ENEMY_CNT2; j++) {
		if ((e + j)->apper == 1) {
			if (pb[i].x + Bullet_W > (e + j)->x && pb[i].x < (e + j)->x + ENEMY_W && pb[i].y + Bullet_H  >(e + j)->y && pb[i].y < (e + j)->y + ENEMY_H) {
				pb[i].flg = 3;
				(e + j)->flg = 3;
				(e + j)->hp--;
				if ((e + j)->hp < 0) {
					(e + j)->hp = 0;
					(e + j)->apper = 0;
				}
			}
		}
	}

}

void Bullet_Atari_Judge2(PLAYER pb, ENEMY *e, int ib)
{
	int i = ib, j;

	for (j = 0; j < ENEMY_CNT + ENEMY_CNT2; j++) {
		if ((e + j)->apper == 1) {
			if (pb.direction == 0) {
				if (pb.x  <(e + j)->x&&pb.x + 704  >(e + j)->x&&pb.y<(e + j)->y + ENEMY_H&&pb.y + PlayerH>(e + j)->y) {
					(e + j)->flg = 3;
					(e + j)->hp--;
					if ((e + j)->hp < 0) {
						(e + j)->hp = 0;
						(e + j)->apper = 0;
					}
				}
			}
				if (pb.direction == 1) {
					if (pb.x > (e + j)->x&&pb.x - 576 < (e + j)->x&&pb.y<(e + j)->y + ENEMY_H&&pb.y + PlayerH>(e + j)->y) {
						(e + j)->flg = 3;
						(e + j)->hp--;
						if ((e + j)->hp < 0) {
							(e + j)->hp = 0;
							(e + j)->apper = 0;
						}
					}
				}
		}
	}

}

//弾発射関数
void Bullet_Shot2(PLAYER p, BULLET *pb, int *pBullet_CNT, int Frame, IMG img, int Jump_flg)
{
	int i;
	//弾発射アニメーションカウント変数
	static int Animation_CNT = 0;
	static int Animation_CNT2 = -2;
	Animation_CNT++;
	Animation_CNT2++;
	//最後までアニメーションしたら0に
	if (Animation_CNT > 3) { Animation_CNT = 0; }
	if (Animation_CNT2 > 3) { Animation_CNT2 = 0; }

	if (Frame > 100) {
		if (p.flg == 0) {
			if (Frame%Bullet_INTERVAL == 0) {
				if (*pBullet_CNT > 0) {
					ds_play1("sound/gun1.wav");

					for (i = 0; i < TMAX; i++) {
						if (pb[i].flg == 0) {
							if (*pBullet_CNT > 0) {
								*pBullet_CNT -= 1;
								if (p.direction == DIRECTION_RIGHT) {
									pb[i].flg = 4;
									pb[i].x = p.x + PlayerW - 20;
									pb[i].vy = -(rand() % 2 * 2);
									//跳んでいないとき
									if (Jump_flg == 0) {
										if (i % 2 == 0) {
											pb[i].y = p.y + PlayerH / 2 - 5;
										}
										else {
											pb[i].y = p.y + PlayerH / 2;
										}
										//弾発射Effect描画(右)
										dg_drawbmp3(bb, p.x + PlayerW, p.y + PlayerH / 2 - 16, 64, 32, img.Bullet_Effect, Animation_CNT * 64, 0, RGB(255, 0, 255));
										dg_drawbmp3(bb, p.x + PlayerW, p.y + PlayerH / 2 - 18, 64, 32, img.Bullet_Effect, Animation_CNT2 * 64, 0, RGB(255, 0, 255));
									}
									else {
										//	跳んでいるとき
										if (i % 2 == 0) {
											pb[i].y = p.y + PlayerH / 2 - 33;
										}
										else {
											pb[i].y = p.y + PlayerH / 2 - 16;
										}
										//弾発射Effect描画（右）
										dg_drawbmp3(bb, p.x + PlayerW, p.y + PlayerH / 2 - 43, 64, 32, img.Bullet_Effect, Animation_CNT * 64, 0, RGB(255, 0, 255));
										dg_drawbmp3(bb, p.x + PlayerW, p.y + PlayerH / 2 - 25, 64, 32, img.Bullet_Effect, Animation_CNT2 * 64, 0, RGB(255, 0, 255));
									}
									break;
								}
								else {
									pb[i].flg = 5;
									pb[i].x = p.x;
									if (Jump_flg == 0) {
										if (i % 2 == 0) {
											pb[i].y = p.y + PlayerH / 2 - 5;
										}
										else {
											pb[i].y = p.y + PlayerH / 2;
										}
										//弾発射Effect描画(右)
										dg_drawbmp3(bb, p.x - 60, p.y + PlayerH / 2 - 16, 64, 32, img.Bullet_Effect, Animation_CNT * 64, 32, RGB(255, 0, 255));
										dg_drawbmp3(bb, p.x - 60, p.y + PlayerH / 2 - 18, 64, 32, img.Bullet_Effect, Animation_CNT2 * 64, 32, RGB(255, 0, 255));
									}
									else {
										//	跳んでいるとき
										if (i % 2 == 0) {
											pb[i].y = p.y + PlayerH / 2 - 33;
										}
										else {
											pb[i].y = p.y + PlayerH / 2 - 16;
										}
										//弾発射Effect描画（右）
										dg_drawbmp3(bb, p.x - 60, p.y + PlayerH / 2 - 43, 64, 32, img.Bullet_Effect, Animation_CNT * 64, 32, RGB(255, 0, 255));
										dg_drawbmp3(bb, p.x - 60, p.y + PlayerH / 2 - 25, 64, 32, img.Bullet_Effect, Animation_CNT2 * 64, 32, RGB(255, 0, 255));
									}
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return;
}

void B_init(BULLET *pb)
{
	int i;

	for (i = 0; i < TMAX; i++) {
		pb[i].flg = 0;
		pb[i].vy = 0;
	}
	return;
}

int SnapInto_LR(char *p_map, int stx, int sty, short px, short py)
{
	int left = ((-(stx)+(int)px) / 64);
	int right = ((-(stx)+(int)px) / 64);
	int up = ((49 - (-(sty)+PlayerH) / 64) * StageW);
	int down = ((49 - (-(sty)+64) / 64) * StageW);
	// 左判定
	if ((*(p_map + (left + up))) == 29 ||
		(*(p_map + (left + down))) == 29)
	{
		return 0;
	}
	if ((*(p_map + (left + up))) == 29 * 2 ||
		(*(p_map + (left + down))) == 29 * 2)
	{
		return 0;
	}
	if ((*(p_map + (left + up))) == 29 * 3 ||
		(*(p_map + (left + down))) == 29 * 3)
	{
		return 0;
	}
	if ((*(p_map + (left + up))) == 29 * 4 ||
		(*(p_map + (left + down))) == 29 * 4)
	{
		return 0;
	}
	if ((*(p_map + (right + up))) == 29 ||
		(*(p_map + (right + down))) == 29)
	{
		return 0;
	}
	if ((*(p_map + (right + up))) == 29 * 2 ||
		(*(p_map + (right + down))) == 29 * 2)
	{
		return 0;
	}
	if ((*(p_map + (right + up))) == 29 * 3 ||
		(*(p_map + (right + down))) == 29 * 3)
	{
		return 0;
	}
	if ((*(p_map + (right + up))) == 29 * 4 ||
		(*(p_map + (right + down))) == 29 * 4)
	{
		return 0;
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
	else if ((*(p_map + (left + up))) > 5 ||
		(*(p_map + (left + down))) > 5)
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
	else if ((*(p_map + (right + up))) > 5 ||
		(*(p_map + (right + down))) > 5)
	{
		return 2;
	}
	return 0;
}
//-------------------------------------------------------------------------------------------------------------

