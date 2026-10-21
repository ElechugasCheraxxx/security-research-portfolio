#include <idc.idc>
static main() {
  msg("IDC OK, idc version=%s\n", get_kernel_version());
  qexit(0);
}
