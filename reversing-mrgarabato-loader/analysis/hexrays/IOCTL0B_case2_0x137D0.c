__int64 __fastcall sub_137D0(__int64 a1, unsigned __int16 *a2)
{
  __int64 v4; // rdx
  __int64 v5; // rdi
  unsigned __int16 v6; // si
  __int64 i; // r8
  __int64 v8; // rdx
  __int64 v9; // rbx
  __int64 v11; // [rsp+20h] [rbp-18h] BYREF
  int v12; // [rsp+28h] [rbp-10h]

  v11 = 0LL;
  v12 = 0;
  sub_132B0(&v11);
  v5 = v11;
  v6 = 0;
  for ( i = v11; v6 < *a2; i = *(_QWORD *)(i + 584) )
  {
    if ( !i )
      break;
    v8 = v6++;
    v4 = 264 * v8;
    *(_BYTE *)(v4 + a1) = *(_BYTE *)i;
    *(_DWORD *)(v4 + a1) ^= (*(_DWORD *)i ^ *(_DWORD *)(v4 + a1)) & 0x1F00;
    *(_DWORD *)(v4 + a1) ^= (*(_DWORD *)i ^ *(_DWORD *)(v4 + a1)) & 0xE000;
  }
  if ( v5 )
  {
    do
    {
      ObfDereferenceObject(*(_QWORD *)(v5 + 48), v4, i);
      v9 = *(_QWORD *)(v5 + 584);
      ExFreePoolWithTag(v5);
      v5 = v9;
    }
    while ( v9 );
  }
  *a2 = v6;
  return 0LL;
}