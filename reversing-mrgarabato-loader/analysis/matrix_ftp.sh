#!/usr/bin/env bash
# matrix_ftp.sh -- prueba combinaciones de configuracion de vsftpd para el login local.
set -u
BASE=/tmp/ftpmatrix
mkdir -p $BASE
PASS='1234'
USER=black

run_case() {
  local nombre="$1"; shift
  local extra="$*"
  local cfg=$BASE/$nombre.conf

  { echo "listen=YES"
    echo "listen_address=127.0.0.1"
    echo "listen_port=2121"
    echo "write_enable=YES"
    echo "local_enable=YES"
    echo "local_umask=022"
    echo "secure_chroot_dir=/var/run/vsftpd/empty"
    echo "pasv_enable=YES"
    echo "pasv_address=127.0.0.1"
    echo "pasv_min_port=41000"
    echo "pasv_max_port=41010"
    echo "hide_ids=NO"
    echo "seccomp_sandbox=NO"
    echo "xferlog_enable=NO"
    for e in $extra; do echo "$e"; done
  } > $cfg

  # matar cualquier instancia previa en el puerto de prueba
  for p in $(ps -eo pid,args --no-headers 2>/dev/null | grep "[v]sftpd $cfg" | awk '{print $1}'); do
    kill -9 $p 2>/dev/null
  done
  sleep 0.4

  setsid vsftpd $cfg </dev/null >$BASE/$nombre.log 2>&1 0>&1 &
  local pid=$!
  sleep 1.2

  local res
  res=$(timeout 12 python3 /root/mrgarabato_analysis/run/ftptest.py 127.0.0.1 "$USER" "$PASS" 2121 2>&1 | tail -3 | tr '\n' ' ')
  kill -9 $pid 2>/dev/null
  sleep 0.3

  case "$res" in
    *"LOGIN OK"*)  printf "  %-34s %-42s => OK\n" "$nombre" "$extra" ;;
    *)             printf "  %-34s %-42s => FALLO\n" "$nombre" "$extra" ;;
  esac
}

echo "════ matriz de configuracion (puerto 2121) ════"
run_case base ""
run_case sin_chroot "chroot_local_user=NO"
run_case sin_shellcheck "check_shell=NO"
run_case chroot_y_check_no "chroot_local_user=YES" "check_shell=NO"
run_case chroot_y_allow "chroot_local_user=YES" "allow_writeable_chroot=YES"
run_case chroot_y_allow_no_shell "chroot_local_user=YES" "allow_writeable_chroot=YES" "check_shell=NO"
run_case shell_enable_no "chroot_local_user=YES" "allow_writeable_chroot=YES" "check_shell=NO"
run_case pasv_no "chroot_local_user=YES" "allow_writeable_chroot=YES" "check_shell=NO" "pasv_enable=NO"
run_case ftp_username "chroot_local_user=YES" "allow_writeable_chroot=YES" "check_shell=NO" "ftp_username=ftp"
run_case pam_login "chroot_local_user=YES" "allow_writeable_chroot=YES" "check_shell=NO" "pam_service_name=login"
run_case virtual_users "chroot_local_user=YES" "allow_writeable_chroot=YES" "check_shell=NO"
echo "  (fin)"