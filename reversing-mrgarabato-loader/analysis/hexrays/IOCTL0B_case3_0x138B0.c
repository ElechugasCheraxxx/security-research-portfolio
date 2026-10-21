__int64 __fastcall sub_138B0(__int64 a1, void *a2, unsigned int a3)
{
  __int64 v5; // r12
  unsigned int v6; // ebx
  __int64 PoolWithTag; // rax
  const void *v8; // rdi
  __int64 v9; // rax
  int v10; // r8d

  v5 = a3;
  v6 = -932544510;
  PoolWithTag = ExAllocatePoolWithTag(0LL, 256LL, 543908932LL);
  v8 = (const void *)PoolWithTag;
  if ( a2 )
  {
    if ( !PoolWithTag )
      return v6;
    v9 = sub_13540(a1);
    if ( v9 )
    {
      LOBYTE(v10) = 15;
      sub_12C60(v9, (_DWORD)v8, v10, 0, 64);
      memmove(a2, v8, 4 * v5);
      v6 = 0;
    }
  }
  if ( v8 )
    sub_11DC0(v8, "c:\\users\\cloudbuild\\337244\\sdk\\nal\\src\\winnt_wdm\\driver\\windriverpci_i.c", 243LL);
  return v6;
}