#!/bin/bash
#
# this script is used to submit runv jobs A-E, input argument must be 1 to 20
#
runnumber=$1
echo run number is $runnumber
if [ $(($runnumber)) -lt 1 ] || [ $(($runnumber)) -gt 20 ]; then
  echo input run number must be 1 to 20
  exit
fi
  echo now submit ${runnumber}A
#~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days '${runnumber}'A {}' ::: /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days/the.a-*
#  sleep 10
  echo now submit ${runnumber}B
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days '${runnumber}'B {}' ::: /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days/the.a-*
  sleep 10
  echo now submit ${runnumber}C
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days '${runnumber}'C {}' ::: /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days/the.a-*
  sleep 10
  echo now submit ${runnumber}D
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days '${runnumber}'D {}' ::: /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days/the.a-*
  sleep 10
  echo now submit ${runnumber}E
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days '${runnumber}'E {}' ::: /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days/the.a-*

