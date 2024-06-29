// ↓Debugモードを解除する場合はコメントアウトする
#define DEBUG


char_far gvram;
char_far bb;
char_far map_bmp;



//全般
#define MapWIDTH 1280//マップの幅
#define MapHEIGHT 720//マップの高さ
#define DIRECTION_LEFT 1//左を向いている
#define DIRECTION_RIGHT 0//右を向いている
#define PI 3.14159265358979
#define RAD(k) ((k)*3.14159265358979/180)//角度変換用
#define NOW timeGetTime()//FPS用


//ステージ関連---------------------------------------
#define StageW 400
#define StageH  50
#define BlockSIZE  64
#define StageMARGIN 5
#define MapGroundHEIGHT 200
#define CharaMARGIN 21
#define SCROLLSPEED 1.5
//-------------------------------------------------

//プレイヤー関連
#define PlayerW 128//プレイヤーの幅
#define PlayerH 128//プレイヤー高さ
#define Player_MOVE_SPEED 10//プレイヤー移動速度
#define Player_DEFAULT_X (MapWIDTH-PlayerW)/2//プレイヤーの初期座標（X）
#define Player_DEFAULT_Y MapHEIGHT-200-PlayerH//プレイヤーの初期座標（Y）
#define JUMPPOWER -9//ジャンプの高さ
#define PLAYER_GRAVITY_SPEED 0.4//プレイヤーの重力加速度
#define PLAYER_GRAVITY_MAX 6//プレイヤーの最大重力加速度
#define JUMPPOWER2 0.9//二段ジャンプ時の倍率(重力による抵抗を受ける為)
#define PLAYER_STAND_BY_MOTION 8//待機時のコマ数
#define PLAYER_DASH_MOTION 7//ダッシュ時のコマ数
#define ANIMATION_INTERVAL 5//コマ送りする間隔
#define Player_Life 10

//弾関連
#define TMAX 30//弾の最大値
#define BulletSPEED 45//弾の速度
#define Bullet_INTERVAL 5//弾発射間隔
#define Bullet_W 128
#define Bullet_H 64
#define RELOAD_NOW 1//リロード中
#define RELOAD_NOT 0//リロードしてない
#define FRAME_DEFAULT -4//リロード時間（小さくなれば長くなる）


//ロボット関連
#define RobotW 32//ロボットの幅
#define RobotH 32//ロボットの高さ
#define RobotSPEED_X 5//ロボット追尾速度（X）
#define RobotSPEED_Y 1//ロボット追尾速度（Y）
#define ROBOT_GRAVITY_SPEED 0.2//ロボットの重力加速度
#define ROBOT_GRAVITY_MAX 3.0//ロボットの最大重力加速度
#define ROBOT_GRAVITY_MIN -3.0//ロボットの最小重力加速度
#define ROBOT_DEFAULT_POSITION_RIGHT_X -30//プレイヤーが右を向いているときのロボットのX座標
#define ROBOT_DEFAULT_POSITION_LEFT_X 130//プレイヤーが左を向いているときのロボットのX座標
#define ROBOT_DEFAULT_POSITION_Y -40//プレイヤーが静止しているときのロボットのY座標

//敵関連
#define ENEMY_W 96//敵の幅
#define ENEMY_H 96//敵の高さ
#define ENEMY_INTERVAL0 500//敵移動切り替え間隔
#define ENEMY_HP 4
#define ESP 3//敵移動スピード
#define SCRMAX 4//敵行動パターン
#define ENEMY_CNT 23//敵の数
#define ENEMY_CNT2 9//敵2の数
#define ENEMY_GRAVITY 16//敵の重力判定


enum { NOHIT = 0, HIT = 1 } COLLISION;
enum { LEFT = 1, RIGHT } DIRECTION;

typedef struct BULLET
{
	short x;
	int y;
	short vy;
	char flg;
}BULLET;

typedef struct {	// 敵構造体
	short x;		// 敵座標
	short y;        //
	short Sx;		// 敵座標固定用
	short bx;		// 敵弾x座標
	short by;		// 敵弾y座標
	short dist;		// 敵当たり判定距離
	unsigned char cnt;		// 敵フレーム制御変数
	unsigned char bcnt;		// 弾フレーム
	unsigned char excnt;	// 爆発フレーム
	char flg;		// 敵状態
	char bflg;		// 敵弾状態
	char aflg;		// 敵アニメーションフラグ
	char vec;		// 自機から見た敵の方向
	int hp;
	char apper;
	char atari_flg;//自機とのあたりフラグ
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

///////////////////////ロビー/////////////////////////////////////
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