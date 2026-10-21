__int64 __fastcall sub_11330(__int64 a1)
{
  if ( !a1 )
    return 1LL;
  if ( *(_QWORD *)a1 == 1LL )
  {
    if ( a1 != -16 )
      *(_DWORD *)(a1 + 16) = sub_13DF0(*(_QWORD *)(a1 + 24));
    return 0LL;
  }
  if ( *(_QWORD *)a1 != 2LL )
  {
    if ( *(_QWORD *)a1 != 3LL )
      return 3362398232LL;
    if ( a1 != -16 )
    {
      *(_DWORD *)(a1 + 16) = sub_13DF0(*(_QWORD *)(a1 + 24));
      return 0LL;
    }
    return 0LL;
  }
  if ( a1 != -16 )
    *(_BYTE *)(a1 + 20) = sub_13E00(*(_QWORD *)(a1 + 24));
  return 0LL;
}