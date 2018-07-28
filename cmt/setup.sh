# echo "setup LArCafJobs LArCafJobs-01-00-53 in /afs/cern.ch/user/b/benitezj/scratch0/LArStudies/20.1.4.2_LArCAF/LArCalorimeter"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/atlas.cern.ch/repo/sw/software/x86_64-slc6-gcc48-opt/20.1.4/CMT/v1r25p20140131; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtLArCafJobstempfile=`${CMTROOT}/${CMTBIN}/cmt.exe -quiet build temporary_name`
if test ! $? = 0 ; then cmtLArCafJobstempfile=/tmp/cmt.$$; fi
${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=LArCafJobs -version=LArCafJobs-01-00-53 -path=/afs/cern.ch/user/b/benitezj/scratch0/LArStudies/20.1.4.2_LArCAF/LArCalorimeter  -quiet -without_version_directory -no_cleanup $* >${cmtLArCafJobstempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/${CMTBIN}/cmt.exe setup -sh -pack=LArCafJobs -version=LArCafJobs-01-00-53 -path=/afs/cern.ch/user/b/benitezj/scratch0/LArStudies/20.1.4.2_LArCAF/LArCalorimeter  -quiet -without_version_directory -no_cleanup $* >${cmtLArCafJobstempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtLArCafJobstempfile}
  unset cmtLArCafJobstempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtLArCafJobstempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtLArCafJobstempfile}
unset cmtLArCafJobstempfile
return $cmtsetupstatus

