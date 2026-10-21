__int64 __fastcall sub_13640(int *a1, _QWORD *a2)
{
  unsigned int v4; // esi
  __int64 v5; // r8
  _QWORD *v6; // rdi
  _QWORD *v7; // rdx
  int v8; // ecx
  int v9; // r9d
  _QWORD *v10; // rbx
  void *Src; // [rsp+20h] [rbp-18h] BYREF
  unsigned int v13; // [rsp+28h] [rbp-10h]

  Src = 0LL;
  v13 = 0;
  v4 = -932560894;
  sub_132B0(&Src);
  v6 = Src;
  v7 = Src;
  if ( a1 )
  {
    v5 = 0LL;
    if ( v13 )
    {
      while ( v7 )
      {
        v8 = *(_DWORD *)v7;
        v9 = *a1;
        if ( (unsigned __int8)*a1 == *(_BYTE *)v7
          && (((unsigned __int16)v9 ^ (unsigned __int16)v8) & 0x1F00) == 0
          && (((unsigned __int16)v9 ^ (unsigned __int16)v8) & 0xE000) == 0 )
        {
          memmove(a2, v7, 0x250uLL);
          ObReferenceObjectByPointer(a2[6], &unk_1F01FF, 0LL, 0LL);
          v4 = 0;
          break;
        }
        v7 = (_QWORD *)v7[73];
        v5 = (unsigned int)(v5 + 1);
        if ( (unsigned int)v5 >= v13 )
          break;
      }
    }
  }
  if ( v6 )
  {
    do
    {
      ObfDereferenceObject(v6[6], v7, v5);
      v10 = (_QWORD *)v6[73];
      ExFreePoolWithTag(v6, 0LL);
      v6 = v10;
    }
    while ( v10 );
  }
  return v4;
}