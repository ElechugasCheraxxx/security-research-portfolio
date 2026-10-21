__int64 __fastcall sub_13110(__int64 a1)
{
  __int64 v1; // rbx
  __int64 v3; // rax
  __int64 v4; // rdx
  int v5; // eax
  _QWORD *PoolWithTag; // rbx
  int v8; // [rsp+40h] [rbp-58h]
  __int64 v9; // [rsp+48h] [rbp-50h]
  char v10[24]; // [rsp+50h] [rbp-48h] BYREF
  int v11; // [rsp+68h] [rbp-30h]
  int v12; // [rsp+6Ch] [rbp-2Ch]
  int v13; // [rsp+70h] [rbp-28h]
  int v14; // [rsp+74h] [rbp-24h]
  int v15; // [rsp+78h] [rbp-20h]
  int v16; // [rsp+7Ch] [rbp-1Ch]
  __int64 v17; // [rsp+80h] [rbp-18h]

  v17 = qword_17108;
  v1 = *(_QWORD *)(a1 + 56);
  v11 = 0;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  v16 = 0;
  KeInitializeEvent(v10, 0LL, 0LL);
  v3 = IoBuildSynchronousFsdRequest(27LL, v1, 0LL);
  if ( v3 )
  {
    v4 = *(_QWORD *)(v3 + 184);
    *(_DWORD *)(v3 + 48) = -1073741637;
    *(_BYTE *)(v4 - 72) = 27;
    *(_BYTE *)(v4 - 71) = 21;
    v5 = IofCallDriver(v1, v3);
    if ( v5 == 259 )
    {
      KeWaitForSingleObject(v10, 0LL, 0LL, 0LL, 0LL);
      v5 = v8;
    }
    else if ( !v5 )
    {
      v5 = v8;
    }
    if ( v5 >= 0 )
    {
      v16 = *(_DWORD *)(v9 + 20);
      ExFreePoolWithTag(v9);
    }
  }
  PoolWithTag = (_QWORD *)ExAllocatePoolWithTag(1LL, 64LL, 543908932LL);
  if ( PoolWithTag )
  {
    *PoolWithTag = 0LL;
    PoolWithTag[1] = 0LL;
    PoolWithTag[2] = 0LL;
    PoolWithTag[3] = 0LL;
    PoolWithTag[4] = 0LL;
    PoolWithTag[5] = 0LL;
    PoolWithTag[6] = 0LL;
    PoolWithTag[7] = 0LL;
    sub_12B70(*(_QWORD *)(a1 + 56), PoolWithTag);
    *(_BYTE *)a1 = v16;
    *(_DWORD *)a1 ^= (*(_DWORD *)a1 ^ (*((_DWORD *)PoolWithTag + 2) >> 8)) & 0x1F00;
    *(_DWORD *)a1 ^= ((unsigned __int16)*(_DWORD *)a1 ^ (unsigned __int16)((unsigned __int16)*((_DWORD *)PoolWithTag + 2) << 13)) & 0xE000;
    ExFreePoolWithTag(PoolWithTag);
  }
  return 0LL;
}