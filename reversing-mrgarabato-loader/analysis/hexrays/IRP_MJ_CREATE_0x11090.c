__int64 __fastcall sub_11090(__int64 a1, __int64 a2)
{
  sub_11F30("Nal Windows DriverCreate: Starting\n");
  sub_11ED0(&dword_17120);
  *(_QWORD *)(a2 + 56) = 0LL;
  *(_DWORD *)(a2 + 48) = 0;
  IofCompleteRequest(a2, 0LL);
  sub_11F30("Nal Windows DriverCreate: Leaving\n");
  return 0LL;
}