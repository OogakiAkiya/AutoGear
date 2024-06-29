//�^�C�g���֐�
void TitleProc(int *eflg);
//�Q�[���֐�
void GameProc(int *eflg);
//�{�X�֐�
void BossProc(int *eflg);

//�Q�[���I�[�o�[
void GameOver(int *eflg);


//�^�C�g���֐�
void TitleProc(int *eflg)
{
	float c = 0;
	char flg = 0;
	int a = 0;
	//FPS����ϐ�
	unsigned long starttime, st = 0, fpscnt = 0, scnt = 0;
	starttime = NOW;
	//�{�^������, �O���f�[�V�����J�E���g
	short button = 0, cnt[2] = { 30, 0 }, acnt[9];
	//�O���f�[�V�����t���O, �L�[�t���O, �A�N�V�����t���O, �A�N�V����������
	char gf[2] = { 0, 0 }, kf = 0, af = 0, cf[9], jf = 0;
	//�A�N�V����������xy���W
	short cx, cy[9], i, j = 9, k = 9, BoxSize = 35, inter = 1,
		BaseFrame = 15, frame = BaseFrame * 8, BoxCnt = 0,
		Tw = 800, Th = 600, CircleCnt = 0, BackCnt = 0 * inter, Backf = 0;
	char_far Box, Titleb, Comment, Backb, Fade;
	//�O���f�[�V�����p�F�ϐ�
	COLORREF but;

	//������
	Box = dg_createbmp(BoxSize, BoxSize);
	dg_box(Box, 0, 0, BoxSize, BoxSize, 1, RGB(255, 255, 255));
	Titleb = dg_loadbmp("bmp/Title.bmp");
	Backb = dg_loadbmp("bmp/TBack.bmp");
	Comment = dg_loadbmp("bmp/Comment.bmp");
	Fade = dg_loadbmp("bmp/�t�F�[�h.bmp");

	//�A�N�V�����������W������
	cx = (MapWIDTH - 277) / 2;
	for (i = 0; i < 9; i++) {
		cy[i] = 650;
		cf[i] = 0;
		acnt[i] = 0;
	}

	//�^�C�g��BGM
	ds_play3("sound/�^�C�g��.wav");

	//�^�C�g�����[�v
	while (1)
	{
		if (flg == 1) { c += 0.5; }
		a++;
		if (getch3(VK_ESCAPE) && a > 60) {
			*eflg = 999;
			exit(0);
		}

		dg_gcls(bb, RGB(255, 255, 255));
		dg_drawbmp5(bb, 0, 0, MapWIDTH, MapHEIGHT, Backb, 0, 0, MapWIDTH, MapHEIGHT, BackCnt / inter, -1);
	
		//FPS����
		if (NOW - starttime < 1000 / 60) { continue; }
		starttime = NOW;
		if (NOW - st > 1000) {
			scnt = fpscnt;
			st = NOW;
			fpscnt = 0;
		}

		//�{�^���w��
		if (getch3(VK_UP) && !kf && !*eflg) {
			button--;
			if (button < 0) { button = 1; }
			kf = 1;
			ds_play1("sound/button60.wav");
		}
		if (getch3(VK_DOWN) && !kf && !*eflg) {
			button++;
			button = button % 2;
			kf = 1;
			ds_play1("sound/button60.wav");
		}
		//����
		if (getch3(VK_RETURN)) {
			if (!button) {
				if (!*eflg) {
					ds_play1("sound/robot-footstep2.wav");
				}
				*eflg = 1;
				flg = 1;
				ds_stop("bgm");
			}
			if (button == 1 && !af) { af = 1; }
		}

		if (!kbhit()) {
			kf = 0;
		}

		dg_setfont(60, 120, "calibrib");
		dg_drawbmp4(bb, (MapWIDTH - (Tw + 200)) / 2, -60, Tw + 200, Th + 90, Titleb, 0, 0, Tw, Th, RGB(255, 0, 255));
		dg_setfont(20, 40, "calibrib");

		//�w��{�^������
		but = RGB((15 - (255 * 0.8)) * cnt[0] / 100 + (255 * 0.8), (15 - (255 * 0.8)) * cnt[0] / 100 + (255 * 0.8), (15 - (255 * 0.8)) * cnt[0] / 100 + (255 * 0.8));
		if (!button)
		{
			dg_box(Box, 0, 0, BoxSize, BoxSize, 1, but);
			dg_drawbmp6(bb, (MapWIDTH - 145) / 2 - (BoxSize + 15), 512, BoxSize, BoxSize, Box, 0, 0, BoxSize, BoxSize, BoxCnt, -1);
			dg_drawbmp5(bb, (MapWIDTH - 148) / 2, 507, 145, 40, Comment, 0, 41, 145, 40, cnt[0], RGB(255, 0, 255));
			dg_drawbmp5(bb, (MapWIDTH - 321) / 2, 565, 321, 40, Comment, 0, 0, 321, 40, 80, RGB(255, 0, 255));
			dg_drawbmp5(bb, 0, 0, 1280, 720, Fade, 0, 0, 1280, 720, c, -1);
			if (c > 100) { break; }	
		}
		else
			if (button == 1)
			{
				dg_box(Box, 0, 0, BoxSize, BoxSize, 1, but);
				dg_drawbmp6(bb, (MapWIDTH - 321) / 2 - (BoxSize + 15), 570, BoxSize, BoxSize, Box, 0, 0, BoxSize, BoxSize, BoxCnt, -1);
				dg_drawbmp5(bb, (MapWIDTH - 148) / 2, 507, 145, 40, Comment, 0, 41, 145, 40, 80, RGB(255, 0, 255));
				dg_drawbmp5(bb, (MapWIDTH - 321) / 2, 565, 321, 40, Comment, 0, 0, 321, 40, cnt[0], RGB(255, 0, 255));
			}

		if (af) {
			dg_printf2(bb, (MapWIDTH - (6 * 20)) / 2-100, 20, RGB((0 - 255) * cnt[1] / 100 + 255, (0 - 255) * cnt[1] / 100 + 255, (0 - 255) * cnt[1] / 100 + 255), -1, "���ݑI���ł��܂���");
		}

		//�O���f�[�V��������
		if (!gf[0]) { cnt[0]++; }
		if (gf[0]) { cnt[0]--; }
		if (!gf[1] && af) { cnt[1] += 2; }
		if (gf[1] && af) { cnt[1] -= 2; }
		//�t���O����
		if (cnt[0] > 90) { gf[0] = 1; }
		if (cnt[0] == 30) { gf[0] = 0; }
		if (cnt[1] > 90) { gf[1] = 1; }
		if (cnt[1] == 0) { gf[1] = 0; af = 0; }

		// ��������ђ��˂鏈�� ===================================================
		//�t���[������
		frame++;
		frame = frame % (BaseFrame * 10);
		if (!(frame)) {
			for (i = 0; i < 9; i++) {
				acnt[i] = 0;
				cf[i] = 0;
			}
			frame = 1;
			j = 0;
			k = 0;
		}

		//�t���[���ԏ���
		if (!jf && !(frame % (BaseFrame / 5))) { j++; }
		if (jf && !(frame % (BaseFrame / 5))) { k++; }

		if (j == 9) { jf = 1; }
		if (j == 0) { jf = 0; }
		if (k > 8) { k = 9; }

		//�A�N�V����������\��
		dg_drawbmp3(bb, cx, cy[0], 26, 40, Comment, 0, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 26, cy[1], 58 - 26, 40, Comment, 27, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 58, cy[2], 81 - 58, 40, Comment, 59, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 81, cy[3], 113 - 81, 40, Comment, 82, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 131, cy[4], 157 - 131, 40, Comment, 132, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 157, cy[5], 190 - 157, 40, Comment, 158, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 190, cy[6], 217 - 190, 40, Comment, 191, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 217, cy[7], 245 - 217, 40, Comment, 218, 90, RGB(255, 0, 255));
		dg_drawbmp3(bb, cx + 245, cy[8], 277 - 245, 40, Comment, 246, 90, RGB(255, 0, 255));


		//�A�N�V����
		for (i = k; i < j; i++) {
			cy[i] = 650 - sin(PI * 2 / (BaseFrame * 2) * acnt[i]) * 20;
		}

		//�A�N�V����������t���O, �J�E���g����
		for (i = k; i < j; i++) {
			if (!cf[i]) { acnt[i]++; }
			if (acnt[i] > BaseFrame) { acnt[i] = BaseFrame; cf[i] = 1; }
		}

		//�{�b�N�X�p�x����
		BoxCnt++;
		BoxCnt = BoxCnt % 360;

		//�w�i�̃{���{������
		if (!Backf) { BackCnt++; }
		if (Backf) { BackCnt--; }
		if (BackCnt / inter >= 100) { Backf = 1; }
		if (BackCnt / inter <= 0) { Backf = 0; }

		dg_flip(gvram, bb);
		ML();

	}
	dg_deletefont();
	dg_deletebmp(Box);
	dg_deletebmp(Titleb);
	dg_deletebmp(Backb);
	dg_deletebmp(Comment);
	return;
}

void GameProc(int *eflg)
{
	//���W�ۑ��p
	short Save_Player_X, Save_Player_Y;
	int save_x = 0;
	int save_y = 0;
	int SaveDirection;//��l���̌����i�ۑ��p�j
	int Player_Get_Damage;
	int Atari_Flg;
	float gravity, Gkasoku;//�v���C���[�̏d�́A�v���C���[�̏d�͉����x
	int jumpFlg, pushFlg;//�W�����v�t���O�A��i�W�����v���Ă��邩�ǂ���
	BULLET bullet[TMAX];
	int Effectw, Effecth;
	PLAYER player;
	char_far Cut_in;
	IMG img;
	player.x = Player_DEFAULT_X;
	player.y = Player_DEFAULT_Y;
	player.life = 10;
	player.flg = 0;
	player.InvincibleCnt = 0;
	player.deadly = 60;
	player.deadlycnt = 0;
	player.deadlyflg = 0;
	int Savecnt = 0;;

	// �}�b�v�p�ϐ�
	char Map[StageH][StageW];

	char *Map_Pointer[StageH];
	int stx = 0;
	int Save_stx = 0;
	int sty = 0;
	int Save_sty = 0;
	//�t���[��
	int Frame;
	int Anime_Frame = 0;
	//for���p�ϐ�
	int i, j;
	//�e�\���p
	int Bullet_CNT = TMAX;


	char Animation_CNT = 0;
	char HP_Animation_CNT[Player_Life] = { 0,0,0,0,0,0,0,0,0,0 };
	ENEMY e[ENEMY_CNT + ENEMY_CNT2];
	ENEMY *E;
	float c = 0;
	float ScrollCnt = 0;
	int k = 0;
	short kf;
	int k2 = 0;
	short k2f;
	//�M�~�b�N��
	int Mfx, Mfy;
	int f = 0;
	int BossStageFlag = 0;
	char deadlyflg = 0;

	E = e;
	// �G������
	E_init(E, &Map[0][0]);
	B_init(bullet);

	//��������
	player.direction = DIRECTION_RIGHT;
	gravity = 0;
	Gkasoku = 0;
	jumpFlg = 0;
	Frame = 101;
	pushFlg = 0;
	Player_Get_Damage = 0;
	Atari_Flg = 0;
	///////////////Robee//////////////////////////////////////////////

	ROBEE robee;
	robee.x = 460;
	robee.y = 300;
	robee.gravity = 0;
	robee.gravityflg = 0;
	robee.vx = 0;
	robee.vy = 0;

	////////////////////////////////////////////////////////////////

	char *pp = &Map[0][0];
	//�X�e�[�W�֘A�̕ϐ�������
	FILE *fp;
	errno_t error;
	for (i = 0; i < StageH; i++) { Map_Pointer[i] = Map[i]; }
	MapOpen(Map_Pointer);
	//�V���b�t��
	srand(time(0));
	rand();
	Cut_in = dg_loadbmp("bmp/Cut-in.bmp");
	//�r�b�g�}�b�v���[�h
	Load_Img(&img);

	//FPS����
	unsigned long starttime;
	starttime = NOW;
	int static unsigned long st = 0, fpscnt = 0, scnt = 0;


	DrawStage(&Map[0][0], img.MapChip, img.Objectbmp, stx, sty, &map_bmp, img.Move_Floor, E, &Mfx, &Mfy);

	Animation(&stx, &sty, map_bmp, img, 0, 100, 6400, 6500, 16500, 16600, &ScrollCnt);
	MapOpen(Map_Pointer);
	sty = 0;

	//BGM�Đ�
	ds_play3("sound/�X.wav");

	ScrollCnt = 0;
	while (1) {
		//��ʃN���A
		dg_drawbmp2(bb, 0, 0, MapWIDTH, MapHEIGHT, img.Background, ScrollCnt, 0);

		//FPS����
		if (NOW - starttime < 1000 / 60) { continue; }
		starttime = NOW;
		if (NOW - st > 1000) {
			scnt = fpscnt;
			st = NOW;
			fpscnt = 0;
		}

		//��l���̃J�b�g�C������
		if (CutinCNT != 0) {
			CutinCNT++;
			if (CutinCNT > 50) { CutinCNT = 0; }
		}

		//�X�e�[�W���W�i�[
		Save_stx = stx;
		Save_sty = sty;


		//�X�e�[�W, �M�~�b�N�`��
		dg_drawbmp3(bb, 0, 0, 1280, 720, map_bmp, -stx, sty + 2680, 0);
		Floor_Gimmick(&k, &kf, &k2, &k2f);
		GimmickDrawStage(&Map[0][0], img.MapChip, img.Objectbmp, img.Move_Floor, stx, sty, k, &Mfx, &Mfy, k2);


		Shadow(&Map[0][0], &stx, &sty, &player.x, &player.y, img.shadow, k);


		//���@����=================================================================================
		if (getch3(VK_ESCAPE) == 1) {
			*eflg = 0;
			break;
		}
		if (*eflg == 2) {
			c += 0.5;
		}

		if (c > 100) { break; }
		if (player.deadlyflg <= 3) {
			Player_Move(&player, jumpFlg, &img, Bullet_CNT, Frame, &Animation_CNT,
				&Map[0][0], &stx, &sty, jumpFlg, &ScrollCnt, k, &robee, &save_x);
		}


		//���@�A�G�@�����蔻��
		if (player.deadlyflg <= 3) {
			Atari_Judge(&player, E, &Player_Get_Damage, img, &Animation_CNT, &stx, &sty, &gravity, &Map[0][0], &ScrollCnt);
		}


		// �X�e�[�W�d�͏���
		sty += gravity;
		if (sty > 0) { sty = 0; }

		//���ݎ�l�����W�ۑ�
		Save_Player_X = player.x;
		Save_Player_Y = player.y;
		//�v���C���[�d�͏���
		Player_Gravity(&player, &pushFlg, &jumpFlg, &Gkasoku, &gravity,
			&Map[0][0], &stx, &sty, k, kf, k2, k2f, &*eflg, &save_y, &BossStageFlag);

		//�G�ړ�����
		E_move(&player, E, stx, sty, Save_stx, Save_sty, &Map[0][0]);

		//�W�����v�֐�
		if (player.deadlyflg <= 3) {
			JumpFunc(&pushFlg, &jumpFlg, &gravity, img, player, Frame, &save_x, &save_y);
		}

		Frame++;
		if (player.deadlyflg <= 3) {
			if (getch3('D') == 1) {
				Bullet_Shot2(player, bullet, &Bullet_CNT, Frame, img, jumpFlg);
			}
		}
		//�K�E�p�J�E���g
		if (player.deadlyflg == 4)
		{
			Savecnt++;
			if (Savecnt >= 160)
			{
				player.deadlyflg = 5;
			}
		}
		//�e�ړ�
		Bullet_Move(bullet, &Map[0][0], stx, sty, img, player);
		for (i = 0; i < TMAX; i++) {
			if (bullet[i].flg == 4 || bullet[i].flg == 5) { Bullet_Atari_Judge(bullet, E, i); }
			if (player.deadlyflg == 5)
			{
				Bullet_Atari_Judge2(player, E, i);
				Savecnt = 0;
			}
		}
		//�����[�h
		if (player.deadlyflg <= 3) {
			Bullet_Reload(player, bullet, &Frame, &Bullet_CNT);
		}
		//=========================================================================================================

		//���{�b�g����============================================================================================

		//���{�b�g�d�͏���
		Robot_gravity(&robee);
		//�Ǐ]���[�h
		Robot_TYPE1(player, &robee, &Map[0][0], k, &stx, &sty);
		//��l���`��
		deadlyflg = Draw_Player(&player, img, &Animation_CNT, jumpFlg, Frame, Bullet_CNT);
		Anime_Frame++;
		if (Anime_Frame > 5000) { Anime_Frame = 0; }
		if (Anime_Frame % ANIMATION_INTERVAL == 0) {
			Animation_CNT++;
		}

		//���{�b�g�`��
		if (deadlyflg == 0) {
			if (player.direction == DIRECTION_RIGHT) {
				dg_drawbmp3(bb, robee.x, robee.y, RobotW, RobotH, img.Robee, f * 32, 0, RGB(255, 0, 255));
			}
			else {
				dg_drawbmp3(bb, robee.x, robee.y, RobotW, RobotH, img.Robee, 64 + f * 32, 0, RGB(255, 0, 255));
			}
		}

		//�U�ꕝ
		Effectw = rand() % 32 - 16;
		Effecth = rand() % 32 - 16;

		//�G�`��
		//�Gver.1
		for (i = 0; i < ENEMY_CNT; i++) {
			if (abs(e[i].x - player.x) <= StageW * 2) {
				if (e[i].apper == 1) {
					if (e[i].flg != 3) {
						dg_drawbmp5(bb, e[i].x + 5, e[i].y + 90 + 38, 80, 10, img.shadow, 2, 0, 80, 10, 100 - 60, RGB(255, 0, 255));
						dg_drawbmp3(bb, e[i].x, e[i].y, ENEMY_W, ENEMY_H, img.Enemy1, 0, (e[i].vec - 1) * ENEMY_H, RGB(255, 0, 255));
					}
					else {
						dg_drawbmp5(bb, e[i].x + 5, e[i].y + 90 + 38, 80, 10, img.shadow, 2, 0, 80, 10, 100 - 60, RGB(255, 0, 255));
						dg_drawbmp3(bb, e[i].x, e[i].y, ENEMY_W, ENEMY_H, img.Enemy1, ENEMY_W * 2, (e[i].vec - 1) * ENEMY_H, RGB(255, 0, 255));
						dg_drawbmp3(bb, (e[i].x + 16) + Effectw, (e[i].y + 16) + Effecth, 64, 64, img.Damage_Effect, 0, 0, RGB(255, 0, 255));
						e[i].flg = 0;
					}
				}
			}
		}

		//�Gver.2
		for (; i < ENEMY_CNT + ENEMY_CNT2; i++) {
			if (abs(e[i].x - player.x) <= StageW * 2) {
				if (e[i].apper == 1) {
					if (e[i].flg != 3) {
						dg_drawbmp5(bb, e[i].x + 5, e[i].y + 90, 80, 10, img.shadow, 2, 0, 80, 10, 100 - 20, RGB(255, 0, 255));
						dg_drawbmp4(bb, e[i].x, e[i].y, ENEMY_W, ENEMY_H, img.Enemy2, (e[i].cnt / 20) * 128, abs((e[i].vec - 2)) * 128, 128, 128, RGB(255, 0, 255));
					}
					else {
						dg_drawbmp5(bb, e[i].x + 5, e[i].y + 90, 80, 10, img.shadow, 2, 0, 80, 10, 100 - 20, RGB(255, 0, 255));
						dg_drawbmp4(bb, e[i].x, e[i].y, ENEMY_W, ENEMY_H, img.Enemy2, (e[i].cnt / 20) * 128, abs((e[i].vec - 2)) * 128, 128, 128, RGB(255, 0, 255));
						dg_drawbmp3(bb, (e[i].x + 16) + Effectw, (e[i].y + 16) + Effecth, 64, 64, img.Damage_Effect, 0, 0, RGB(255, 0, 255));
						e[i].flg = 0;
					}
				}
			}
		}

		//�G�e�`��
		for (i = 0; i < ENEMY_CNT + ENEMY_CNT2; i++) {
			if (e[i].bflg) {
				dg_drawbmp3(bb, e[i].bx, e[i].by, 64, 32, img.E_bullet, 0, 0, RGB(255, 0, 255));
			}
			if (i >= ENEMY_CNT) {
				if (!e[i].apper) {
					e[i].cnt = 120;
					dg_drawbmp4(bb, e[i].x, e[i].y, ENEMY_W, ENEMY_H, img.Enemy2, (e[i].cnt / 20) * 128, abs((e[i].vec - 2)) * 128, 128, 128, RGB(255, 0, 255));
				}
			}
			if (!e[i].apper) {
				dg_drawbmp3(bb, e[i].x, e[i].y, ENEMY_W, ENEMY_H, img.explosion, (e[i].excnt / 10) * ENEMY_W, 0, RGB(255, 0, 255));
				if (e[i].excnt == 0) {
					ds_play1("sound/����1.wav");
				}
				e[i].excnt += 5;
				//�������Ԋi�[
				if (e[i].excnt > 80) {
					e[i].apper = 2;
					if (player.deadlyflg == 0) {
						player.deadlyflg = 1;
					}
				}
			}
		}


#ifdef DEBUG

#endif

		//UI�\��
		dg_drawbmp3(bb, 5, 5, 518, 226, img.HP, 0, 0, RGB(255, 0, 255));
		for (i = 0; i < Player_Life; i++) {
			if (Player_Life - (Player_Life - player.life) > i) {
				if (player.life > 4) {
					dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, 0, 227, RGB(255, 0, 255));
				}
				else if (player.life > 2) {
					dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, 0, 297, RGB(255, 0, 255));
				}
				else {
					if (Frame % 60 > 30) {
						dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, 0, 367, RGB(255, 0, 255));
					}
				}
			}
			else {
				if (HP_Animation_CNT[i] < 4) {
					if (player.life > 3) {
						dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, HP_Animation_CNT[i] * 44, 227, RGB(255, 0, 255));
					}
					else if (player.life > 2) {
						dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, HP_Animation_CNT[i] * 44, 297, RGB(255, 0, 255));
					}
					else {
						dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, HP_Animation_CNT[i] * 44, 367, RGB(255, 0, 255));
					}
					if (Anime_Frame % ANIMATION_INTERVAL == 0) {
						HP_Animation_CNT[i]++;
					}
				}
			}
		}

		dg_setfont(30, 70, "IMPACT");
		if (Frame > 100) {
			if (Bullet_CNT != 0) {
				dg_printf2(bb, 299, 99, RGB(255, 255, 255), -1, "%02d", Bullet_CNT);
			}
		}
		dg_deletefont();
		dg_setfont(15, 30, "MS�S�V�b�N");
		if (Bullet_CNT == 0) {
			dg_printf2(bb, 275, 115, RGB(250, 0, 0), -1, "EMPTY!!");
		}
		if (Frame < 100) {
			dg_printf2(bb, 280, 115, RGB(0, 0, 230), -1, "RELOAD");
		}
		dg_deletefont();

		//�K�E�`���[�W
		dg_drawbmp5(bb, 405, 102, 60, 60, img.HP, 60, 625, 60, 60, 100, RGB(255, 0, 255));
		if (player.deadlyflg == 1) {
			player.deadlycnt++;
			player.deadly--;
			if (player.deadlycnt > 10) {
				player.deadlycnt = 0;
				player.deadlyflg = 0;
			}
		}
		//�Q�[�W���܂肫�������̃T�E���h
		if (player.deadly < 0) {
			ds_play1("sound/robot-eye-flash1.wav");

			player.deadly = 0;
			player.deadlyflg = 2;
		}
		//�Q�[�W
		if (player.deadlyflg == 0 || player.deadlyflg == 1) {
			dg_drawbmp5(bb, 405, 102 + player.deadly, 60, 60 - player.deadly, img.HP, 0, 625 + player.deadly, 60, 60 - player.deadly, 100, RGB(255, 0, 255));
		}

		if (player.deadlyflg == 2) {
			player.deadlycnt += 2;
			if (player.deadlycnt > 100) { player.deadlyflg = 3; }
			dg_drawbmp5(bb, 405, 102 + player.deadly, 60, 60 - player.deadly, img.HP, 0, 625 + player.deadly, 60, 60 - player.deadly, 100 - player.deadlycnt, RGB(255, 0, 255));
		}
		if (player.deadlyflg == 3) {
			player.deadlycnt -= 2;
			if (player.deadlycnt < 0) { player.deadlyflg = 2; }
			dg_drawbmp5(bb, 405, 102 + player.deadly, 60, 60 - player.deadly, img.HP, 0, 625 + player.deadly, 60, 60 - player.deadly, 100 - player.deadlycnt, RGB(255, 0, 255));
		}

		if (ScrollCnt < 0) { ScrollCnt = 1280; }
		if (ScrollCnt > 1280) { ScrollCnt = 0; }
	
		dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, c, -1);

		if (CutinCNT != 0) {
			dg_drawbmp(bb, -1000 + ((CutinCNT < 30) ? CutinCNT * 32 : CutinCNT * 50), 360 - 150, 1280, 300, Cut_in);
		}


		//�Q�[���I�[�o�[����
		if (player.life <= 0) {
			player.life--;
			dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, -player.life, RGB(15, 0, 0));
			if (player.life < -100) {
				*eflg = 99;
				break;
			}
		}

		////////////////////////////////////
		if (getch3('P')) {
			*eflg = 2;
			break;
		}
		/////////////////////////////////////

		//�t���b�v
		dg_flip(gvram, bb);
		ML();
	}
	//�������J��
	ds_stop("bgm");
	dg_deletebmp(Cut_in);

	dg_deletebmp(map_bmp);
	Delete_Img(&img);
	return;
}

void BossProc(int *eflg)
{
	//���W�ۑ��p
	short Save_Player_X, Save_Player_Y;
	int save_x = 0;
	int save_y = 0;
	int SaveDirection;//��l���̌����i�ۑ��p�j
	int Player_Get_Damage;
	int Atari_Flg;
	float gravity, Gkasoku;//�v���C���[�̏d�́A�v���C���[�̏d�͉����x
	int jumpFlg, pushFlg;//�W�����v�t���O�A��i�W�����v���Ă��邩�ǂ���
	BULLET bullet[TMAX];
	PLAYER player;
	IMG img;
	char_far Cut_in;
	player.x = Player_DEFAULT_X;
	player.y = Player_DEFAULT_Y;
	player.flg = 0;
	player.InvincibleCnt = 0;
	player.deadly = 60;
	player.deadlycnt = 0;
	player.deadlyflg = 0;


	// �}�b�v�p�ϐ�
	char Map[StageH][StageW];

	char *Map_Pointer[StageH];
	int stx = -200;
	int Save_stx = 0;
	int sty = 0;
	//�t���[��
	int Frame;
	int Anime_Frame = 0;
	//for���p�ϐ�
	int i, j;
	//�e�\���p
	int Bullet_CNT = TMAX;

	char Animation_CNT = 0;
	char HP_Animation_CNT[Player_Life] = { 0,0,0,0,0,0,0,0,0,0 };
	float ScrollCnt = 0;
	int k = 0;
	short kf;
	int k2 = 0;
	short k2f;
	// BossFinish�p
	int flg = 0;
	int BossStageFlag = 0;

	int Savecnt = 0;
	//�M�~�b�N��
	int Mfx, Mfy;
	int f = 0;
	char deadlyflg = 0;
	ENEMY e[ENEMY_CNT + ENEMY_CNT2];
	ENEMY *E;

	player.life = 110;

	BOSS boss;
	boss.x = BOSSX;
	boss.y = BOSSY;
	boss.direction = 0;
	boss.flg = 0;
	boss.life = 50;
	boss.cnt = 0;
	boss.kasoku = 1.6;
	boss.bomcnt = 0;
	boss.gearcnt = 0;
	boss.attack = 0;
	boss.pflg = 0;
	boss.motionwait = -1;
	for (i = 0; i < 8; i++) {
		boss.explosion[i] = 0;
	}

	BOM bom[6];
	for (i = 0; i < 6; i++) {
		bom[i].x = 0;
		bom[i].y = 0;
		bom[i].cnt = 0;
		bom[i].flag = 0;
		bom[i].kasoku = 0;
		bom[i].life = 6;
	}

	GEAR gear[2];
	for (i = 0; i < 2; i++) {
		gear[i].x = 0;
		gear[i].y = 0;
		gear[i].cnt = 0;
		gear[i].flag = 0;
		gear[i].kasoku = 0;
		gear[i].direction = 0;
		gear[i].skasoku = 0;
		gear[i].life = 8;
		gear[i].attack = 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////


	//��������
	player.direction = DIRECTION_RIGHT;
	gravity = 0;
	Gkasoku = 0;
	jumpFlg = 0;
	Frame = 101;
	pushFlg = 0;
	Player_Get_Damage = 0;
	Atari_Flg = 0;

	///////////////Robee//////////////////////////////////////////////

	ROBEE robee;
	robee.x = 460;
	robee.y = 300;
	robee.gravity = 0;
	robee.gravityflg = 0;
	robee.vx = 0;
	robee.vy = 0;

	////////////////////////////////////////////////////////////////

	//�X�e�[�W�֘A�̕ϐ�������
	FILE *fp;
	errno_t error;
	for (i = 0; i < StageH; i++) { Map_Pointer[i] = Map[i]; }
	BossMapOpen(Map_Pointer);
	//�V���b�t��
	srand(time(0));
	rand();
	Cut_in = dg_loadbmp("bmp/Cut-in.bmp");
	//�r�b�g�}�b�v���[�h
	Load_Img(&img);

	//FPS����
	unsigned long starttime;
	starttime = NOW;
	int static unsigned long st = 0, fpscnt = 0, scnt = 0;
	E = e;
	// �G������
	E_init(E, &Map[0][0]);
	B_init(bullet);


	DrawStage(&Map[0][0], img.MapChip, img.Objectbmp, stx, sty, &map_bmp, img.Move_Floor, E, &Mfx, &Mfy);

	BossMapOpen(Map_Pointer);

	//BGM�Đ�
	ds_play3("sound/�{�X.wav");


	while (1) {
		//��ʃN���A
		dg_drawbmp2(bb, 0, 0, MapWIDTH, MapHEIGHT, img.Background, ScrollCnt, 0);
		//FPS����
		if (NOW - starttime < 1000 / 60) { continue; }
		starttime = NOW;
		if (NOW - st > 1000) {
			scnt = fpscnt;
			st = NOW;
			fpscnt = 0;
		}

		//��l���̃J�b�g�C������
		if (CutinCNT != 0) {
			CutinCNT++;
			if (CutinCNT > 50) { CutinCNT = 0; }
		}
		//�X�e�[�W���W�i�[
		Save_stx = stx;

		//boss����
		if (boss.flg < 3) {
			Boss(&img, &Map[0][0], &boss, &player, stx);
			if (BossCloss(&boss, &player, &stx, &sty) == 1) {
				gravity = ROBOT_GRAVITY_MAX;
			}
			//���E�Ɉړ���boss�A�j���[�V����
			Direction(&boss, &player, stx);
			if (BulletBossHit(bullet, &boss, &player, &stx, &sty) == 0) {
				if (boss.direction == 0) {
					dg_drawbmp6(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30, 384 - 50, 500 - 30, 0, RGB(255, 0, 255));
				}
				else {
					dg_drawbmp6(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30 + 500, 384 - 50, 500 - 30, 0, RGB(255, 0, 255));
				}
			}
			else {
				if (boss.direction == 0) {
					dg_drawbmp5(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30, 384 - 50, 500 - 30, 80, RGB(255, 0, 255));
					for (i = 0; i < 8; i++) {
						dg_drawbmp5(bb, boss.x + stx + 170 - rand() % 40, bullet[i].y, 64, 64, img.Damage_Effect, 0, 0, 64, 64, 100, RGB(255, 0, 255));
						break;
					}
				}
				else {
					dg_drawbmp5(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30 + 500, 384 - 50, 500 - 30, 80, RGB(255, 0, 255));
					for (i = 0; i < 8; i++) {
						dg_drawbmp5(bb, boss.x + stx + 240 + rand() % 40, bullet[i].y, 64, 64, img.Damage_Effect, 0, 0, 64, 64, 100, RGB(255, 0, 255));
						break;
					}
				}
			}
			if (player.deadlyflg == 5)
			{
				if (BulletBossHitdeadly(bullet, &boss, &player, &stx, &sty) == 0) {
					if (boss.direction == 0) {
						dg_drawbmp6(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30, 384 - 50, 500 - 30, 0, RGB(255, 0, 255));
					}
					else {
						dg_drawbmp6(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30 + 500, 384 - 50, 500 - 30, 0, RGB(255, 0, 255));
					}
				}
				else {
					if (boss.direction == 0) {
						dg_drawbmp5(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30, 384 - 50, 500 - 30, 80, RGB(255, 0, 255));
						for (i = 0; i < 8; i++) {
							dg_drawbmp5(bb, boss.x + stx + 170 - rand() % 40, bullet[i].y, 64, 64, img.Damage_Effect, 0, 0, 64, 64, 100, RGB(255, 0, 255));
							break;
						}
					}
					else {
						dg_drawbmp5(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0 + 384 * boss.pflg, 30 + 500, 384 - 50, 500 - 30, 80, RGB(255, 0, 255));
						for (i = 0; i < 8; i++) {
							dg_drawbmp5(bb, boss.x + stx + 240 + rand() % 40, bullet[i].y, 64, 64, img.Damage_Effect, 0, 0, 64, 64, 100, RGB(255, 0, 255));
							break;
						}
					}
				}
			}
		}

		if (boss.cnt % 6 == 0) { boss.pflg++; }
		if (boss.pflg > 7) { boss.pflg = 0; }

		//�����p����
		if (boss.flg == 3) {
			if (boss.motionwait == -1) {
				ds_stop("bgm");
				ds_play2("sound/explosion.wav");
				boss.cnt = 0;
			}
			for (i = 0; i < 2; i++) {
				gear[i].flag = 0;
			}
			for (i = 0; i < 6; i++) {
				bom[i].flag = 0;

			}
			if (boss.flg == 3){
				boss.motionwait++;
			}
			if (boss.motionwait > 800) {
				boss.flg = 4;
				boss.x = 0;
				boss.y = 0;
			}
			BossFinish(&img, &boss, &player, &stx, &sty, &flg);
			if (boss.direction == 0) {
				dg_drawbmp6(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0, 30, 384 - 50, 500 - 30, 0, RGB(255, 0, 255));
			}
			else {
				dg_drawbmp6(bb, boss.x + stx, -boss.y - sty, 384 + 50, 500 + 90, img.boss, 0, 30 + 500, 384 - 50, 500 - 30, 0, RGB(255, 0, 255));
			}
			for (i = 0; i < 8; i++) {
				if (boss.explosion[i] > 0) {
					dg_drawbmp4(bb, boss.x + stx + (boss.explosionx[i]), -(boss.y) - sty + (boss.explosiony[i]), 94 + (boss.explosionr[i]), 94 + (boss.explosionr[i]), img.explosion, 96 * (boss.explosion[i] - 1), 0, 94, 94, RGB(255, 0, 255));
				}
			}

		}

		//�X�e�[�W, �M�~�b�N�`��
		dg_drawbmp3(bb, 0, 0, 1280, 720, map_bmp, -stx, sty + 2680, RGB(0, 0, 0));
		Floor_Gimmick(&k, &kf, &k2, &k2f);
		GimmickDrawStage(&Map[0][0], img.MapChip, img.Objectbmp, img.Move_Floor, stx, sty, k, &Mfx, &Mfy, k2);

		if (boss.flg < 3) {
			if (boss.flg != 4) {
				BossBomAtack(&img, &boss, &player, &bom[0], &stx, &sty, bullet, &gravity);
				BossGearAtack(&img, &boss, &gear[0], &player, &bom[0], &stx, &sty, bullet, &gravity);
			}
		}

		Shadow(&Map[0][0], &stx, &sty, &player.x, &player.y, img.shadow, k);

		//���@����=================================================================================
		if (getch3(VK_ESCAPE) == 1) {
			*eflg = 0;
			break;
		}
		if (boss.flg != 4) {

			if (player.deadlyflg <= 3) {
				Player_Move(&player, jumpFlg, &img, Bullet_CNT, Frame, &Animation_CNT,
					&Map[0][0], &stx, &sty, jumpFlg, &ScrollCnt, k, &robee, &save_x);
			}


			//���@�A�G�@�����蔻��
			if (player.deadlyflg <= 3) {
				Atari_Judge(&player, E, &Player_Get_Damage, img, &Animation_CNT, &stx, &sty, &gravity, &Map[0][0], &ScrollCnt);
			}


			// �X�e�[�W�d�͏���
			sty += gravity;
			if (sty > 0) { sty = 0; }

			//���ݎ�l�����W�ۑ�
			Save_Player_X = player.x;
			Save_Player_Y = player.y;
			//�v���C���[�d�͏���
			//�v���C���[�d�͏���
			Player_Gravity(&player, &pushFlg, &jumpFlg, &Gkasoku, &gravity,
				&Map[0][0], &stx, &sty, k, kf, k2, k2f, &*eflg, &save_y, &BossStageFlag);

			//���{�b�g�d�͏���
			Robot_gravity(&robee);
			//�Ǐ]���[�h
			Robot_TYPE1(player, &robee, &Map[0][0], k, &stx, &sty);



			//�W�����v�֐�
			if (player.deadlyflg <= 3) {
				JumpFunc(&pushFlg, &jumpFlg, &gravity, img, player, Frame, &save_x, &save_y);
			}

			if (bullet[TMAX - 1].flg == 0) { Frame++; }
			if (player.deadlyflg <= 3) {
				if (getch3('D') == 1) {
					Bullet_Shot2(player, bullet, &Bullet_CNT, Frame, img, jumpFlg);
				}
			}
			//�K�E�p�J�E���g
			if (player.deadlyflg == 4)
			{
				Savecnt++;
				if (Savecnt >= 160)
				{
					player.deadlyflg = 5;
				}
			}
			if (player.deadlyflg == 0)
			{
				Savecnt = 0;
			}

			//�e�ړ�
			Bullet_Move(bullet, &Map[0][0], stx, sty, img, player);
			for (i = 0; i < TMAX; i++) {
				if (bullet[i].flg == 4 || bullet[i].flg == 5) { Bullet_Atari_Judge(bullet, E, i); }
			}
			//�����[�h
			if (player.deadlyflg <= 3) {
				Bullet_Reload(player, bullet, &Frame, &Bullet_CNT);
			}

		}

			//��l���`��
			deadlyflg = Draw_Player(&player, img, &Animation_CNT, jumpFlg, Frame, Bullet_CNT);
			Anime_Frame++;
			if (Anime_Frame > 5000) { Anime_Frame = 0; }
			if (Anime_Frame % ANIMATION_INTERVAL == 0) {
				Animation_CNT++;
			}

		

		//���{�b�g�`��
		if (deadlyflg == 0) {
			if (player.direction == DIRECTION_RIGHT) {
				dg_drawbmp3(bb, robee.x, robee.y, RobotW, RobotH, img.Robee, f * 32, 0, RGB(255, 0, 255));
			}
			else {
				dg_drawbmp3(bb, robee.x, robee.y, RobotW, RobotH, img.Robee, 64 + f * 32, 0, RGB(255, 0, 255));
			}
		}

		//HP�\��
		if (boss.flg != 4) {
			dg_drawbmp3(bb, 5, 5, 518, 226, img.HP, 0, 0, RGB(255, 0, 255));
			for (i = 0; i < Player_Life; i++) {
				if (Player_Life - (Player_Life - player.life) > i) {
					if (player.life > 4) {
						dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, 0, 227, RGB(255, 0, 255));
					}
					else if (player.life > 2) {
						dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, 0, 297, RGB(255, 0, 255));
					}
					else {
						if (Frame % 60 > 30) {
							dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, 0, 367, RGB(255, 0, 255));
						}
					}
				}
				else {
					if (HP_Animation_CNT[i] < 4) {
						if (player.life > 3) {
							dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, HP_Animation_CNT[i] * 44, 227, RGB(255, 0, 255));
						}
						else if (player.life > 2) {
							dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, HP_Animation_CNT[i] * 44, 297, RGB(255, 0, 255));
						}
						else {
							dg_drawbmp3(bb, i * 31 + 198, 33, 44, 69, img.HP, HP_Animation_CNT[i] * 44, 367, RGB(255, 0, 255));
						}
						if (Anime_Frame % ANIMATION_INTERVAL == 0) {
							HP_Animation_CNT[i]++;
						}
					}
				}
			}
			dg_setfont(30, 70, "IMPACT");
			if (Frame > 100) {
				if (Bullet_CNT != 0) {
					dg_printf2(bb, 299, 99, RGB(255, 255, 255), -1, "%02d", Bullet_CNT);
				}
			}
			dg_deletefont();
			dg_setfont(15, 30, "MS�S�V�b�N");
			if (Bullet_CNT == 0) {
				dg_printf2(bb, 275, 115, RGB(250, 0, 0), -1, "EMPTY!!");
			}
			if (Frame < 100) {
				dg_printf2(bb, 280, 115, RGB(0, 0, 230), -1, "RELOAD");
			}
			dg_deletefont();

			//�K�E
			dg_drawbmp5(bb, 405, 102, 60, 60, img.HP, 60, 625, 60, 60, 100, RGB(255, 0, 255));
			if (player.deadlyflg == 1) {
				player.deadlycnt++;
				player.deadly--;
				if (player.deadlycnt > 10) {
					player.deadlycnt = 0;
					player.deadlyflg = 0;
				}
			}
			if (player.deadly < 0) {
				player.deadly = 0;
				player.deadlyflg = 2;
			}
			//�Q�[�W
			if (player.deadlyflg == 0 || player.deadlyflg == 1) {
				dg_drawbmp5(bb, 405, 102 + player.deadly, 60, 60 - player.deadly, img.HP, 0, 625 + player.deadly, 60, 60 - player.deadly, 100, RGB(255, 0, 255));
			}

			if (player.deadlyflg == 2) {
				player.deadlycnt += 2;
				if (player.deadlycnt > 100) { player.deadlyflg = 3; }
				dg_drawbmp5(bb, 405, 102 + player.deadly, 60, 60 - player.deadly, img.HP, 0, 625 + player.deadly, 60, 60 - player.deadly, 100 - player.deadlycnt, RGB(255, 0, 255));
			}
			if (player.deadlyflg == 3) {
				player.deadlycnt -= 2;
				if (player.deadlycnt < 0) { player.deadlyflg = 2; }
				dg_drawbmp5(bb, 405, 102 + player.deadly, 60, 60 - player.deadly, img.HP, 0, 625 + player.deadly, 60, 60 - player.deadly, 100 - player.deadlycnt, RGB(255, 0, 255));
			}
		}

		//clear�p����
		if (boss.flg == 4) {
			boss.x++;
			if (boss.x > 100) {
				boss.x = 100;
				boss.y++;
			}

			dg_box(bb, 0, 0, 1280, boss.x, 1, RGB(0, 0, 0));
			dg_box(bb, 0, 720, 1280, -boss.x, 1, RGB(0, 0, 0));
			if (boss.y > 100) {
				if (boss.y > 600) {
					*eflg = 0;
					break;

				}
				if (boss.y == 101) { ds_play1("sound/clear.wav"); }
				dg_drawbmp5(bb, 0 - 50, 0 - 150, 1280, 720, img.clear, 0, 0, 1280 - 150, 720 - 200, boss.y - 100, RGB(255, 0, 255));
			}
		}
		//�t�F�[�hin
		if(boss.y>500){
			dg_drawbmp5(bb, 0 , 0, 1280, 720, img.fade, 0, 0, 1280, 720, boss.y - 500, RGB(255, 0, 255));
		}
		if (ScrollCnt < 0) { ScrollCnt = 1280; }
		if (ScrollCnt > 1280) { ScrollCnt = 0; }

		if (CutinCNT != 0) {
			dg_drawbmp(bb, -1000 + ((CutinCNT < 30) ? CutinCNT * 32 : CutinCNT * 50), 360 - 150, 1280, 300, Cut_in);
		}

		//�Q�[���I�[�o�[����
		if (player.life <= 0) {
			player.life--;
			dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, -player.life, RGB(15, 0, 0));
			if (player.life < -100) {
				*eflg = 99;
				break;
			}
		}

				//�t���b�v
		dg_flip(gvram, bb);
		ML();
	}
	//�������J��
	dg_deletebmp(Cut_in);
	dg_deletebmp(map_bmp);
	Delete_Img(&img);
	ds_stop("bgm");
	return;

}


int m = 0;

void GameOver(int *ef) {
	char_far BOX;

	//�r�b�g�}�b�v���[�h
	IMG img;
	Load_Img(&img);

	//�t�F�[�h�p�摜�쐬
	BOX = dg_createbmp(40, 40);
	dg_box(BOX, 0, 0, 40, 40, 1, RGB(255, 255, 255));


	int cnt = 0, i = 0;
	char mcnt = 0;
	char flg = 0;

	//FPS����
	unsigned long starttime;
	starttime = NOW;
	int static unsigned long st = 0, fpscnt = 0, scnt = 0;

	do {
		//��ʃN���A
		dg_gcls(bb, RGB(0, 0, 0));
		//FPS����
		if (NOW - starttime < 1000 / 60) { continue; }
		starttime = NOW;
		if (NOW - st > 1000) {
			scnt = fpscnt;
			st = NOW;
			fpscnt = 0;
		}

		//�`�揈��
		dg_drawbmp5(bb, 80, 0, 1280 * 1.5, 720 * 1.5, img.gameover, 0, 0, 1280, 720, cnt, RGB(255, 0, 255));//GameOver
		if (cnt > 50) {
			dg_drawbmp5(bb, 550, 400, 128 * 1.5, 128 * 1.5, img.Player_Animation, 0, 2048 - 128, 128, 128, cnt - 50, RGB(255, 0, 255));//player
			dg_drawbmp5(bb, 500, 400, 277, 45, img.cntinue, 0, 0, 277, 45, cnt - 50, RGB(255, 0, 255));//continue
			dg_drawbmp5(bb, 420, 500, 100, 45, img.cntinue, 0, 45, 100, 45, cnt - 50, RGB(255, 0, 255));//YES
			dg_drawbmp5(bb, 820, 500, 100, 45, img.cntinue, 0, 90, 100, 45, cnt - 50, RGB(255, 0, 255));//NO
			if (cnt < 150) { dg_drawbmp5(bb, 420 - 50, 500, 30, 30, BOX, 0, 0, 40, 40, cnt - 50, -1); }
		}

		//selectBOX�o��AND�I������
		if (cnt > 150) {
			if (i > 360) { i = 0; }
			if (flg == 0) {
				dg_drawbmp6(bb, 420 - 50, 500, 30, 30, BOX, 0, 0, 40, 40, i, -1);
				if (getch3(VK_RETURN)) {
					ds_play1("sound/robot-footstep2.wav");
					*ef = m;
					mcnt++;
				}

			}
			else {
				dg_drawbmp6(bb, 820 - 50, 500, 30, 30, BOX, 0, 0, 40, 40, i, -1);
				if (getch3(VK_RETURN)) {
					ds_play1("sound/robot-footstep2.wav");
					*ef = 0;
					mcnt++;
				}

			}
			if (getch3(VK_LEFT)) {
				flg = 0;
				ds_play1("sound/button60.wav");
			}
			if (getch3(VK_RIGHT)) {
				flg = 1;
				ds_play1("sound/button60.wav");
			}
			i += 2;

		}
		if (getch3(VK_ESCAPE) == 1) {
			*ef = 0;
		}
		if (mcnt > 0) {
			dg_drawbmp5(bb, 0, 0, 1280, 720, img.fade, 0, 0, 1280, 720, mcnt, -1);
			mcnt++;
			if (mcnt > 100) { break; }
		}

		//�o���^�C�}�[�̃J�E���g����
		cnt++;
		if (cnt > 1000) { cnt = 1000; }
		//�t���b�v
		dg_flip(gvram, bb);
		ML();


	} while (ef != 0);
	//�������J��
	dg_deletebmp(map_bmp);
	Delete_Img(&img);
	ds_stop("bgm");

	return;
}