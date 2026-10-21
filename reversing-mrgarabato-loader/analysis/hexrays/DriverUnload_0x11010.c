__int64 __fastcall sub_11010(__int64 a1)
{
  __int64 v2; // rcx
  struct _UNICODE_STRING DestinationString; // [rsp+20h] [rbp-18h] BYREF

  sub_11F30("Nal Windows Driver Unload: Starting\n");
  RtlInitUnicodeString(&DestinationString, L"\\??\\Nal");
  IoDeleteSymbolicLink(&DestinationString);
  v2 = *(_QWORD *)(a1 + 8);
  if ( v2 )
    IoDeleteDevice(v2);
  else
    sub_11F30("Nal Windows Driver Unload: IoDeleteDevice NOT called: NULL DeviceObject\n");
  return sub_11F30("Nal Windows Driver Unload: Leaving... \n");
}