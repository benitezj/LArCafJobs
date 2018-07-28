# echo "setup LArCafJobs LArCafJobs-01-00-53 in /afs/cern.ch/user/b/benitezj/scratch0/LArStudies/20.1.4.2_LArCAF/LArCalorimeter"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.1.4/CMT/v1r25p20140131
endif
source ${CMTROOT}/mgr/setup.csh
set cmtLArCafJobstempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if $status != 0 then
  set cmtLArCafJobstempfile=/tmp/cmt.$$
endif
${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=LArCafJobs -version=LArCafJobs-01-00-53 -path=/afs/cern.ch/user/b/benitezj/scratch0/LArStudies/20.1.4.2_LArCAF/LArCalorimeter  -quiet -without_version_directory -no_cleanup $* >${cmtLArCafJobstempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/${CMTBIN}/cmt.exe setup -csh -pack=LArCafJobs -version=LArCafJobs-01-00-53 -path=/afs/cern.ch/user/b/benitezj/scratch0/LArStudies/20.1.4.2_LArCAF/LArCalorimeter  -quiet -without_version_directory -no_cleanup $* >${cmtLArCafJobstempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtLArCafJobstempfile}
  unset cmtLArCafJobstempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtLArCafJobstempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtLArCafJobstempfile}
unset cmtLArCafJobstempfile
exit $cmtsetupstatus

