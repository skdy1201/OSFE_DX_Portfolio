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

	"TRANSFORM",	// ������Ʈ�� ��ġ,ũ��,ȸ��
	"COLLIDER2D",	// 2���� �浹ü
	"COLLIDER3D", // 3���� �浹ü
	"ANIMATOR2D",	// ��������Ʈ Animation
	"ANIMATOR3D",	// Bone Skinning Animation
	"LIGHT2D",	// 2���� ����
	"LIGHT3D",	// 3���� ����
	"CAMERA",		// ī�޶� ���
	"STATEMACHINE", // ���¸ӽ�

	// Render Component
	"MESHRENDER",
	"TILEMAP",
	"PARTICLESYSTEM",
	"SKYBOX",
	"DECAL",
	"LANDSCAPE",

};

const char* MTRL_SCALAR_STRING[(UINT)SCALAR_PARAM::END]
{

	"INT_0",
	"INT_1",
	"INT_2",
	"INT_3",

	"FLOAT_0",
	"FLOAT_1",
	"FLOAT_2",
	"FLOAT_3",

	"VEC2_0",
	"VEC2_1",
	"VEC2_2",
	"VEC2_3",

	"VEC4_0",
	"VEC4_1",
	"VEC4_2",
	"VEC4_3",

	"MAT_0",
	"MAT_1",
	"MAT_2",
	"MAT_3"
};