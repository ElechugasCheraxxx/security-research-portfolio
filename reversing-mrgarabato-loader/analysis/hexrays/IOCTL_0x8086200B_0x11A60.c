__int64 __fastcall sub_11A60(__int64 a1)
{
  __int64 result; // rax
  char Dst[280]; // [rsp+20h] [rbp-118h] BYREF

  result = 1LL;
  if ( a1 )
  {
    switch ( *(_QWORD *)a1 )
    {
      case 1LL:
        *(_WORD *)(a1 + 16) = sub_13740();
        result = 0LL;
        break;
      case 2LL:
        *(_DWORD *)(a1 + 16) = sub_137D0(a1 + 24, a1 + 20);
        result = 0LL;
        break;
      case 3LL:
        memmove(Dst, (const void *)(a1 + 24), 0x108uLL);
        *(_DWORD *)(a1 + 16) = sub_138B0(Dst, a1 + 292, *(unsigned int *)(a1 + 288));
        result = 0LL;
        break;
      case 4LL:
        memmove(Dst, (const void *)(a1 + 24), 0x108uLL);
        *(_DWORD *)(a1 + 16) = sub_13980(Dst, *(unsigned int *)(a1 + 288), a1 + 292);
        result = 0LL;
        break;
      case 5LL:
        memmove(Dst, (const void *)(a1 + 24), 0x108uLL);
        *(_DWORD *)(a1 + 16) = sub_13A00(Dst, *(unsigned int *)(a1 + 288), *(unsigned int *)(a1 + 292));
        result = 0LL;
        break;
      case 6LL:
        memmove(Dst, (const void *)(a1 + 24), 0x108uLL);
        *(_DWORD *)(a1 + 16) = sub_13B20(Dst);
        result = 0LL;
        break;
      case 7LL:
        memmove(Dst, (const void *)(a1 + 24), 0x108uLL);
        *(_DWORD *)(a1 + 16) = sub_13100(Dst);
        result = 0LL;
        break;
      default:
        result = 3362398232LL;
        break;
    }
  }
  return result;
}