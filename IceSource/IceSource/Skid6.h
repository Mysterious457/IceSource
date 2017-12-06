#pragma once
//getfield
unsigned long getSkId = SKID(0x732da0);
//settop
unsigned long SkIdtop = SKID(0x734ed0);
//pushstring
unsigned long pushSkId = SKID(0x734150);
//pushvalue
unsigned long SkIdvalue = SKID(0x734210);
//call
unsigned long SkIds = SKID(0x732730);
//setfield
unsigned long setSkId = SKID(0x734af0);
//pushnumber
unsigned long hOwMaNySkIdS = SKID(0x7340c0);
//contextlevel/identity
unsigned long SKIDLEVEL = SKID(0x5a8180);
//ScriptContextVFTable
unsigned long SkIdTab = SKID(0x6bb00e);
//getmetatable
unsigned long DOGGO = SKID(0x733090);
//pcall
unsigned long pSkId = SKID(0x733b80);
//rawrjz
unsigned long miaujz = SKID(0x72c4c7);

int Skidtest;
int SkidState;
int skid = 220;

void SKIDD() {
	using namespace std;
	DWORD SkIdT = *(DWORD*)(SkIdTab + 0x2);
	Skidtest = SkId::ScanforSkid((char*)&SkIdT);
	//luastate
	SkidState = *(DWORD*)(Skidtest + skid) - (Skidtest + skid);
}