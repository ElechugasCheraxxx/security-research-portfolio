char __fastcall sub_11220(__int64 *a1, char a2)
{
  __int64 v2; // r11
  char v3; // r10
  unsigned __int64 v4; // r8
  __int64 v5; // r9
  unsigned __int64 v6; // rax
  __int64 v7; // rax
  unsigned __int64 v8; // rcx
  char result; // al
  __int64 v10; // r8

  v2 = *a1;
  v3 = 0;
  v4 = 0LL;
  v5 = 0LL;
  v6 = 0LL;
  while ( *(_QWORD *)&byte_5CFEC0[v6] != v2 || byte_5CFEC0[v6 + 264] != 1 )
  {
    v6 += 272LL;
    ++v5;
    if ( v6 >= 0x11000 )
      goto LABEL_9;
  }
  if ( a2 )
  {
    v3 = 0;
  }
  else
  {
    v3 = 1;
    v7 = 272 * v5;
    byte_5CFEC0[v7 + 264] = 0;
    *(_QWORD *)&byte_5CFEC0[v7] = 0LL;
  }
LABEL_9:
  if ( v5 != 256 )
    return v3;
  if ( a2 == 1 )
  {
    v8 = 0LL;
    while ( *(_QWORD *)&byte_5CFEC0[v8] )
    {
      v8 += 272LL;
      ++v4;
      if ( v8 >= 0x11000 )
        return v3;
    }
    if ( v4 < 0x100 )
    {
      v10 = 272 * v4;
      result = 1;
      *(_QWORD *)&byte_5CFEC0[v10] = v2;
      byte_5CFEC0[v10 + 264] = 1;
      return result;
    }
    return v3;
  }
  result = v3;
  if ( !a2 )
    return 1;
  return result;
}