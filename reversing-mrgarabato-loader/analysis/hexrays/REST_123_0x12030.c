unsigned __int64 __fastcall sub_12030(const void *a1, unsigned int a2, __int64 a3)
{
  unsigned int v5; // ebx
  __int64 Mdl; // rax
  __int64 v8; // rdi
  const void *locked; // rax
  unsigned __int64 v10; // rsi
  __int64 v11; // rcx
  unsigned __int64 result; // rax
  int v13[6]; // [rsp+30h] [rbp-28h] BYREF

  v5 = 0;
  v13[0] = 0;
  while ( _InterlockedCompareExchange64((volatile signed __int64 *)&unk_3E7A40 + 5 * v5 + 3, (signed __int64)v13, 0LL) )
  {
    v5 = ++v13[0];
    if ( v13[0] >= 0xC350u )
      goto LABEL_6;
  }
  v5 = v13[0];
LABEL_6:
  sub_11F30("_NalWinGetUserAddress: Using memory map table slot %d - Length %d\n", v5, a2);
  sub_11F30("PAGE_SIZE * (65535 - sizeof(MDL)) / sizeof(ULONG_PTR) = %d\n", 33529344LL);
  if ( v5 < 0xC350 )
  {
    sub_11F30("_NalWinGetUserAddress: KernelLevelAddress = 0x%p\n", a1);
    Mdl = IoAllocateMdl(a1, a2, 0LL, 0LL, 0LL);
    v8 = Mdl;
    if ( Mdl )
    {
      MmBuildMdlForNonPagedPool(Mdl);
      locked = (const void *)MmMapLockedPagesSpecifyCache(v8, 1LL, 1LL, 0LL, 0, 16);
      v10 = (unsigned __int64)locked;
      if ( locked )
      {
        sub_11F30("_NalWinGetUserAddress: Address To Free = 0x%p\n", locked);
        v11 = 5LL * v5;
        *((_QWORD *)&unk_3E7A40 + v11 + 3) = v10;
        *((_QWORD *)&unk_3E7A40 + v11 + 2) = v8;
        *((_QWORD *)&unk_3E7A40 + v11 + 1) = a1;
        *((_QWORD *)&unk_3E7A40 + v11 + 4) = a3;
        result = (v10 & 0xFFFFFFFFFFFFF000uLL) + *(unsigned int *)(v8 + 44);
        *((_QWORD *)&unk_3E7A40 + v11) = result;
        return result;
      }
      sub_11F30("_NalWinGetUserAddress: MmMapLockedPages failed. Freeing MDL\n");
      IoFreeMdl(v8);
    }
    else
    {
      sub_11F30("_NalWinGetUserAddress: Unable to allocate MDL\n");
    }
  }
  return 0LL;
}