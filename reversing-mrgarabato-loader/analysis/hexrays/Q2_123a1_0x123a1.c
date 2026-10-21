__int64 __fastcall sub_12220(const void *a1, __int64 a2, unsigned int a3, const void *a4)
{
  __int64 v6; // r12
  const void **v7; // rbx
  unsigned int v8; // edi
  signed __int64 v9; // rax

  v6 = a3;
  if ( !a1 || !a3 )
    return 1LL;
  sub_11F30("NalUnmapAddressEx: Looking to unmap 0x%p, Length %d, ProcessId %d\n", a1, a3, a4);
  v7 = (const void **)&unk_3E7A40;
  v8 = 0;
  while ( 1 )
  {
    sub_11F30("NalUnmapAddressEx: Global_WinMemoryMapTable[%d].MappedAddress = 0x%p == 0x%p\n", v8, *v7, a1);
    if ( a4 == v7[4] && a1 == *v7 )
      break;
    ++v8;
    v7 += 5;
    if ( v8 >= 0xC350 )
      goto LABEL_15;
  }
  sub_11F30("NalUnmapAddressEx: Slot %d matched\n", v8);
  if ( *((_QWORD *)&unk_3E7A40 + 5 * v8 + 2) && *((_QWORD *)&unk_3E7A40 + 5 * v8 + 3) )
  {
    sub_11F30("NalUnmapAddressEx: Calling MmUnmapLockedPages\n");
    MmUnmapLockedPages(*((_QWORD *)&unk_3E7A40 + 5 * v8 + 3));
    IoFreeMdl(*((_QWORD *)&unk_3E7A40 + 5 * v8 + 2));
  }
  else
  {
    sub_11F30("NalUnmapAddressEx: Skipped MmUnmapLockedPages - AddressToFree or Mdl was NULL\n");
  }
  if ( *((_QWORD *)&unk_3E7A40 + 5 * v8 + 1) )
  {
    sub_11F30("NalUnmapAddressEx: Unmapping OriginalMemoryMapped\n");
    MmUnmapIoSpace(*((_QWORD *)&unk_3E7A40 + 5 * v8 + 1), v6);
  }
  v9 = *((_QWORD *)&unk_3E7A40 + 5 * v8 + 3);
  *((_QWORD *)&unk_3E7A40 + 5 * v8 + 2) = 0LL;
  *((_QWORD *)&unk_3E7A40 + 5 * v8 + 1) = 0LL;
  *((_QWORD *)&unk_3E7A40 + 5 * v8) = 0LL;
  *((_QWORD *)&unk_3E7A40 + 5 * v8 + 4) = 0LL;
  _InterlockedCompareExchange64((volatile signed __int64 *)&unk_3E7A40 + 5 * v8 + 3, 0LL, v9);
  sub_11F30(
    "NalUnmapAddressEx: Global_WinMemoryMapTable[i].AddressToFree = %p\n",
    *((const void **)&unk_3E7A40 + 5 * v8 + 3));
LABEL_15:
  if ( v8 == 50000 )
    sub_11F30("NalUnmapAddressEx: Address not found in table - not unmapping 0x%p, Length %d\n", a1, (unsigned int)v6);
  return 0LL;
}