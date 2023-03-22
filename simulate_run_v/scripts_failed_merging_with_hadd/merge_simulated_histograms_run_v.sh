#!/bin/bash
#
# this script is used to submit runv jobs A-E, input argument must be 1 to 20
#
runnumber=$1
runsubnumber_filename=$2
runsubnumber=`cat "${runsubnumber_filename}"`
echo now merge $runnumber${runsubnumber}
cd /ptmp/mpp/xliu/
mkdir -p runv_merged_histograms
mkdir -p runv_merged_logs
rm runv_merged_histograms//h.runv_mc_merged.${runnumber}${runsubnumber}.root
rm runv_merged_logs/log.merge.runv_mc_${runnumber}${runsubnumber}.txt
hadd runv_merged_histograms/h.runv_mc_merged.${runnumber}${runsubnumber}.root $(find minidex_runv_mc_run${runnumber}${runsubnumber} -name "${runnumber}${runsubnumber}_RUN_V_simulate_minidex_*.root" | sort) >& runv_merged_logs/log.merge.runv_mc_${runnumber}${runsubnumber}.txt

