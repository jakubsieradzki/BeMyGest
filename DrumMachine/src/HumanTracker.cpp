#include "HumanTracker.h"

#include <iostream>

using xn::UserGenerator;
using xn::PoseDetectionCapability;
using xn::SkeletonCapability;

HumanTracker::HumanTracker(XnSkeletonProfile skeleton_profile, UserGenerator& user_generator)
  : user_generator_(user_generator) 
{
  user_generator_.GetSkeletonCap().SetSkeletonProfile(skeleton_profile);
}

void XN_CALLBACK_TYPE HumanTracker::User_NewUser(UserGenerator& generator, XnUserID nId, void* pCookie)
{
  HumanTracker* human_tracker = reinterpret_cast<HumanTracker*>(pCookie);
  human_tracker->OnNewUser(generator, nId);
}

void XN_CALLBACK_TYPE HumanTracker::User_LostUser(UserGenerator& generator, XnUserID nId, void* pCookie)
{
  HumanTracker* human_tracker = reinterpret_cast<HumanTracker*>(pCookie);
  human_tracker->OnLostUser(generator, nId);
}

void XN_CALLBACK_TYPE HumanTracker::Pose_Detected(PoseDetectionCapability& pose, const XnChar* strPose, XnUserID nId, void* pCookie)
{
  HumanTracker* human_tracker = reinterpret_cast<HumanTracker*>(pCookie);
  human_tracker->OnPoseDetected(pose, strPose, nId);
}

void XN_CALLBACK_TYPE HumanTracker::Calibration_Start(SkeletonCapability& capability, XnUserID nId, void* pCookie)
{
  HumanTracker* human_tracker = reinterpret_cast<HumanTracker*>(pCookie);
  human_tracker->OnCalibrationStart(capability, nId);
}

void XN_CALLBACK_TYPE HumanTracker::Calibration_End(SkeletonCapability& capability, XnUserID nId,XnBool bSuccess, void* pCookie)
{
  HumanTracker* human_tracker = reinterpret_cast<HumanTracker*>(pCookie);
  human_tracker->OnCalibrationEnd(capability, nId, bSuccess);
}

void HumanTracker::OnNewUser(UserGenerator& generator, XnUserID nId)
{
  user_generator_.GetPoseDetectionCap().StartPoseDetection("Psi", nId);
}

void HumanTracker::OnLostUser(UserGenerator& generator, XnUserID nId)
{
}

void HumanTracker::OnPoseDetected(PoseDetectionCapability& pose, const XnChar* strPose, XnUserID nId)
{
  user_generator_.GetPoseDetectionCap().StopPoseDetection(nId);
  user_generator_.GetSkeletonCap().RequestCalibration(nId, true);
}

void HumanTracker::OnCalibrationStart(SkeletonCapability& capability, XnUserID nId)
{
}

void HumanTracker::OnCalibrationEnd(SkeletonCapability& capability, XnUserID nId,XnBool bSuccess)
{
  if (bSuccess) {
    user_generator_.GetSkeletonCap().StartTracking(nId);
  } else {
    user_generator_.GetPoseDetectionCap().StartPoseDetection("Psi", nId);
  }
}

void HumanTracker::RegisterAllCallbacks()
{
  user_generator_.RegisterUserCallbacks(User_NewUser, User_LostUser, this, user_handle);
  user_generator_.GetPoseDetectionCap()
    .RegisterToPoseCallbacks(Pose_Detected, nullptr, this, pose_handle);
  user_generator_.GetSkeletonCap()
    .RegisterCalibrationCallbacks(Calibration_Start, Calibration_End, this, calibration_handle);
}

void HumanTracker::TrackAllUsersParts()
{
  tracked_human_ids_.clear();

  XnUserID users_ids[MAX_USER_TRACK];
  XnUInt16 num_max_users = MAX_USER_TRACK;
  user_generator_.GetUsers(users_ids, num_max_users);

  for (int i = 0; i < num_max_users; ++i)
  {
    XnUserID current_user_id = users_ids[i];
    if (user_generator_.GetSkeletonCap().IsTracking(current_user_id))
    {
      tracked_human_ids_.push_back(current_user_id);
      XnSkeletonJointPosition part_position;

      // track all body parts for tracked human
      for (int part_id = 1; part_id <= 24; ++part_id) 
      {
        XnSkeletonJoint body_part = static_cast<XnSkeletonJoint>(part_id);
        user_generator_.GetSkeletonCap()
          .GetSkeletonJointPosition(current_user_id, body_part, part_position);
        humans_parts_positions[current_user_id][part_id] = part_position;
      }
    }
  }
}

XnSkeletonJointPosition HumanTracker::GetHumanPartPosition(XnUserID user_id, XnSkeletonJoint part_type)
{
  return humans_parts_positions[user_id][static_cast<unsigned>(part_type)];
}

XnUserID HumanTracker::GetFirstTrackedHumanId()
{
  return IsAnyHumanTracked() ? tracked_human_ids_[0] : -1;
}
