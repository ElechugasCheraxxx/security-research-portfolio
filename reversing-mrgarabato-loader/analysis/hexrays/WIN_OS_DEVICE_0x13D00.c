__int64 __fastcall sub_13D00(__int64 a1, __int64 a2)
{
  __int64 v4; // rax

  if ( !a1 || !a2 )
    return 1LL;
  memmove((void *)(a2 + 8), (const void *)(a1 + 8), 0x108uLL);
  *(_BYTE *)(a2 + 296) = *(_BYTE *)(a1 + 296);
  *(_QWORD *)a2 = *(_QWORD *)a1;
  *(_QWORD *)(a2 + 272) = *(_QWORD *)(a1 + 272);
  *(_QWORD *)(a2 + 288) = *(_QWORD *)(a1 + 288);
  v4 = *(_QWORD *)(a1 + 280);
  *(_BYTE *)(a2 + 336) = 0;
  *(_QWORD *)(a2 + 280) = v4;
  *(_DWORD *)(a2 + 320) = *(_DWORD *)(a2 + 368);
  *(_DWORD *)(a2 + 308) = *(_DWORD *)(a2 + 356);
  *(_BYTE *)(a2 + 304) = *(_BYTE *)(a2 + 352);
  *(_QWORD *)(a2 + 312) = *(_QWORD *)(a2 + 360);
  sub_11F30("FillKernelContext: VirtualAddress: %p\n");
  return 0LL;
}