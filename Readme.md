# Incident Response Course - Intro into Incident Response

This repository presents some examples of security incident response / investigation.

The trainings from this repository are for beginners and focus on the perspective of Operating Systems concepts.

When investigating a system, we are mainly looking at the system's anomalies.
Mainly, we are focusing out analysis on the following OS resources:
  - system calls - gives an overview of what the system is running (can be too verbose); filtering may be needed.
  - processes - we can see what processes are running in the system and find the ones that do not fit with the server activity.
  - memory - when needed, inspect the memory of a running process to see what it does.
  - disk / file system - file system changes may indicate malicious activity.
  - network connections - track suspicious connections.
  - configuration files - bad configurations can lead to security issues.
  - services/applications - odd applications may be indicators of compromise
  - how tools are used - legitimate tools ca be used to launch attacks.

![Testing Architecture](so-security.drawio.png)


## CPU

```
# htop
# ps -ef
# ll /proc/<pid>/
```


## Connections

```
sudo ss -utwpano
sudo tcpdump -i <if> port <src> or port <dst> -s0 -A
```

## Auditd

```
sudo apt update && sudo apt install auditd audispd-plugins
 
sudo ausearch -i

sudo aureport -x

sudo auditctl -w /dev/shm -p rw -k dev_shm

sudo ausearch -i -k dev_shm

sudo auditctl -a exit,always -F arch=b64 -F euid=0 -S execve

sudo auditctl -a always,exit -S all -F path=/usr/bin/tar -F uid=1000

sudo auditctl -a exit,always -F arch=b64 -F uid=student -S open,openat,creat -F dir=/dev/shm/

sudo auditctl -d always,exit -S all -F path=/usr/bin/tar -F uid=1000

```

## Memory inspection

```
cat /proc/<pid>/maps
00400000-00401000 r--p 00000000 00:01 1044                               /memfd: (deleted)
00401000-00402000 r-xp 00001000 00:01 1044                               /memfd: (deleted)
00402000-00403000 r--p 00002000 00:01 1044                               /memfd: (deleted)
00403000-00404000 rw-p 00002000 00:01 1044                               /memfd: (deleted)
7ffe22bdb000-7ffe22bfc000 rw-p 00000000 00:00 0                          [stack]
7ffe22d7a000-7ffe22d7e000 r--p 00000000 00:00 0                          [vvar]
7ffe22d7e000-7ffe22d80000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]

sudo cat /proc/<pid>/map_files/401000-402000 > test

file test
test: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, not stripped

objdump -d -M intel test
../test:     file format elf64-x86-64


Disassembly of section .text:

0000000000401000 <main>:
  401000:       55                      push   rbp
  401001:       48 89 e5                mov    rbp,rsp

```

## Services (web) - Data exfiltration

```
cat /var/log/apache2/access.log

apt install libapache2_mod_security2

cp /etc/modsecurity/modsecurity.conf-recommended /etc/modsecurity/modsecurity.conf

systemctl restart apache2

cat /var/log/apache/mod_security.log

```

## Services (web) - Remote Code Execution



# File system inspection

TODO
