
int GetAngle(int Player_X1, int Player_Y1, int x2, int Player_Y2);
void Load_Img(IMG *img);
void Delete_Img(IMG *img);


//追尾角度計算関数
int GetAngle(int Player_X1, int Player_Y1, int Player_X2, int Player_Y2) {
	int kaku;
	double rad;

	if (Player_X1 == Player_X2 && Player_Y1 == Player_Y2) { return 270; }

	rad = atan2(Player_Y2 - Player_Y1, Player_X2 - Player_X1);
	kaku = rad*180.0 / 3.14159265358979;
	if (kaku < 0) { kaku += 360; }
	return kaku;
}

void Load_Img(IMG *img)
{
	int i;
	img->Player_Animation = dg_loadbmp("bmp/Player_Animation.bmp");
	img->Background = dg_loadbmp("bmp/mori2.bmp");
	img->Enemy1 = dg_loadbmp("bmp/E_TYPE1.bmp");
	img->Enemy2 = dg_loadbmp("bmp/E_TYPE2.bmp");
	img->MapChip = dg_loadbmp("bmp/mapchip_Forest.bmp");
	img->HP = dg_loadbmp("bmp/Chara_UI.bmp");
	img->explosion = dg_loadbmp("bmp/爆発.bmp");
	img->Bullet_Effect = dg_loadbmp("bmp/Bullet_Effect.bmp");
	img->Bullet = dg_loadbmp("bmp/Bullet.bmp");
	img->fade = dg_loadbmp("bmp/フェード.bmp");
	img->shadow = dg_loadbmp("bmp/shadow.bmp");
	img->Dash_Effect = dg_loadbmp("bmp/Dash_Effect.bmp");
	img->Objectbmp = dg_loadbmp("bmp/Object.bmp");
	img->Move_Floor = dg_loadbmp("bmp/Move_Floor.bmp");
	img->boss = dg_loadbmp("bmp/boss2.bmp");
	img->bom = dg_loadbmp("bmp/bom.bmp");
	img->gear = dg_loadbmp("bmp/歯車.bmp");
	img->clear = dg_loadbmp("bmp/CLEAR.bmp");
	img->E_bullet = dg_loadbmp("bmp/EnemyBullet.bmp");
	img->Damage_Effect = dg_loadbmp("bmp/Damage_Effect.bmp");
	img->Player = dg_loadbmp("bmp/Player.bmp");
	img->tns = dg_loadbmp("bmp/tns.bmp");
	img->Robee = dg_loadbmp("bmp/Robee.bmp");
	img->Robee_sp = dg_loadbmp("bmp/Robee_sp.bmp");
	img->Buster_Effect = dg_loadbmp("bmp/Buster_Effect.bmp");
	img->Continue = dg_loadbmp("bmp/Continue.bmp");
	img->Jump_Effect = dg_loadbmp("bmp/Jump_Effect.bmp");
	img->gameover = dg_loadbmp("bmp/Game Over.bmp");
	img->cntinue = dg_loadbmp("bmp/CONTINUE.bmp");

}

void Delete_Img(IMG *img)
{
	int i;
	dg_deletebmp(img->Player_Animation);
	dg_deletebmp(img->Background);
	dg_deletebmp(img->Enemy1);
	dg_deletebmp(img->Enemy2);
	dg_deletebmp(img->MapChip);
	dg_deletebmp(img->HP);
	dg_deletebmp(img->explosion);
	dg_deletebmp(img->Bullet_Effect);
	dg_deletebmp(img->Bullet);
	dg_deletebmp(img->fade);
	dg_deletebmp(img->shadow);
	dg_deletebmp(img->Dash_Effect);
	dg_deletebmp(img->Objectbmp);
	dg_deletebmp(img->Move_Floor);
	dg_deletebmp(img->boss);
	dg_deletebmp(img->bom);
	dg_deletebmp(img->gear);
	dg_deletebmp(img->clear);
	dg_deletebmp(img->E_bullet);
	dg_deletebmp(img->Damage_Effect);
	dg_deletebmp(img->Player);
	dg_deletebmp(img->tns);
	dg_deletebmp(img->Robee);
	dg_deletebmp(img->Robee_sp);
	dg_deletebmp(img->Buster_Effect);
	dg_deletebmp(img->Continue);
	dg_deletebmp(img->Jump_Effect);
	dg_deletebmp(img->gameover);
	dg_deletebmp(img->cntinue);

}
