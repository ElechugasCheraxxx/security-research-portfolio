__int64 __fastcall sub_13540(_DWORD *a1)
{
  __int64 v2; // rsi
  __int64 v3; // rdx
  __int64 v4; // r8
  __int64 v5; // rdi
  __int64 v6; // rbx
  unsigned int i; // r11d
  int v8; // ecx
  __int64 v9; // rbx
  __int64 v11; // [rsp+20h] [rbp-18h] BYREF
  unsigned int v12; // [rsp+28h] [rbp-10h]

  v2 = 0LL;
  v11 = 0LL;
  v12 = 0;
  sub_132B0(&v11);
  v5 = v11;
  v6 = v11;
  if ( a1 )
  {
    sub_11F30("Looking for match for %d/%d/%d\n", (unsigned __int8)*a1, (*a1 >> 8) & 0x1F, (unsigned __int16)*a1 >> 13);
    v4 = v12;
    for ( i = 0; i < v12; ++i )
    {
      if ( !v6 )
        break;
      v8 = *(_DWORD *)v6;
      v3 = (unsigned int)*a1;
      if ( (unsigned __int8)v3 == *(_BYTE *)v6
        && (((unsigned __int16)v3 ^ (unsigned __int16)v8) & 0x1F00) == 0
        && (((unsigned __int16)v3 ^ (unsigned __int16)v8) & 0xE000) == 0 )
      {
        v2 = *(_QWORD *)(v6 + 56);
      }
      v6 = *(_QWORD *)(v6 + 584);
    }
  }
  if ( v5 )
  {
    do
    {
      ObfDereferenceObject(*(_QWORD *)(v5 + 48), v3, v4);
      v9 = *(_QWORD *)(v5 + 584);
      ExFreePoolWithTag(v5);
      v5 = v9;
    }
    while ( v9 );
  }
  return v2;
}