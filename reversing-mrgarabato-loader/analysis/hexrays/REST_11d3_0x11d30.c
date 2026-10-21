char __fastcall sub_11D30(_DWORD *a1, int a2)
{
  void *retaddr; // [rsp+0h] [rbp+0h] BYREF

  if ( !a1 )
    return 0;
  *a1 = a2;
  _InterlockedOr((volatile signed __int32 *)&retaddr, 0);
  return 1;
}