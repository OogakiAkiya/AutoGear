//ロボット関数
void Robot_gravity(ROBEE *robee);
void Robot_TYPE1(PLAYER p, ROBEE *robee, char *p_map, int k, int *stx, int *sty);

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

