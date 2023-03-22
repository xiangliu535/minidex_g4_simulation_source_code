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
~/bin/parallel-2020-slurm '/afs/ipp-garching.mpg.de/home/x/xliu/work/minidex/minidex_g4_simulation_source_code/simulate_run_v/script_sum_up_all_systematic_histograms_from_mc.sh '${runnumber}' {}' ::: /ptmp/mpp/xliu/work/merging_needed_logs/log*.txt

