__int64 __fastcall sub_13EA0(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 result; // rax

  if ( a1 )
  {
    if ( *(_DWORD *)(a1 + 936) )
    {
      result = ObfDereferenceObject(*(_QWORD *)(a1 + 392), a2, a3);
      --*(_DWORD *)(a1 + 936);
    }
    if ( !*(_DWORD *)(a1 + 936) )
      return ExFreePoolWithTag(a1);
  }
  return result;
}