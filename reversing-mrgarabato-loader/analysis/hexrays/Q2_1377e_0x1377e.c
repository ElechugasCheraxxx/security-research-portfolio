__int16 sub_13740()
{
  __int64 v0; // rdx
  __int64 v1; // r8
  __int64 v2; // rdi
  __int64 v3; // rbx
  __int64 v5; // [rsp+20h] [rbp-18h] BYREF
  unsigned int v6; // [rsp+28h] [rbp-10h]

  v5 = 0LL;
  v6 = 0;
  sub_132B0(&v5);
  sub_11F30("_NalReadPciDeviceCount found %d devices (%d)\n", (unsigned __int16)v6, v6);
  v2 = v5;
  if ( v5 )
  {
    do
    {
      ObfDereferenceObject(*(_QWORD *)(v2 + 48), v0, v1);
      v3 = *(_QWORD *)(v2 + 584);
      ExFreePoolWithTag(v2);
      v2 = v3;
    }
    while ( v3 );
  }
  return v6;
}