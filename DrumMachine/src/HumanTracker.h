#pragma once

#include <XnCppWrapper.h>
#include <vector>

#define MAX_USER_TRACK 15

class HumanTracker
{
private:
  XnCallbackHandle user_handle, pose_handle, calibration_handle;

protected:
  xn::UserGenerator& user_generator_;
  XnSkeletonJointPosition humans_parts_positions_[MAX_USER_TRACK][25];
  std::vector<XnUserID> tracked_human_ids_;

public:
  HumanTracker(XnSkeletonProfile skeleton_profile, xn::UserGenerator& user_generator);
  virtual ~HumanTracker();

  bool IsAnyHumanTracked() { return !tracked_human_ids_.empty(); }
  XnUserID GetFirstTrackedHumanId();
  std::vector<XnUserID>& tracked_human_ids() { return tracked_human_ids_; }
  XnSkeletonJointPosition GetHumanPartPosition(XnUserID user_id, XnSkeletonJoint part_type);
  std::vector<XnSkeletonJointPosition> GetHumanAllPartPosition(XnUserID user_id);

  void RegisterAllCallbacks();
  void TrackAllUsersParts();

  virtual void TrackUsers() { TrackAllUsersParts(); }
  virtual void RegisterCallbacks() { RegisterAllCallbacks(); }
  virtual void OnNewUser(xn::UserGenerator& generator, XnUserID nId);
  virtual void OnLostUser(xn::UserGenerator& generator, XnUserID nId);
  virtual void OnPoseDetected(xn::PoseDetectionCapability& pose, const XnChar* strPose, XnUserID nId);
  virtual void OnCalibrationStart(xn::SkeletonCapability& capability, XnUserID nId);
  virtual void OnCalibrationEnd(xn::SkeletonCapability& capability, XnUserID nId,XnBool bSuccess);

  static void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
  static void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie);
  static void XN_CALLBACK_TYPE Pose_Detected(xn::PoseDetectionCapability& pose, const XnChar* strPose, XnUserID nId, void* pCookie);
  static void XN_CALLBACK_TYPE Calibration_Start(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie);
  static void XN_CALLBACK_TYPE Calibration_End(xn::SkeletonCapability& capability, XnUserID nId,XnBool bSuccess, void* pCookie);

};
