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