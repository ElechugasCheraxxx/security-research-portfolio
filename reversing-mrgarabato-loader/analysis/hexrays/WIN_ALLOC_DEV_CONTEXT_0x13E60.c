void *sub_13E60()
{
  void *result; // rax
  void *v1; // rbx

  result = (void *)ExAllocatePoolWithTag(0LL, 1584LL, 543908932LL);
  v1 = result;
  if ( result )
  {
    memset(result, 0, 0x630uLL);
    return v1;
  }
  return result;
}