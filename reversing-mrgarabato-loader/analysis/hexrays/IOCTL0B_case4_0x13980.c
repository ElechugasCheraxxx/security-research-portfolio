__int64 __fastcall sub_13980(_DWORD *a1, int a2, __int64 a3)
{
  __int64 v5; // rax
  int v6; // eax
  unsigned int v7; // ecx

  if ( !a3 )
    return 3362406402LL;
  v5 = sub_13540(a1);
  if ( !v5 )
    return 3362406402LL;
  v6 = sub_12C60(v5, a3, 15, 4 * a2, 4);
  v7 = -932560887;
  if ( v6 >= 0 )
    return 0;
  return v7;
}