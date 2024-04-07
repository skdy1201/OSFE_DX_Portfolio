#pragma once



#define DynamicMtrl GetRenderComponent()->GetDynamicMaterial() 

#define TileStartPointx -900
#define TileStartPointy -200

#define TileMaxRow 4
#define TileMaxCol 16

#define TileX 120
#define TileY 75

#define Tilespacex 3
#define Tilespacey 3


#define CursorZ  0.f
#define ProjectileZ 300.f

#define PlayerZ 500.f
#define TileZ 600.f
#define BackGroundZ 1000.f
#define PlayerAttackRange Vec2{4, 0}

#define BlueMagicLayer 9
#define RedMagicLayer 10

#define MagicFieldIndexY 7
#define MagicFieldIndexX 15


// 레이어 매크로
#define LayerDefault 0
#define LayerField 1
#define LayerTile 2
#define LayerPlayer 3
#define LayerMonster 4
#define LayerLight 5
#define LayerPlayerAttack 6
#define LayerMonsterAttack 7
#define LayerUI	31

// 프리팹 매크로
#define PrefabPlayer L"prefab\\temptest.pref"
#define PrefabPlayerBullet L"prefab\\PlayerBullet.pref"
#define PrefabPlayerBulletAnim L"prefab\\PlayerBulletAnim.pref"
#define PrefabPlayerSpawnAnim L"prefab\\PlayerSpawnAnim.pref"

#define PrefabSniper L"prefab\\SniperTest.pref"
#define PrefabSniperBullet L"prefab\\SniperBullet.pref"


#define PrefabPlayerCursor L"prefab\\PlayerCursor.pref"


// 에니메이션 매크로
#define frostblastanim FrostBlast
#define BulletBasicCast L"BasicCast"
#define SpawnEffect L"SaffronSpawnFX"

// FSM 매크로
#define BlackBoardPlayer (CGameObject*)GetBlackboardData(BBPlayer);
#define BlackBoardOwner (CGameObject*)GetBlackboardData(L"Owner");


//BB 매크로
#define  BBPlayer L"Player"
#define  MoveCooldown (float*)GetBlackboardData(L"MoveCooldown");
#define  AttackCooldown (float*)GetBlackboardData(L"AttackCooldown");
