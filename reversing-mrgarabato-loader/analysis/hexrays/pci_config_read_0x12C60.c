__int64 __fastcall sub_12C60(__int64 a1, __int64 a2, char a3, int a4, int a5)
{
  __int64 v9; // rax
  __int64 v10; // rdx
  __int64 result; // rax
  unsigned int v12; // [rsp+40h] [rbp-58h]
  unsigned int v13; // [rsp+48h] [rbp-50h]
  char v14[32]; // [rsp+58h] [rbp-40h] BYREF

  KeInitializeEvent(v14, 0LL, 0LL);
  v9 = IoBuildSynchronousFsdRequest(27LL, a1, 0LL);
  if ( !v9 )
    return v12;
  v10 = *(_QWORD *)(v9 + 184) - 72LL;
  if ( *(_QWORD *)(v9 + 184) == 72LL )
    return v12;
  *(_DWORD *)(v9 + 48) = -1073741637;
  *(_BYTE *)v10 = 27;
  *(_DWORD *)(v10 + 32) = a5;
  *(_BYTE *)(v10 + 1) = a3;
  *(_QWORD *)(v10 + 16) = a2;
  *(_DWORD *)(v10 + 8) = 0;
  *(_DWORD *)(v10 + 24) = a4;
  result = IofCallDriver(a1, v9);
  if ( (_DWORD)result == 259 )
  {
    KeWaitForSingleObject(v14, 0LL, 0LL, 0LL, 0LL);
    return v13;
  }
  return result;
}