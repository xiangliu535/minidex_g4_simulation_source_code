minidex geant4 simulation code

git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/xiangliu535/Minidex_Geant4_Simulation.git

git remote add origin git@github.com:xiangliu535/minidex_g4_simulation_source_code.git
git push -u origin main

to commit newly modified file into repository
git status
git add [files]
git commit -m "new comments"
git push -u origin main



to pull:

 git clone git@github.com:xiangliu535/minidex_g4_simulation_source_code.git

cenv legend-base
cenv legend-old
. /opt/geant4/share/Geant4-10.5.1/geant4make/geant4make.sh 

git checkout HEAD^ file/to/overwrite
git pull

--------------------------
procedure to add new key to github
--------------------------
on my own computer

ssh-keygen -t ed25519 -C "xliu@mpp.mpg.de"
eval "$(ssh-agent -s)"

xliu@legend114:/remote/ceph2/user/x/xliu/work/minidex>ssh-add ~/.ssh/id_ed25519
Enter passphrase for /home/iwsatlas1/xliu/.ssh/id_ed25519:
Identity added: /home/iwsatlas1/xliu/.ssh/id_ed25519 (xliu@mpp.mpg.de)

then on github webpage, add new ssh key

