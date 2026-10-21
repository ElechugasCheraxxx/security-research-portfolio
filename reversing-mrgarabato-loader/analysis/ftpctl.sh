#!/usr/bin/env bash
# ftpctl.sh -- gestion del servidor FTP de laboratorio (vsftpd)
#
#   ./ftpctl.sh start | stop | restart | status | test | users | logs
#
set -u
CFG=/etc/vsftpd.conf
SVC=vsftpd

case "${1:-status}" in
  start)   systemctl start $SVC && echo "FTP arrancado" ;;
  stop)    systemctl stop $SVC && echo "FTP parado" ;;
  restart) systemctl restart $SVC && echo "FTP reiniciado" ;;
  status)
    echo "servicio : $(systemctl is-active $SVC) / $(systemctl is-enabled $SVC)"
    ss -tln 2>/dev/null | grep -w 21 | sed 's/^/socket   : /'
    echo "endpoint : ftp://192.168.64.5:21"
    echo "local    : usuario 'black' / '1234' -- raiz = / real, R/W en el arbol del laboratorio"
    echo "anonimo  : usuario 'anonymous', sin contrasena, chroot /srv/ftp/anon, escritura en /upload"
    ;;
  test)    python3 /root/mrgarabato_analysis/run/ftprw_test.py ;;
  users)
    echo "--- /etc/passwd (usuarios FTP) ---"
    grep -E '^(black|ftp):' /etc/passwd
    echo "--- arbol FTP ---"
    find /srv/ftp -maxdepth 2 -printf '  %M %u:%g %p\n' 2>/dev/null
    echo "--- ACL de 'black' sobre el arbol del laboratorio ---"
    getfacl -p /root/mrgarabato_analysis 2>/dev/null | grep -E '^(user:black|default:user:black)' | sed 's/^/  /'
    ;;
  logs)    tail -n "${2:-40}" /var/log/vsftpd.log ;;
  *)       echo "uso: $0 {start|stop|restart|status|test|users|logs}"; exit 1 ;;
esac
