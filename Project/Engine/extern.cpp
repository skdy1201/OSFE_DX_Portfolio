#include "pch.h"
#include "global.h"

tTransform g_Transform = {};
tGlobalData g_global = {};


const char* ASSET_TYPE_STRING[(UINT)ASSET_TYPE::END]
{
	"MESH",
	"MESHDATA",
	"PREFAB",
	"TEXTURE",
	"MATERIAL",
	"SOUND",
	"COMPUTE_SHADER",
	"GRAPHICS_SHADER",
	"FSM",
};

const char* COMPONENT_TYPE_STRING[(UINT)COMPONENT_TYPE::END]
{

	"TRANSFORM",	// 오브젝트의 위치,크기,회전
	"COLLIDER2D",	// 2차원 충돌체
	"COLLIDER3D", // 3차원 충돌체
	"ANIMATOR2D",	// 스프라이트 Animation
	"ANIMATOR3D",	// Bone Skinning Animation
	"LIGHT2D",	// 2차원 광원
	"LIGHT3D",	// 3차원 광원
	"CAMERA",		// 카메라 기능
	"STATEMACHINE", // 상태머신

	// Render Component
	"MESHRENDER",
	"TILEMAP",
	"PARTICLESYSTEM",
	"SKYBOX",
	"DECAL",
	"LANDSCAPE",

};