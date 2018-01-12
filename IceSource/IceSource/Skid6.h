#pragma once
//getfield
unsigned long getSkId = SKID(0x72fe40);
//settop
unsigned long SkIdtop = SKID(0x731f80);
//pushstring
unsigned long pushSkId = SKID(0x7311f0);
//pushvalue
unsigned long SkIdvalue = SKID(0x7312c0);
//call
unsigned long SkIds = SKID(0x72f7c0);
//setfield
unsigned long setSkId = SKID(0x731ba0);
//pushnumber
unsigned long hOwMaNySkIdS = SKID(0x731160);
//contextlevel/identity
unsigned long SKIDLEVEL = SKID(0x5a6a90);
//ScriptContextVFTable
unsigned long SkIdTab = SKID(0x6b8dbe);
//getmetatable
unsigned long DOGGO = SKID(0x730130);
//pcall
unsigned long pSkId = SKID(0x730c20);
//rawrjz
unsigned long miaujz = SKID(0x729777);

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