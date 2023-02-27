=========================================================
NOTICE: job submission must be outside container
=========================================================
command to submit jobs is 
=========================================================

~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/xliu/fluka_input 1 {}' ::: /ptmp/mpp/xliu/fluka_input/the.a-*

2022.08.05 simulate again

~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days 1A {}' ::: /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days 1B {}' ::: /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days 1C {}' ::: /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days 1D {}' ::: /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days 1E {}' ::: /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days/the.a-*

~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days 2A {}' ::: /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days 2B {}' ::: /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days 2C {}' ::: /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days 2D {}' ::: /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days 2E {}' ::: /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days/the.a-*

~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days 3A {}' ::: /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days 3B {}' ::: /ptmp/mpp/aempl/work/raphael/B-2.14gcm3-approx-24.129-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days 3C {}' ::: /ptmp/mpp/aempl/work/raphael/C-2.14gcm3-approx-24.146-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days 3D {}' ::: /ptmp/mpp/aempl/work/raphael/D-2.14gcm3-approx-24.151-days/the.a-*
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days 3E {}' ::: /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days/the.a-*

=========================================================
2023.02.25, to increase MC statics, only save histograms
=========================================================
cd minidex_runv_mc_run1B
hadd h.runv_mc_merged.1B.root $(find . -name "1B_RUN_V_simulate_minidex_*.root" | sort) >& log.merge_runv_mc_1B.txt
cd minidex_runv_mc_run:B
hadd h.runv_mc_merged.3B.root $(find . -name "3B_RUN_V_simulate_minidex_*.root" | sort) >& log.merge_runv_mc_3B.txt

hadd h.runv_mc_merged.4A.root $(find . -name "4A_RUN_V_simulate_minidex_*.root" | sort) >& log.merge_runv_mc_4A.txt

and commands to check status

squeue -j job_ID
squeue -u xliu
squeue -j job_ID --start

------
single run, test
------
./simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days 3E /ptmp/mpp/aempl/work/raphael/E-2.14gcm3-approx-24.134-days/the.a-ud6b_d_oo09-608544

------
submit 10 jobs for testing, and add up all
------
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/xliu/work/raphael/A-2.14gcm3-approx-24.154-days 4A {}' ::: /ptmp/mpp/xliu/work/raphael/A-2.14gcm3-approx-24.154-days/the.a-*
hadd h.runv_mc_merged.4A.root $(find . -name "4A_RUN_V_simulate_minidex_*.root" | sort) >& log.merge_runv_mc_4A.txt

----> 4A with trajectory and trajector points information saved
~/bin/parallel-2020-slurm './simulate_minidex_run_v.sh RUN_V /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days 4A {}' ::: /ptmp/mpp/aempl/work/raphael/A-2.14gcm3-approx-24.154-days/the.a-*

------
old input files
------
/ptmp/mpp/aempl/work/raphael/4.75GV-1.85gcm3-approx-490-hours
/ptmp/mpp/aempl/work/raphael/4.75GV-1.85gcm3-approx-515-hours
/ptmp/mpp/aempl/work/raphael/4.75GV-1.85gcm3-approx-516-hours
/ptmp/mpp/aempl/work/raphael/4.75GV-1.85gcm3-approx-519-hours
/ptmp/mpp/aempl/work/raphael/4.75GV-1.85gcm3-approx-520-hours

