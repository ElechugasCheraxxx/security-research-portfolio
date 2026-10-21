__int64 __fastcall sub_129C0(_QWORD *a1, __int64 a2, unsigned int *a3, __int64 a4)
{
  __int64 v7; // rax
  unsigned int v8; // ebx
  const void *v9; // rsi
  const void *v10; // rax

  if ( !a1 || !a3 )
    return 1LL;
  v7 = *a3;
  v8 = -932544508;
  if ( !(_DWORD)v7 )
    return 3362422788LL;
  v9 = (const void *)MmMapIoSpace(a2, v7, 0LL);
  sub_11F30("NalMmapAddressEx: Vaddress = 0x%p\n", v9);
  if ( v9 )
  {
    if ( a4 )
    {
      v10 = (const void *)sub_12030(v9, *a3, a4);
      *a1 = v10;
      sub_11F30("NalMmapAddressEx: *VirtualAddress = 0x%p (mapped to user)\n", v10);
    }
    else
    {
      *a1 = v9;
      sub_11F30("NalMmapAddressEx: *VirtualAddress = 0x%p (not mapped to user)\n", v9);
    }
    if ( *a1 )
      return 0;
  }
  return v8;
}