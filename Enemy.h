#pragma once
#include"Vector2.h"

class Enemy {
public:
  /// <summary>
  /// インストラクタ
  /// </summary>
  /// <param name="pos"></param>
  /// <param name="speed"></param>
  Enemy(Vector2 pos, float speed);

  /// <summary>
  /// 敵の移動処理
  /// </summary>
  void Update();

  /// <summary>
  /// 敵の描画処理
  /// </summary>
  void Draw();

public:
  Vector2 pos_;
  float speed_;
  float radius_;

  static int isAlive_;
};
