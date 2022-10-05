#!/bin/bash
#
#
#$ -q standard
#$ -j y
#$ -notify
#$ -e /afs/ipp-garching.mpg.de/home/m/matpaler/log
#$ -o /afs/ipp-garching.mpg.de/home/m/matpaler/log
#$ -S /bin/bash
#
GEOMETRY=$1
input_data_folder=$2
ReSimulation_Number=$3
folder_AND_input_data_file=$4
input_data_file=`echo $folder_AND_input_data_file | awk -F\/ '{print $8}'`
#
jobID=`date +%Y%m%d%H%M%S`_${input_data_file}
echo jobID is $jobID
#
#---> get number of events from the input file to be simulated
#
number_of_events_in_inputfile=`echo $input_data_file | awk -F\- '{print $3}'`
echo -e  "\n"
echo The number of events in this input file is: $number_of_events_in_inputfile
echo -e  "\n"
###### toni told me to recejt the last event each time
number_of_events_we_run=$(($number_of_events_in_inputfile-1))
echo -e  "\n"
echo The number of events we run is: $number_of_events_we_run
echo -e  "\n"
#
#---> output root file
#
TMPDIR=/ptmp/mpp
calclocation=$TMPDIR/xliu
echo calclocation is $calclocation
echo TMPDIR is $TMPDIR
calcdir=${calclocation}/$jobID
outputfile=${ReSimulation_Number}_${GEOMETRY}_simulate_minidex_${input_data_file}.root
echo Making ${calcdir}
mkdir -p ${calcdir} # kein Fehler, wenn vorhanden; übergeordnete Verzeichnissen erzeugen, wenn notwendig
echo Changing to ${calcdir}
cd ${calcdir}
#
########
repository=/ptmp/mpp/xliu/minidex_runv_mc_run${ReSimulation_Number} # this is the folder where the output of the simulation will be stored - this folder needs to be created before u run the simulation to be created before you run the simulation                                                                        
echo Creating $repository
mkdir -p ${repository}
########
#
#--> prepare macro file for simulation
#
macname=${GEOMETRY}_${input_data_file}_$jobID.mac
echo THE MACNAME IS: $macname
echo TESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT start
echo inputpath und inputfilename is: $input_data_folder/$input_data_file
echo TESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT end
#
cat > ${macname} <<!

#*******************
/control/verbose 0
/run/verbose 0
/event/verbose 0
/tracking/verbose 0

/HPGe/det/GDMLsourceFile /afs/ipp-garching.mpg.de/home/x/xliu/work/minidex/minidex_gdml_simulation/gdml_geometry/RunV_geometry/MINIDEX_GDML_RunV_Phase2.gdml

/run/initialize

/xe/gun/useFluka true
/xe/gun/FlukaInputFileName $input_data_folder/$input_data_file

#*******************
!
#
#---> start the simulation
echo Running simulation
if [ -f /ptmp/mpp/projects/gedet/sw/scripts/bin/mpcdf-mpp-env.sh ]; then
    . /ptmp/mpp/projects/gedet/sw/scripts/bin/mpcdf-mpp-env.sh
fi
#
cenv legend-old /afs/ipp-garching.mpg.de/home/x/xliu/geant4/bin/Linux-g++/minidex_sim -f ${macname} -n ${number_of_events_we_run} -o ${outputfile}
#. /opt/geant4/share/Geant4-10.5.1/geant4make/geant4make.sh 
#
# --> move output
#
echo Copying ${outputfile} to ${repository}
if [ ! -f ${outputfile} ]; then
    echo ERROR ${outputfile} not created
fi
mv ${outputfile} ${repository}
# clean up
cd $TMPDIR/xliu # this here needs to be also changed to the correct one  
echo Removing ${calcdir} ...
rm -rf ${calcdir}

#rmdir --ignore-fail-on-non-empty ${calclocation}

#---> I DO NOT understand the following yet
#cd /afs/ipp/home/x/xliu/.batch/jobs # i think this folder needs to be created as well
#taskname=${input_data_file}
#ls -dt */ > dirlist_${taskname}.txt
#lastdir=`head -n 1 dirlist_${taskname}.txt`
#echo $lastdir
#cd $lastdir
#rm -f task-${taskname}.stdout
#cd -
#rm -f dirlist_${taskname}.txt
