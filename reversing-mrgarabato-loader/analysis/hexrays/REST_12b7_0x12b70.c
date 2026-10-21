__int64 __fastcall sub_12B70(__int64 a1, _WORD *a2)
{
  __int64 v4; // rax
  __int64 v5; // rcx
  unsigned int v7; // [rsp+40h] [rbp-38h]
  char v8[40]; // [rsp+50h] [rbp-28h] BYREF

  memset(a2, 0, 0x40uLL);
  *a2 = 64;
  a2[1] = 1;
  *((_DWORD *)a2 + 2) = -1;
  *((_DWORD *)a2 + 3) = -1;
  KeInitializeEvent(v8, 0LL, 0LL);
  v4 = IoBuildSynchronousFsdRequest(27LL, a1, 0LL);
  if ( !v4 )
    return 3221225626LL;
  v5 = *(_QWORD *)(v4 + 184);
  *(_DWORD *)(v4 + 48) = -1073741637;
  *(_BYTE *)(v5 - 72) = 27;
  *(_BYTE *)(v5 - 71) = 9;
  *(_QWORD *)(v5 - 64) = a2;
  if ( (unsigned int)IofCallDriver(a1, v4) == 259 )
    KeWaitForSingleObject(v8, 0LL, 0LL, 0LL, 0LL);
  return v7;
}