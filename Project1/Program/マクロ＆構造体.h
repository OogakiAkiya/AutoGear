// ��Debug���[�h����������ꍇ�̓R�����g�A�E�g����
#define DEBUG


char_far gvram;
char_far bb;
char_far map_bmp;



//�S��
#define MapWIDTH 1280//�}�b�v�̕�
#define MapHEIGHT 720//�}�b�v�̍���
#define DIRECTION_LEFT 1//���������Ă���
#define DIRECTION_RIGHT 0//�E�������Ă���
#define PI 3.14159265358979
#define RAD(k) ((k)*3.14159265358979/180)//�p�x�ϊ��p
#define NOW timeGetTime()//FPS�p


//�X�e�[�W�֘A---------------------------------------
#define StageW 400
#define StageH  50
#define BlockSIZE  64
#define StageMARGIN 5
#define MapGroundHEIGHT 200
#define CharaMARGIN 21
#define SCROLLSPEED 1.5
//-------------------------------------------------

//�v���C���[�֘A
#define PlayerW 128//�v���C���[�̕�
#define PlayerH 128//�v���C���[����
#define Player_MOVE_SPEED 10//�v���C���[�ړ����x
#define Player_DEFAULT_X (MapWIDTH-PlayerW)/2//�v���C���[�̏������W�iX�j
#define Player_DEFAULT_Y MapHEIGHT-200-PlayerH//�v���C���[�̏������W�iY�j
#define JUMPPOWER -9//�W�����v�̍���
#define PLAYER_GRAVITY_SPEED 0.4//�v���C���[�̏d�͉����x
#define PLAYER_GRAVITY_MAX 6//�v���C���[�̍ő�d�͉����x
#define JUMPPOWER2 0.9//��i�W�����v���̔{��(�d�͂ɂ���R���󂯂��)
#define PLAYER_STAND_BY_MOTION 8//�ҋ@���̃R�}��
#define PLAYER_DASH_MOTION 7//�_�b�V�����̃R�}��
#define ANIMATION_INTERVAL 5//�R�}���肷��Ԋu
#define Player_Life 10

//�e�֘A
#define TMAX 30//�e�̍ő�l
#define BulletSPEED 45//�e�̑��x
#define Bullet_INTERVAL 5//�e���ˊԊu
#define Bullet_W 128
#define Bullet_H 64
#define RELOAD_NOW 1//�����[�h��
#define RELOAD_NOT 0//�����[�h���ĂȂ�
#define FRAME_DEFAULT -4//�����[�h���ԁi�������Ȃ�Β����Ȃ�j


//���{�b�g�֘A
#define RobotW 32//���{�b�g�̕�
#define RobotH 32//���{�b�g�̍���
#define RobotSPEED_X 5//���{�b�g�ǔ����x�iX�j
#define RobotSPEED_Y 1//���{�b�g�ǔ����x�iY�j
#define ROBOT_GRAVITY_SPEED 0.2//���{�b�g�̏d�͉����x
#define ROBOT_GRAVITY_MAX 3.0//���{�b�g�̍ő�d�͉����x
#define ROBOT_GRAVITY_MIN -3.0//���{�b�g�̍ŏ��d�͉����x
#define ROBOT_DEFAULT_POSITION_RIGHT_X -30//�v���C���[���E�������Ă���Ƃ��̃��{�b�g��X���W
#define ROBOT_DEFAULT_POSITION_LEFT_X 130//�v���C���[�����������Ă���Ƃ��̃��{�b�g��X���W
#define ROBOT_DEFAULT_POSITION_Y -40//�v���C���[���Î~���Ă���Ƃ��̃��{�b�g��Y���W

//�G�֘A
#define ENEMY_W 96//�G�̕�
#define ENEMY_H 96//�G�̍���
#define ENEMY_INTERVAL0 500//�G�ړ��؂�ւ��Ԋu
#define ENEMY_HP 4
#define ESP 3//�G�ړ��X�s�[�h
#define SCRMAX 4//�G�s���p�^�[��
#define ENEMY_CNT 23//�G�̐�
#define ENEMY_CNT2 9//�G2�̐�
#define ENEMY_GRAVITY 16//�G�̏d�͔���


enum { NOHIT = 0, HIT = 1 } COLLISION;
enum { LEFT = 1, RIGHT } DIRECTION;

typedef struct BULLET
{
	short x;
	int y;
	short vy;
	char flg;
}BULLET;

typedef struct {	// �G�\����
	short x;		// �G���W
	short y;        //
	short Sx;		// �G���W�Œ�p
	short bx;		// �G�ex���W
	short by;		// �G�ey���W
	short dist;		// �G�����蔻�苗��
	unsigned char cnt;		// �G�t���[������ϐ�
	unsigned char bcnt;		// �e�t���[��
	unsigned char excnt;	// �����t���[��
	char flg;		// �G���
	char bflg;		// �G�e���
	char aflg;		// �G�A�j���[�V�����t���O
	char vec;		// ���@���猩���G�̕���
	int hp;
	char apper;
	char atari_flg;//���@�Ƃ̂�����t���O
} ENEMY;

typedef struct PLAYER
{
	short x;
	float y;
	char direction;
	int flg;
	char life;
	unsigned char InvincibleCnt;
	char deadly;
	char deadlycnt;
	char deadlyflg;
}PLAYER;

typedef struct IMAGES
{
	char_far Player_Animation;
	char_far Background;
	char_far Enemy1;
	char_far Enemy2;
	char_far MapChip;
	char_far HP;
	char_far explosion;
	char_far Bullet_Effect;
	char_far Bullet;
	char_far fade;
	char_far shadow;
	char_far Dash_Effect;
	char_far Objectbmp;
	char_far Move_Floor;
	char_far boss;
	char_far bom;
	char_far gear;
	char_far clear;
	char_far E_bullet;
	char_far Damage_Effect;
	char_far Player;
	char_far tns;
	char_far Robee;
	char_far Robee_sp;
	char_far Buster_Effect;
	char_far Continue;
	char_far Jump_Effect;
	char_far gameover;
	char_far cntinue;

}IMG;


////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BOSSX 2200
#define BOSSY 330
#define BOSSMAX 1280*2+320
#define BOSSMIN 64 * 3
typedef struct BOSS
{
	float x;
	float y;
	char direction;
	char flg;
	int cnt;
	char life;
	float kasoku;
	int bomcnt;
	int gearcnt;
	char attack;
	char pflg;
	int motionwait;
	int explosion[8];
	int explosionx[8];
	int explosiony[8];
	int explosionr[8];
}BOSS;
typedef struct BOM
{
	float x;
	float y;
	char flag;
	int cnt;
	float kasoku;
	char life;
}BOM;
typedef struct GEAR
{
	float x;
	float y;
	char flag;
	float cnt;
	float kasoku;
	float skasoku;
	char direction;
	char life;
	char attack;
}GEAR;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////���r�[/////////////////////////////////////
typedef struct
{
	short x;
	float y;
	float vx;
	float vy;
	float gravity;
	char flg;
	char gravityflg;
}ROBEE;