//ロボット関数
void Robot_gravity(ROBEE *robee);
void Robot_TYPE1(PLAYER p, ROBEE *robee, char *p_map, int k, int *stx, int *sty);
//void Robot_TYPE2(PLAYER p, float *p_Robot_X, float *p_Robot_Y, float Robot_Gravity);


//ロボット重力処理関数
void Robot_gravity(ROBEE *robee)
{
	if (robee->gravityflg == 0) {
		robee->gravity += ROBOT_GRAVITY_SPEED;
		if (robee->gravity > ROBOT_GRAVITY_MAX) {
			robee->gravityflg = 1;
		}
	}

	if (robee->gravityflg == 1) {
		robee->gravity -= ROBOT_GRAVITY_SPEED;
		if (robee->gravity < ROBOT_GRAVITY_MIN) {
			robee->gravityflg = 0;
		}
	}
	return;
}

//ロボット追尾モード関数
void Robot_TYPE1(PLAYER p, ROBEE *robee, char *p_map, int k, int *stx, int *sty)
{
	int kaku;
	int i;

	robee->y += robee->gravity;

	if (p.direction == DIRECTION_RIGHT) {
		kaku = GetAngle(robee->x, robee->y, p.x + ROBOT_DEFAULT_POSITION_RIGHT_X, p.y + ROBOT_DEFAULT_POSITION_Y);
		robee->vy = sin(RAD(kaku));
		robee->y += robee->vy;

		robee->vx = cos(RAD(kaku))*RobotSPEED_X;
		robee->x += robee->vx;
	}
	else {
		kaku = GetAngle(robee->x, robee->y, p.x + ROBOT_DEFAULT_POSITION_LEFT_X, p.y + ROBOT_DEFAULT_POSITION_Y);
		robee->vy = sin(RAD(kaku)) * RobotSPEED_Y;
		robee->y += robee->vy;

		robee->vx = cos(RAD(kaku)) * RobotSPEED_X;
		robee->x += robee->vx;
	}

	return;
}

/*//ロボット銃弾跳ね返し関数
void Robot_TYPE2(PLAYER p, float *p_Robot_X, float *p_Robot_Y, float Robot_Gravity)
{
int kaku;
static int hankei = 101;
float Robot_X_Vector, Robot_Y_Vector;
int i;

if (p.direction == DIRECTION_RIGHT) {
kaku = GetAngle(*p_Robot_X, *p_Robot_Y, p.x + 500, p.y - 400);
Robot_Y_Vector = sin(RAD(kaku)) * RobotSPEED_Y;
*p_Robot_Y += Robot_Y_Vector;
Robot_X_Vector = cos(RAD(kaku)) * RobotSPEED_X;
*p_Robot_X += Robot_X_Vector;
if (hankei < 150 && hankei>100) {
hankei++;
}
else {
hankei = 101;
}
dg_circle(bb,*p_Robot_X + RobotW/2, *p_Robot_Y + RobotH/2, 1*hankei, RGB(255, 200, 200));
}
else {
kaku = GetAngle(*p_Robot_X, *p_Robot_Y, p.x + ROBOT_MIRROR_BULLETMODE_POSITION_LEFT_X, p.y + ROBOT_MIRROR_BULLETMODE_POSITION_Y);
Robot_Y_Vector = sin(RAD(kaku)) * RobotSPEED_Y;
*p_Robot_Y += Robot_Y_Vector;
Robot_X_Vector = cos(RAD(kaku)) * RobotSPEED_X;
*p_Robot_X += Robot_X_Vector;
}
return;
}
*/
