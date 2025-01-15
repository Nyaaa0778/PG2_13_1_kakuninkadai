#include "Enemy.h"
#include "Vector2.h"
#include <Novice.h>

Enemy::Enemy(Vector2 pos, float speed) {
  pos_ = pos;
  speed_ = speed;
  radius_ = 32.0f;
}

/// <summary>
/// 敵の移動処理
/// </summary>
void Enemy::Update() {
  pos_.x += speed_;

  if (pos_.x + radius_ >= 1280.0f || pos_.x - radius_ <= 0.0f) {
    speed_ = -speed_;
  }
}

/// <summary>
/// 敵の描画処理
/// </summary>
void Enemy::Draw() {
  if (Enemy::isAlive_) {
    Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
                        static_cast<int>(radius_), static_cast<int>(radius_),
                        0.0f, WHITE, kFillModeSolid);
  }
}