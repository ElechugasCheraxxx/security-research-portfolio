__int64 __fastcall sub_13A00(_DWORD *a1, int a2, int a3)
{
  __int64 v4; // rbx
  __int64 v5; // rax
  __int64 v6; // rcx
  int v7; // r11d
  __int64 result; // rax
  int v9; // [rsp+40h] [rbp-48h]
  int v10; // [rsp+48h] [rbp-40h]
  char v11[32]; // [rsp+58h] [rbp-30h] BYREF
  int v12; // [rsp+A0h] [rbp+18h] BYREF

  v12 = a3;
  v4 = sub_13540(a1);
  if ( !v4 )
    return 3362406402LL;
  KeInitializeEvent(v11, 0LL, 0LL);
  v5 = IoBuildSynchronousFsdRequest(27LL, v4, 0LL);
  if ( !v5 || (v6 = *(_QWORD *)(v5 + 184) - 72LL, *(_QWORD *)(v5 + 184) == 72LL) )
  {
    v7 = v9;
  }
  else
  {
    *(_DWORD *)(v5 + 48) = -1073741637;
    *(_BYTE *)v6 = 27;
    *(_QWORD *)(v6 + 16) = &v12;
    *(_BYTE *)(v6 + 1) = 16;
    *(_DWORD *)(v6 + 32) = 4;
    *(_DWORD *)(v6 + 8) = 0;
    *(_DWORD *)(v6 + 24) = 4 * a2;
    v7 = IofCallDriver(v4, v5);
    if ( v7 == 259 )
    {
      KeWaitForSingleObject(v11, 0LL, 0LL, 0LL, 0LL);
      v7 = v10;
    }
  }
  result = 3362406409LL;
  if ( v7 >= 0 )
    return 0LL;
  return result;
}