__int64 __fastcall sub_11DE0(__int64 a1, __int64 a2)
{
  __int64 v2; // r9
  _QWORD *v3; // rax
  unsigned __int64 v4; // r8

  if ( a2 )
  {
    v2 = 0LL;
    v3 = &unk_17180;
    v4 = 0LL;
    while ( 1 )
    {
      if ( *(_QWORD *)(v4 + 4094560) == a2 && a1 == *(_QWORD *)(v4 + 4094528) )
      {
        a1 = qword_3E7A48[5 * v2];
        goto LABEL_11;
      }
      if ( v3[1] == a2 && a1 == *v3 )
        break;
      v4 += 40LL;
      ++v2;
      v3 += 10;
      if ( v4 >= 0x1E8480 )
        goto LABEL_11;
    }
    a1 = qword_17150[10 * v2];
  }
LABEL_11:
  if ( a1 )
    return MmGetPhysicalAddress(a1);
  else
    return 0LL;
}