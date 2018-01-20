#pragma once
//getfield
unsigned long getSkId = SKID(0x733D00);
//settop
unsigned long SkIdtop = SKID(0x735E40);
//pushstring
unsigned long pushSkId = SKID(0x736080);
//pushvalue
unsigned long SkIdvalue = SKID(0x735180);
//call
unsigned long SkIds = SKID(0x737A40);
//setfield
unsigned long setSkId = SKID(0x735A60);
//pushnumber
unsigned long hOwMaNySkIdS = SKID(0x735020);
//contextlevel/identity
unsigned long SKIDLEVEL = SKID(0x5A96E0);
//ScriptContextVFTable
unsigned long SkIdTab = SKID(0x6bbd00);
//getmetatable
unsigned long DOGGO = SKID(0x72E910);
//pcall
unsigned long pSkId = SKID(0x734AE0);
//rawrjz
unsigned long miaujz = SKID(0x72D320);

int Skidtest;
int SkidState;
int skid = 220;

void SKIDD() {
	using namespace std;
	DWORD SkIdT = *(DWORD*)(SkIdTab + 0x2);
	Skidtest = SkId::ScanforSkid((char*)&SkIdT);
	//luastate
	SkidState = Skidtest + skid + *(DWORD*)(Skidtest + skid);
}
