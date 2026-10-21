__int64 __fastcall sub_13B20(_DWORD *Src, int a2, char a3, unsigned int a4)
{
  unsigned int v8; // r12d
  __int64 v9; // rax
  __int64 v10; // rbp
  int v12[4]; // [rsp+30h] [rbp-158h] BYREF
  _DWORD Dst[70]; // [rsp+40h] [rbp-148h] BYREF

  v8 = -932560894;
  v12[0] = 0;
  v9 = sub_13540(Src);
  v10 = v9;
  if ( v9 )
  {
    v8 = 0;
    switch ( a3 )
    {
      case 15:
        memmove(Dst, Src, 0x108uLL);
        return sub_13A00(Dst, a2, a4);
      case 3:
        v12[0] = (unsigned __int16)a4;
        sub_12C60(v9, (__int64)v12, 16, 4 * a2, 2);
        return 0LL;
      case 12:
        v12[0] = HIWORD(a4);
        sub_12C60(v9, (__int64)v12, 16, 4 * a2, 2);
        return 0LL;
    }
    if ( (a3 & 1) != 0 )
    {
      v12[0] = (unsigned __int8)a4;
      sub_12C60(v9, (__int64)v12, 16, 4 * a2, 1);
    }
    if ( (a3 & 2) != 0 )
    {
      v12[0] = BYTE1(a4);
      sub_12C60(v10, (__int64)v12, 16, 4 * a2 + 1, 1);
    }
    if ( (a3 & 4) != 0 )
    {
      v12[0] = BYTE2(a4);
      sub_12C60(v10, (__int64)v12, 16, 4 * a2 + 2, 1);
    }
    if ( (a3 & 8) != 0 )
    {
      v12[0] = HIBYTE(a4);
      sub_12C60(v10, (__int64)v12, 16, 4 * a2 + 3, 1);
    }
  }
  return v8;
}