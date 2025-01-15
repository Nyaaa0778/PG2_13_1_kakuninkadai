#include <Novice.h>
#define _USE_MATH_DEFINES
#include "Enemy.h"
#include <math.h>

const char kWindowTitle[] = "LC1B_26_ヤマダナオ_タイトル";

typedef struct Player {
  Vector2 pos;
  float speed;
  float radius;
} Player;

typedef struct Bullet {
  Vector2 pos;
  float speed;
  float radius;
  int isShoot;
} Bullet;

//静的メンバ変数
int Enemy::isAlive_ = true;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  // ライブラリの初期化
  Novice::Initialize(kWindowTitle, 1280, 720);

  // キー入力結果を受け取る箱
  char keys[256] = {0};
  char preKeys[256] = {0};

  Player player = {{640.0f, 680.0f}, 7.0f, 32.0f};

  Bullet bullet = {{0.0f, 0.0f}, 10.0f, 8.0f, false};

  Enemy *enemy[2] = {new Enemy({640.0f, 300.0f}, 4.0f),
                     new Enemy({640.0f, 400.0f}, 6.0f)};

  // ウィンドウの×ボタンが押されるまでループ
  while (Novice::ProcessMessage() == 0) {
    // フレームの開始
    Novice::BeginFrame();

    // キー入力を受け取る
    memcpy(preKeys, keys, 256);
    Novice::GetHitKeyStateAll(keys);

    ///
    /// ↓更新処理ここから
    ///

    //プレイヤーの移動処理
    if (keys[DIK_D]) {
      player.pos.x += player.speed;
    }
    if (keys[DIK_A]) {
      player.pos.x -= player.speed;
    }
    if (keys[DIK_S]) {
      player.pos.y += player.speed;
    }
    if (keys[DIK_W]) {
      player.pos.y -= player.speed;
    }

    //SPACEキーで弾発射
    if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
      if (!bullet.isShoot) {
        bullet.isShoot = true;
        bullet.pos = player.pos;
      }
    }

    if (bullet.isShoot) {
      bullet.pos.y -= bullet.speed;

      if (bullet.pos.y + bullet.radius <= 0.0f) {
        bullet.isShoot = false;
      }
    }

    //敵の移動処理
    for (int i = 0; i < 2; i++) {
      enemy[i]->Update();
    }

    //当たり判定
    for (int i = 0; i < 2; i++) {
      if (Enemy::isAlive_) {
        if (enemy[i]->radius_ + bullet.radius >=
            sqrtf(powf(enemy[i]->pos_.x - bullet.pos.x, 2) +
                  powf(enemy[i]->pos_.y - bullet.pos.y, 2))) {
          Enemy::isAlive_ = false;
          bullet.isShoot = false;
        }
      }
    }

    ///
    /// ↑更新処理ここまで
    ///

    ///
    /// ↓描画処理ここから
    ///

    // 敵の描画処理
    for (int i = 0; i < 2; i++) {
      enemy[i]->Draw();
    }

    //弾の描画処理
    if (bullet.isShoot) {
      Novice::DrawEllipse(
          static_cast<int>(bullet.pos.x), static_cast<int>(bullet.pos.y),
          static_cast<int>(bullet.radius), static_cast<int>(bullet.radius),
          0.0f, WHITE, kFillModeSolid);
    }

    // プレイヤーの描画処理
    Novice::DrawEllipse(
        static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
        static_cast<int>(player.radius), static_cast<int>(player.radius), 0.0f,
        WHITE, kFillModeSolid);

    ///
    /// ↑描画処理ここまで
    ///

    // フレームの終了
    Novice::EndFrame();

    // ESCキーが押されたらループを抜ける
    if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
      break;
    }
  }

  for (int i = 0; i < 2; i++) {
    delete enemy[i];
  }

  // ライブラリの終了
  Novice::Finalize();
  return 0;
}
