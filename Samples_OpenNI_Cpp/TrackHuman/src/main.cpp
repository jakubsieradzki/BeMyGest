#include "GlueGL.h"
#include "OpenNiUtil.h"

#include <iostream>

const char* HUMAN_POSE = "Psi";
const int MAX_DEPTH = 10000;
xn::UserGenerator user_generator;

// Define user tracking event callbacks
void XN_CALLBACK_TYPE User_NewUser(
  xn::UserGenerator& generator,
  XnUserID nId,
  void* pCookie)
{
  user_generator.GetPoseDetectionCap().StartPoseDetection(HUMAN_POSE, nId);
}

void XN_CALLBACK_TYPE User_LostUser(
  xn::UserGenerator& generator,
  XnUserID nId,
  void* pCookie)
{}

void XN_CALLBACK_TYPE Pose_Detected(
  xn::PoseDetectionCapability& pose,
  const XnChar* strPose,
  XnUserID nId,
  void* pCookie)
{
  user_generator.GetPoseDetectionCap().StopPoseDetection(nId);
  user_generator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}

void XN_CALLBACK_TYPE Calibration_Start(
  xn::SkeletonCapability& capability,
  XnUserID nId,
  void* pCookie)
{
}

void XN_CALLBACK_TYPE Calibration_End(
  xn::SkeletonCapability& capability,
  XnUserID nId,XnBool bSuccess,
  void* pCookie)
{
  if (bSuccess) {
    user_generator.GetSkeletonCap().StartTracking(nId);
  } else {
    user_generator.GetPoseDetectionCap().StartPoseDetection(HUMAN_POSE, nId);
  }
}

int main(int argc, char* argv[]) {
  auto& glue = bmg::GlueGL::getInstance();
  glue.Init(argc, argv, 640, 240, "TrackHuman");

  xn::Context context;
  XnStatus status = context.Init();
  bmg::OnError(status, []{
    std::cout << "Couldn't init OpenNi!" << std::endl;
    exit(1);
  });

  xn::ImageGenerator image_generator;
  status = image_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create image generator!" << std::endl;
  });

  xn::DepthGenerator depth_generator;
  status = depth_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create depth generator!" << std::endl;
  });

  xn::ImageMetaData image_metadata;
  xn::DepthMetaData depth_metadata;

  // Create user generator
  status = user_generator.Create(context);
  bmg::OnError(status, []{
    std::cout << "Couldn't create user generator!" << std::endl;
  });
  // Register user tracking callbacks
  XnCallbackHandle h1, h2, h3;
  user_generator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, h1);
  user_generator.GetPoseDetectionCap().RegisterToPoseCallbacks( Pose_Detected, NULL, NULL, h2);
  user_generator.GetSkeletonCap().RegisterCalibrationCallbacks( Calibration_Start, Calibration_End, NULL, h3);
  // Set skeleton profile
  user_generator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

  status = context.StartGeneratingAll();
  bmg::OnError(status, []{
    std::cout << "Couldn't generate all data!" << std::endl;
  });

  glue.BindDisplayFunc([&]{
    glue.BeginDraw();

    XnStatus status = context.WaitAndUpdateAll();
    bmg::OnError(status, []{
      std::cout << "Couldn't update and wait for new data!" << std::endl;
    });

    image_generator.GetMetaData(image_metadata);
    unsigned imageX = image_metadata.XRes();
    unsigned imageY = image_metadata.YRes();

    glue.DrawOnTexture(
      (void*)image_metadata.RGB24Data(),
      imageX, imageY,
      imageX, imageY,
      320, 0, 640, 240);

    depth_generator.GetMetaData(depth_metadata);
    unsigned depthX = depth_metadata.XRes();
    unsigned depthY = depth_metadata.YRes();

    XnRGB24Pixel* transformed_depth_map = new XnRGB24Pixel[depthX * depthY];
    bmg::CalculateDepth(
      depth_generator.GetDepthMap(), depthX, depthY, MAX_DEPTH, transformed_depth_map);

    glue.DrawOnTexture(
      (void*)transformed_depth_map,
      depthX, depthY,
      depthX, depthY,
      0, 0,
      320, 240);
    delete [] transformed_depth_map;

    // Get through all tracked users
    XnUserID aUsers[15];
    XnUInt16 nUsers = 15;
    user_generator.GetUsers(aUsers, nUsers);
    for (int i = 0; i < nUsers; ++i) {
      if (user_generator.GetSkeletonCap().IsTracking(aUsers[i])) {
        XnSkeletonJointPosition Head;
        user_generator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_HEAD, Head);
        XnPoint3D projective_point;
        depth_generator.ConvertRealWorldToProjective(1, &Head.position, &projective_point);
        // Display point over tracked human's head
        glue.DrawPointOverRegion(static_cast<unsigned>(projective_point.X), static_cast<unsigned>(projective_point.Y), 0, 0);
        glue.DrawPointOverRegion(static_cast<unsigned>(projective_point.X), static_cast<unsigned>(projective_point.Y), 320, 0);
      }
    }
    glue.EndDraw();
  });

  glue.BindKeyboardFunc([](unsigned char key, int x, int y){
    switch(key) {
    case 27:
      exit(1);
    }
  });

  glue.Run();
  context.Release();
}