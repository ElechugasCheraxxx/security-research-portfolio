__int64 __fastcall sub_121C0(const void *a1, __int64 a2, unsigned int a3)
{
  __int64 v4; // rbx

  v4 = a3;
  if ( a1 && a3 )
  {
    sub_11F30("NalUnmapAddress: Unmapping non-usermode mapped address 0x%p, Length %d\n", a1, a3);
    MmUnmapIoSpace(a1, v4);
  }
  return 0LL;
}