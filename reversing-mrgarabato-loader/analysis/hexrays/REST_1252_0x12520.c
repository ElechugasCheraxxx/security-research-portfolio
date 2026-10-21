void *__fastcall sub_12520(unsigned int a1, unsigned int a2, __int64 a3, unsigned __int64 *a4)
{
  unsigned __int64 v5; // rbp
  unsigned int v8; // ebx
  void *ContiguousMemory; // rax
  void *v11; // rsi
  __int64 v12; // rdi
  unsigned __int64 PhysicalAddress; // rax
  unsigned __int64 v14; // r11
  __int64 v15; // rbp
  unsigned __int64 *v16; // rdx
  _QWORD *v17; // rcx
  __int64 v18; // rax
  __int64 Mdl; // rax
  __int64 locked; // r11
  __int64 v21; // rax
  const void *v22; // rbx

  v5 = a2;
  v8 = 0;
  while ( _InterlockedCompareExchange((volatile signed __int32 *)&unk_17140 + 20 * v8, 1, 0) )
  {
    if ( ++v8 >= 0xC350 )
      return 0LL;
  }
  ContiguousMemory = (void *)MmAllocateContiguousMemory(a1 + a2, 0xFFFFFFFFLL);
  v11 = ContiguousMemory;
  if ( ContiguousMemory )
  {
    memset(ContiguousMemory, 0, a1 + (unsigned int)v5);
    v12 = 10LL * v8;
    *((_QWORD *)&unk_17140 + v12 + 1) = v11;
    *((_DWORD *)&unk_17140 + 2 * v12 + 11) = a1 + v5;
    *((_DWORD *)&unk_17140 + 2 * v12 + 10) = v5;
    PhysicalAddress = MmGetPhysicalAddress(v11);
    v14 = PhysicalAddress;
    *((_QWORD *)&unk_17140 + v12 + 4) = PhysicalAddress;
    if ( (_DWORD)v5 && (unsigned int)(PhysicalAddress % v5) )
    {
      v15 = (unsigned int)v5 - (unsigned int)(PhysicalAddress % v5);
      v16 = (unsigned __int64 *)((char *)&unk_17140 + 80 * v8 + 24);
      v11 = (void *)((unsigned int)v15 + *((_QWORD *)&unk_17140 + 10 * v8 + 1));
      v17 = (_QWORD *)((char *)&unk_17140 + 80 * v8 + 16);
      *v16 = v15 + PhysicalAddress;
      *v17 = v11;
    }
    else
    {
      v18 = *((_QWORD *)&unk_17140 + 10 * v8 + 1);
      v16 = (unsigned __int64 *)((char *)&unk_17140 + 80 * v8 + 24);
      v17 = (_QWORD *)((char *)&unk_17140 + 80 * v8 + 16);
      *v16 = v14;
      *v17 = v18;
    }
    if ( a4 )
      *a4 = *v16;
    if ( a3 )
    {
      Mdl = IoAllocateMdl(*v17, a1, 0LL, 0LL, 0LL);
      *((_QWORD *)&unk_17140 + 10 * v8 + 6) = Mdl;
      if ( Mdl )
      {
        MmBuildMdlForNonPagedPool(Mdl);
        locked = MmMapLockedPagesSpecifyCache(*((_QWORD *)&unk_17140 + 10 * v8 + 6), 1LL, 1LL, 0LL, 0, 16);
        *((_QWORD *)&unk_17140 + 10 * v8 + 7) = locked;
        if ( locked )
        {
          v21 = *((_QWORD *)&unk_17140 + 10 * v8 + 6);
          *((_QWORD *)&unk_17140 + 10 * v8 + 9) = a3;
          v22 = (const void *)((locked & 0xFFFFFFFFFFFFF000uLL) + *(unsigned int *)(v21 + 44));
          *((_QWORD *)&unk_17140 + v12 + 8) = v22;
          sub_11F30("_NalAllocateMemoryNonPaged - VirtualAddress = 0x%p\n", v22);
          return (void *)v22;
        }
        sub_11F30("_NalAllocateMemoryNonPaged - MmMapLockedPages failed. Freeing MDL\n");
        IoFreeMdl(*((_QWORD *)&unk_17140 + 10 * v8 + 6));
        *((_QWORD *)&unk_17140 + 10 * v8 + 6) = 0LL;
      }
    }
  }
  else
  {
    sub_11F30("_NalAllocateMemoryNonPaged - MmAllocateContiguousMemory failed\n");
    _InterlockedCompareExchange((volatile signed __int32 *)&unk_17140 + 20 * v8, 0, 1);
  }
  return v11;
}