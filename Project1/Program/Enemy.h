
// “GŠÖ”
void E_init(ENEMY *e, char *p_map);
void E_move(PLAYER *p, ENEMY *e, int stx, int sty, int Save_stx, int Save_sty, char *p_map);
void EShadow(ENEMY *e, int stx, int sty, char *p_map, char_far shadow);

//“G‘Î‰”ÍˆÍ”»’è
int Collision(PLAYER p, short ex, short ey, short dist);
//“G•ûŒü”»’è
int CheckDirection(int x1, int x2);


// “GŠÖ”==================================================================================================
//“G‰Šú‰»
void E_init(ENEMY *e, char *p_map) {
	int i;

	for (i = 0; i < ENEMY_CNT; i++) {
		(e + i)->cnt = 0;
		(e + i)->excnt = 0;
		(e + i)->bcnt = 0;
		(e + i)->dist = 600;
		(e + i)->hp = ENEMY_HP;
		(e + i)->apper = 1;
		(e + i)->atari_flg = 0;
		(e + i)->flg = 0;
		(e + i)->vec = 1;
		(e + i)->bflg = 0;
		(e + i)->aflg = 0;
	}


	for (; i < ENEMY_CNT + ENEMY_CNT2; i++) {
		(e + i)->cnt = 0;
		(e + i)->excnt = 0;
		(e + i)->bcnt = 0;
		(e + i)->dist = 600;
		(e + i)->hp = ENEMY_HP;
		(e + i)->apper = 1;
		(e + i)->atari_flg = 0;
		(e + i)->flg = 0;
		(e + i)->vec = 1;
		(e + i)->bflg = 0;
		(e + i)->aflg = 0;
	}

	return;

}

//“Gˆ—
void E_move(PLAYER *p, ENEMY *e, int stx, int sty, int Save_stx, int Save_sty, char *p_map)
{
	unsigned char i, j, l, m, Bsize = 20, EBZ = 10;
	short left, right, down, up;


	for (i = 0, l = ENEMY_CNT - 1; i < ENEMY_CNT + ENEMY_CNT2; i++, l--) {
		//“G, “G’eÀ•W‚ğstx, sty‚É‘Î‰‚³‚¹‚é
		(e + i)->x += stx - Save_stx;
		if (i >= ENEMY_CNT) {
			(e + i)->y -= sty - Save_sty;
		}
		if ((e + i)->bflg) {
			(e + i)->bx += stx - Save_stx;
			(e + i)->by -= sty - Save_sty;
		}


		if ((e + i)->apper == 1) {

			//EMP0, 2, EBM, “G, “G‚Ì’e“–‚½‚è”»’è‘S‚Ä
			(e + i)->vec = CheckDirection(p->x, (e + i)->x);
			if (Collision(*p, (e + i)->x, (e + i)->y, (e + i)->dist)) {
				(e + i)->flg = 1;
			}


			//“Gver.1ˆ—
			if (i < ENEMY_CNT)
			{
				//“Gver.1’eˆ—
				if (!(e + i)->bflg && (e + i)->flg && !(e + i)->aflg) {
					(e + i)->aflg = 1;
				}

				//“GƒAƒjƒ[ƒVƒ‡ƒ“ˆ—
				if ((e + i)->aflg) {
					if ((e + i)->aflg == 1) {
						(e + i)->cnt++;
					}
					if ((e + i)->cnt > 60) {
						(e + i)->aflg = 2;
						(e + i)->cnt -= 20;
					}
					if ((e + i)->aflg == 2) {
						(e + i)->cnt--;
						if ((e + i)->cnt == 0) {
							(e + i)->aflg = 0;
						}
					}
				}

				//’e”­Ëˆ—
				if ((e + i)->cnt == 60) {
					if ((e + i)->vec == 1) {
						(e + i)->bx = (e + i)->x - Bsize;
						(e + i)->by = (e + i)->y + (ENEMY_H / 2) + EBZ;
						(e + i)->bflg = 1;
					}
					if ((e + i)->vec == 2) {
						(e + i)->bx = (e + i)->x + ENEMY_W - Bsize;
						(e + i)->by = (e + i)->y + (ENEMY_H / 2) + EBZ;
						(e + i)->bflg = 2;
					}
				}


				//“G“¯m‚Ì“–‚½‚è”»’è
				for (j = 1, m = ENEMY_CNT - 1; j < ENEMY_CNT; m--, j++)
				{
					// ‰E‘¤
					if ((e + j - 1)->x < (e + j)->x + ENEMY_W &&
						(e + j - 1)->x + ENEMY_W >(e + j)->x &&
						(e + j - 1)->y < (e + j)->y + ENEMY_H &&
						(e + j - 1)->y + ENEMY_H >(e + j)->y ||
						(e + m)->x < (e + m - 1)->x + ENEMY_W &&
						(e + m)->x + ENEMY_W >(e + m - 1)->x &&
						(e + m)->y < (e + m - 1)->y + ENEMY_H &&
						(e + m)->y + ENEMY_H >(e + m - 1)->y)
					{
						(e + j)->flg = 0;
						(e + j - 1)->flg = 0;
						(e + m)->flg = 0;
						(e + m - 1)->flg = 0;
					}
				}


				//“G‚ÌˆÚ“®”»’è
				if (p->x - 200 < ((e + i)->x + ENEMY_W) &&
					p->x + PlayerW + 200 > ((e + i)->x))
				{
					(e + i)->flg = 0;
				}

				//ˆÚ“®ˆ—

				if ((e + i)->flg) {
					if ((e + i)->vec == 1) {
						(e + i)->x -= ESP;
					}
					if ((e + i)->vec == 2) {
						(e + i)->x += ESP;
					}
				}

			} 
			else if(i >= ENEMY_CNT)
			{
				//“Gver.2’eˆ—
				if (!(e + i)->bflg && (e + i)->flg && !(e + i)->aflg) {
					(e + i)->aflg = 1;
				}

				//“GƒAƒjƒ[ƒVƒ‡ƒ“ˆ—
				if ((e + i)->aflg) {
					if ((e + i)->aflg == 1) {
						(e + i)->cnt++;
					}
					if ((e + i)->cnt > 60) {
						(e + i)->aflg = 2;
					}
					if ((e + i)->aflg == 2) {
						(e + i)->cnt--;
						if ((e + i)->cnt == 0) {
							(e + i)->aflg = 0;
						}
					}
				}

				//’e”­Ëˆ—
				if ((e + i)->cnt == 60) {
					if ((e + i)->vec == 1) {
						(e + i)->bx = (e + i)->x - Bsize;
						(e + i)->by = (e + i)->y + (ENEMY_H / 2) - 5;
						(e + i)->bflg = 1;
					}
					if ((e + i)->vec == 2) {
						(e + i)->bx = (e + i)->x + ENEMY_W - Bsize;
						(e + i)->by = (e + i)->y + (ENEMY_H / 2) - 5;
						(e + i)->bflg = 2;
					}
				}
			}
		}
		if (i < ENEMY_CNT) {
			//“G“–‚½‚è”»’è
			//¶‰E“–‚½‚è”»’è
			left = ((-stx + (e + i)->x) / 64);
			right = ((-stx + (e + i)->x + ENEMY_W) / 64);
			up = ((((sty)+(e + i)->y + 2680 - ENEMY_H) / 64) * StageW);
			down = ((((sty)+(e + i)->y + 2680 - 32) / 64) * StageW);

			if ((*(p_map + (left + up))) == 6 || (*(p_map + (left + up))) == 7 || (*(p_map + (left + up))) == 8 ||
				(*(p_map + (left + up))) == 10 || (*(p_map + (left + up))) == 11 || (*(p_map + (left + up))) == 12 ||
				(*(p_map + (left + up))) == 14 || (*(p_map + (left + up))) == 15 || (*(p_map + (left + up))) == 16 ||
				(*(p_map + (left + down))) == 6 || (*(p_map + (left + down))) == 7 || (*(p_map + (left + down))) == 8 ||
				(*(p_map + (left + down))) == 10 || (*(p_map + (left + down))) == 11 || (*(p_map + (left + down))) == 12 ||
				(*(p_map + (left + down))) == 14 || (*(p_map + (left + down))) == 15 || (*(p_map + (left + down))) == 16)
			{
				(e + i)->x = (((e + i)->Sx / 64) * 64) + stx;
			}

			if ((*(p_map + (right + up))) == 6 || (*(p_map + (right + up))) == 7 || (*(p_map + (right + up))) == 8 ||
				(*(p_map + (right + up))) == 10 || (*(p_map + (right + up))) == 11 || (*(p_map + (right + up))) == 12 ||
				(*(p_map + (right + up))) == 14 || (*(p_map + (right + up))) == 15 || (*(p_map + (right + up))) == 16 ||
				(*(p_map + (right + down))) == 6 || (*(p_map + (right + down))) == 7 || (*(p_map + (right + down))) == 8 ||
				(*(p_map + (right + down))) == 10 || (*(p_map + (right + down))) == 11 || (*(p_map + (right + down))) == 12 ||
				(*(p_map + (right + down))) == 14 || (*(p_map + (right + down))) == 15 || (*(p_map + (right + down))) == 16)
			{
				(e + i)->x = (((e + i)->Sx / 64) * 64 + 32) + stx;
			}

			//“Gver.1d—Íˆ—
			e[i].Sx = e[i].x - stx;
			e[i].y -= sty - Save_sty;
				
			//ã‰º“–‚½‚è”»’è
			right = ((-stx + (e + i)->x + ENEMY_W + 1) / 64);
			down = ((((sty)+(e + i)->y + 2680 + BlockSIZE) / 64) * StageW);
			if (!((*(p_map + (left + down))) == 6 || (*(p_map + (left + down))) == 7 || (*(p_map + (left + down))) == 8 ||
				(*(p_map + (left + down))) == 10 || (*(p_map + (left + down))) == 11 || (*(p_map + (left + down))) == 12 ||
				(*(p_map + (left + down))) == 14 || (*(p_map + (left + down))) == 15 || (*(p_map + (left + down))) == 16 ||
				(*(p_map + (right + down))) == 6 || (*(p_map + (right + down))) == 7 || (*(p_map + (right + down))) == 8 ||
				(*(p_map + (right + down))) == 10 || (*(p_map + (right + down))) == 11 || (*(p_map + (right + down))) == 12 ||
				(*(p_map + (right + down))) == 14 || (*(p_map + (right + down))) == 15 || (*(p_map + (right + down))) == 16))
			{
				(e + i)->y += ENEMY_GRAVITY;
			}
		}

		//“G‚Ì’eˆ—
		if((e + i)->bflg) {
			//’eˆÚ“®ˆ—
			if ((e + i)->bflg == 1) {
				(e + i)->bx -= (ESP + 3);
				(e + i)->bcnt++;
			}
			else
				if ((e + i)->bflg == 2) {
					(e + i)->bx += (ESP + 3);
					(e + i)->bcnt++;
				}


			if ((e + i)->bcnt > 160)
			{
				(e + i)->bflg = 0;
				(e + i)->flg = 0;
				(e + i)->bcnt = 0;
			}
			left = ((-stx + (e + i)->bx) / 64);
			right = ((-stx + (e + i)->bx + 20) / 64);
			up = ((((sty)+(e + i)->by + 2680 - ENEMY_H) / 64) * StageW);
			down = ((((sty)+(e + i)->by + 2680 - 32) / 64) * StageW);
			if ((*(p_map + (left + up))) == 6 || (*(p_map + (left + up))) == 7 || (*(p_map + (left + up))) == 8 ||
				(*(p_map + (left + up))) == 10 || (*(p_map + (left + up))) == 11 || (*(p_map + (left + up))) == 12 ||
				(*(p_map + (left + up))) == 14 || (*(p_map + (left + up))) == 15 || (*(p_map + (left + up))) == 16 ||
				(*(p_map + (left + down))) == 6 || (*(p_map + (left + down))) == 7 || (*(p_map + (left + down))) == 8 ||
				(*(p_map + (left + down))) == 10 || (*(p_map + (left + down))) == 11 || (*(p_map + (left + down))) == 12 ||
				(*(p_map + (left + down))) == 14 || (*(p_map + (left + down))) == 15 || (*(p_map + (left + down))) == 16)
			{
				(e + i)->bflg = 0;
				(e + i)->bcnt = 0;
				(e + i)->flg = 0;
			}

			if ((*(p_map + (right + up))) == 6 || (*(p_map + (right + up))) == 7 || (*(p_map + (right + up))) == 8 ||
				(*(p_map + (right + up))) == 10 || (*(p_map + (right + up))) == 11 || (*(p_map + (right + up))) == 12 ||
				(*(p_map + (right + up))) == 14 || (*(p_map + (right + up))) == 15 || (*(p_map + (right + up))) == 16 ||
				(*(p_map + (right + down))) == 6 || (*(p_map + (right + down))) == 7 || (*(p_map + (right + down))) == 8 ||
				(*(p_map + (right + down))) == 10 || (*(p_map + (right + down))) == 11 || (*(p_map + (right + down))) == 12 ||
				(*(p_map + (right + down))) == 14 || (*(p_map + (right + down))) == 15 || (*(p_map + (right + down))) == 16)
			{
				(e + i)->bflg = 0;
				(e + i)->bcnt = 0;
				(e + i)->flg = 0;
			}
		}

	}

	return;
}



//ƒvƒŒƒCƒ„[“–‚½‚è”»’è
int Collision(PLAYER p, short ex, short ey, short dist) {
	if (p.x < (ex + ENEMY_W) + dist &&
		p.x + PlayerW >(ex - dist) &&
		p.y < (ey + ENEMY_H) + dist &&
		p.y + PlayerH >(ey - dist))
	{
		return HIT;
	}
	else {
		return NOHIT;
	}
}

//‰æ‘œ‚Ì\‘¢‘Ì‚©‚çˆê‚Â‚¾‚¯”²ˆ
void EShadow(ENEMY *e, int stx, int sty, char *p_map, char_far shadow) {
	unsigned char i, j;
	int down, center;
	//distanceX‚Í•ªŠ„‚Ì‚½‚ß, distanceY‚Í‰e‚Ì”Z’W‚ğ•Ï‚¦‚é‚½‚ß
	short distanceL, distanceR, distanceH;

	for (i = 0; i < ENEMY_CNT; i++) {
		distanceL = 0;
		distanceR = 0;
		distanceH = 0;

		//‰e‚ğ2‚Â‚ÉŠ„‚éˆ—
		down = ((((sty)+(e + i)->y + 2680 + BlockSIZE) / 64) * StageW);
		//0`40
		for (j = 0; j <= 80; j += 5) {
			center = ((-stx + (e + i)->x + 5 + j) / 64);
			if (((*(p_map + ((center)+down))) == 6 || (*(p_map + ((center)+down))) == 7 || (*(p_map + ((center)+down))) == 8 ||
				(*(p_map + ((center)+down))) == 10 || (*(p_map + ((center)+down))) == 11 || (*(p_map + ((center)+down))) == 12 ||
				(*(p_map + ((center)+down))) == 14 || (*(p_map + ((center)+down))) == 15 || (*(p_map + ((center)+down))) == 16 ||
				(*(p_map + ((center)+down))) == 18 || (*(p_map + ((center)+down))) == 19))
			{
				distanceL = j;
				break;
			}
		}
		//0`40
		for (j = 0; j <= 80; j += 5) {
			center = ((-stx + (e + i)->x - 15 + ENEMY_W - j) / 64);
			if (((*(p_map + ((center)+down))) == 6 || (*(p_map + ((center)+down))) == 7 || (*(p_map + ((center)+down))) == 8 ||
				(*(p_map + ((center)+down))) == 10 || (*(p_map + ((center)+down))) == 11 || (*(p_map + ((center)+down))) == 12 ||
				(*(p_map + ((center)+down))) == 14 || (*(p_map + ((center)+down))) == 15 || (*(p_map + ((center)+down))) == 16 ||
				(*(p_map + ((center)+down))) == 19))
			{
				distanceR = j;
				break;
			}
		}

		//‰e‚ğ‰º‚É—‚Æ‚·ˆ—
		if (distanceL)
		{
			center = ((-stx + (e + i)->x + 5 + distanceL - 5) / 64);
			for (j = 0; j <= 16; j++)
			{
				down = ((((sty)+(e + i)->y + 2680 + BlockSIZE + (j * 16)) / 64) * StageW);
				if (!((*(p_map + ((center)+down))) == 6 || (*(p_map + ((center)+down))) == 7 || (*(p_map + ((center)+down))) == 8 ||
					(*(p_map + ((center)+down))) == 10 || (*(p_map + ((center)+down))) == 11 || (*(p_map + ((center)+down))) == 12 ||
					(*(p_map + ((center)+down))) == 14 || (*(p_map + ((center)+down))) == 15 || (*(p_map + ((center)+down))) == 16))
				{
					distanceH += 16;
				}
				else {
					break;
				}
			}
		}
		else
			if (distanceR)
			{
				center = ((-stx + (e + i)->x - 15 + ENEMY_W - distanceR + 5) / 64);
				for (j = 0; j <= 16; j++)
				{
					down = ((((sty)+(e + i)->y + 2680 + BlockSIZE + (j * 16)) / 64) * StageW);
					if (!((*(p_map + ((center)+down))) == 6 || (*(p_map + ((center)+down))) == 7 || (*(p_map + ((center)+down))) == 8 ||
						(*(p_map + ((center)+down))) == 10 || (*(p_map + ((center)+down))) == 11 || (*(p_map + ((center)+down))) == 12 ||
						(*(p_map + ((center)+down))) == 14 || (*(p_map + ((center)+down))) == 15 || (*(p_map + ((center)+down))) == 16 ||
						(*(p_map + ((center)+down))) == 19))
					{
						distanceH += 16;
					}
					else {
						break;
					}
				}
			}
			else {
				center = ((-stx + (e + i)->x + 5 + (ENEMY_W / 2)) / 64);
				for (j = 0; j <= 16; j++)
				{
					down = ((((sty)+(e + i)->y + 2680 + BlockSIZE + (j * 16)) / 64) * StageW);
					if (!((*(p_map + ((center)+down))) == 6 || (*(p_map + ((center)+down))) == 7 || (*(p_map + ((center)+down))) == 8 ||
						(*(p_map + ((center)+down))) == 10 || (*(p_map + ((center)+down))) == 11 || (*(p_map + ((center)+down))) == 12 ||
						(*(p_map + ((center)+down))) == 14 || (*(p_map + ((center)+down))) == 15 || (*(p_map + ((center)+down))) == 16 ||
						(*(p_map + ((center)+down))) == 19))
					{
						distanceH += 16;
					}
					else
					{
						break;
					}
				}
			}

			//“G‚Ì‰e•`‰æ
			if ((e + i)->apper == 1) {
				if (abs((e + i)->x - Player_DEFAULT_X) <= StageW * 2) {
					//’Êí
					if (!distanceL && !distanceR)
					{
						dg_drawbmp5(bb, e[i].x + 5, e[i].y + 90 + 38 + distanceH, 80, 10, shadow, 2, 0, 80, 10, 100 - (60 + ((distanceH / 64) * 10)), RGB(255, 0, 255));
					}
					//¶‚É‚Í‚İo‚µ‚Ä‚¢‚é‚Æ‚«
					else
						if (distanceL) {
							getch();
							// ‚Í‚İo‚é•”•ª
							dg_drawbmp5(bb, e[i].x + 5, e[i].y + BlockSIZE * 2 + distanceH, distanceL, 10, shadow, 0, 0, distanceL, 10, 100 - (60 + ((distanceH / 64) * 10)), RGB(255, 0, 255));
							// ’n–Ê‚Éc‚é•”•ª
							dg_drawbmp5(bb, e[i].x + 5 + distanceL, e[i].y + 90 + 38, 80 - distanceL, 10, shadow, distanceL, 0, 80 - distanceL, 10, 100 - 60, RGB(255, 0, 255));
							dg_printf2(bb, 500, 0, RGB(255, 255, 255), -1, "disH = %d", distanceH);
						}
					//‰E‚É‚Í‚İ‚¾‚µ‚Ä‚¢‚é‚Æ‚«
						else
							if (distanceR) {
								// ‚Í‚İo‚é•”•ª
								dg_drawbmp5(bb, e[i].x + 5 + 80 - distanceR, e[i].y + BlockSIZE * 2 + distanceH, distanceR, 10, shadow, 82 - distanceR, 0, distanceR, 10, 100 - (60 + ((distanceH / 64) * 10)), RGB(255, 0, 255));
								// ’n–Ê‚Éc‚é•”•ª
								dg_drawbmp5(bb, e[i].x + 5, e[i].y + 90 + 38, 80 - distanceR, 10, shadow, 0, 0, 80 - distanceR, 10, 100 - 60, RGB(255, 0, 255));
								dg_printf2(bb, 500, 0, RGB(255, 255, 255), -1, "disH = %d", distanceH);
							}
				}
			}
	}
	return;
}

int CheckDirection(int x1, int x2) {
	if (x1 <= x2) {
		return LEFT;
	}
	if (x1 >= x2) {
		return RIGHT;
	}
	return 0;
}