char __fastcall sub_13E00(__int64 a1)
{
  char result; // al

  if ( !a1 )
    return 0;
  sub_11F30("_NalHasInterruptOccurred returning %s\n");
  result = *(_BYTE *)(a1 + 297);
  *(_BYTE *)(a1 + 297) = 0;
  return result;
}