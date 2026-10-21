__int64 __fastcall sub_12AC0(_QWORD *a1, __int64 a2, unsigned int *a3)
{
  __int64 v4; // rax
  unsigned int v5; // ebx
  const void *v6; // rsi

  if ( !a1 || !a3 )
    return 1LL;
  v4 = *a3;
  v5 = -932544508;
  if ( !(_DWORD)v4 )
    return 3362422788LL;
  v6 = (const void *)MmMapIoSpace(a2, v4, 0LL);
  sub_11F30("NalMmapAddressEx: Vaddress = 0x%p\n", v6);
  if ( v6 )
  {
    *a1 = v6;
    sub_11F30("NalMmapAddressEx: *VirtualAddress = 0x%p (not mapped to user)\n", v6);
    if ( *a1 )
      return 0;
  }
  return v5;
}