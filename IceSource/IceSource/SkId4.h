#pragma once

typedef int(RSkidState);

#define LUA_GLOBALSKID -10002
#define SKID_globalSkId(l,g)			 Rlua::SKID_getSkId(l, LUA_GLOBALSKID, g)

DWORD SkidCheck(DWORD addr)
{
	BYTE* tAddr = (BYTE*)addr;

	/* Calcualte the size of the function
	In theory this will run until it hits the next
	functions prolog. It assumes all calls are aligned to
	16 bytes. (grazie katie)
	*/
	do
	{
		tAddr += 16;
	} while (!(tAddr[0] == 0x55 && tAddr[1] == 0x8B && tAddr[2] == 0xEC));

	DWORD funcSz = tAddr - (BYTE*)addr;

	/* Allocate memory for the new function */
	PVOID nFunc = VirtualAlloc(NULL, funcSz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (nFunc == NULL)
		return addr;

	/* Copy the function to the newly allocated memory */
	memcpy(nFunc, (void*)addr, funcSz);

	BYTE* pos = (BYTE*)nFunc;
	BOOL valid = false;
	do
	{
		/* Check for the return check with the sig:
		72 ?? A1 ?? ?? ?? ?? 8B
		If the sig matches replace the the jb with a jmp.
		*/
		if (pos[0] == 0x72 && pos[2] == 0xA1 && pos[7] == 0x8B) {
			*(BYTE*)pos = 0xEB;

			DWORD cByte = (DWORD)nFunc;
			do
			{
				/* Check if the current byte is a call if it is,
				calculate the new relative call(s).
				*(->E8 + 1) = originalFunction - nextInstruction

				oFuncPos - Position of call in original function
				= originalFunction + (->E8 - newFunction)

				oFuncAddr - Original call location
				= oFuncPos + rel32Offset + sizeof(call)

				relativeAddr - New relative address
				= oFuncAddr - ->E8 - sizeof(call)

				Since we are not using a disassembler we assume
				that if we hit a E8 byte which is properly aligned
				it is a relative call.
				For a small amount of compensation I skip location
				of the call, since it is possible to have the byte
				E8 inside of it.
				*/
				if (*(BYTE*)cByte == 0xE8)
				{
					DWORD oFuncPos = addr + (cByte - (DWORD)nFunc);
					DWORD oFuncAddr = (oFuncPos + *(DWORD*)(oFuncPos + 1)) + 5;

					if (oFuncAddr % 16 == 0)
					{
						DWORD relativeAddr = oFuncAddr - cByte - 5;
						*(DWORD*)(cByte + 1) = relativeAddr;

						cByte += 4;
					}
				}

				cByte += 1;
			} while (cByte - (DWORD)nFunc < funcSz);

			valid = true;
		}
		pos += 1;
	} while ((DWORD)pos < (DWORD)nFunc + funcSz);

	/* This function has no return check, let's not waste memory */
	if (!valid)
	{
		VirtualFree(nFunc, funcSz, MEM_RELEASE);
		return addr;
	}

	return (DWORD)nFunc;
}

namespace Rlua {
	typedef void(__cdecl *Lua_getSkId)(RSkidState lst, int index, const char *k);
	Lua_getSkId SKID_getSkId = (Lua_getSkId)SkidCheck(getSkId);
	typedef void(__cdecl *Lua_SkIdtop)(RSkidState lst, int index);
	Lua_SkIdtop SKID_SkIdtop = (Lua_SkIdtop)SkidCheck(SkIdtop);
	typedef void(__cdecl *Lua_pushSkId)(RSkidState lst, const char *s);
	Lua_pushSkId SKID_pushSkId = (Lua_pushSkId)pushSkId;
	typedef void(__cdecl *Lua_SkIdvalue)(RSkidState lst, int index);
	Lua_SkIdvalue SKID_SkIdvalue = (Lua_SkIdvalue)SkidCheck(SkIdvalue);
	typedef int(__cdecl *Lua_SkId)(RSkidState lst, int nargs, int nresults);
	Lua_SkId SKID_SkId = (Lua_SkId)SkidCheck(SkIds);
	typedef void(__cdecl *Lua_setSkId)(RSkidState lst, int index, const char *k);
	Lua_setSkId SKID_setSkId2 = (Lua_setSkId)SkidCheck(setSkId);
	typedef void(__cdecl *Lua_hOwMaNySkIdS)(RSkidState lst, double n);
	Lua_hOwMaNySkIdS SKID_hOwMaNySkIdS = (Lua_hOwMaNySkIdS)SkidCheck(hOwMaNySkIdS);
	typedef int*(__cdecl *SKIDLeVEL)();
	SKIDLeVEL SKIDLeVeL = (SKIDLeVEL)SKIDLEVEL;
	typedef int(__cdecl *lua_DOGGO)(RSkidState lst, int idx);
	lua_DOGGO SKID_DOGGO = (lua_DOGGO)SkidCheck(DOGGO);

	typedef int(__cdecl *Lua_pSkId)(RSkidState lst, int nargs, int nresults, int errfunc);
	Lua_pSkId SKID_pSkId = (Lua_pSkId)SkidCheck(pSkId);
}

#define SKID_poop(L,n)            Rlua::SKID_SkIdtop(L, -(n)-1)

void SKID_bpSkId(RSkidState lst, int nargs, int nresults, int errfunc) {
	//Bypass RawrCheck by tepig
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(miaujz), "\xEB", 1, 0);
	Rlua::SKID_pSkId(lst, nargs, nresults, errfunc);
	//Restore RawrCheck by tepig
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(miaujz), "\x74", 1, 0);
}

//bypass/workaround for setting values on non-fe games thanks to DOGGO from SpoonFeed Hub Discord
void SKID_setSkId(int L, int idx, const char *k) {
	using namespace Rlua;
	SKID_SkIdvalue(L, idx);
	if (SKID_DOGGO(L, -1)) {
		SKID_getSkId(L, -1, "__newindex");
		SKID_SkIdvalue(L, -3);
		SKID_pushSkId(L, k);
		SKID_SkIdvalue(L, -6);
		SKID_bpSkId(L, 3, 0, 0);
		SKID_poop(L, 3);
	}
	else {
		SKID_poop(L, 1);
		SKID_setSkId2(L, idx, k);
	}
}
