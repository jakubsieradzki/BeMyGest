/* --------------------------------------------------------------------------
 * SimpleOpenNI Hands3d Test
 * --------------------------------------------------------------------------
 * Processing Wrapper for the OpenNI/Kinect 2 library
 * http://code.google.com/p/simple-openni
 * --------------------------------------------------------------------------
 * prog:  Max Rheiner / Interaction Design / Zhdk / http://iad.zhdk.ch/
 * date:  12/12/2012 (m/d/y)
 * ----------------------------------------------------------------------------
 * This demos shows how to use the gesture/hand generator.
 * It's not the most reliable yet, a two hands example will follow
 * ----------------------------------------------------------------------------
 */
 
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import SimpleOpenNI.*;

// OpenNI context
SimpleOpenNI context;

// shape size
final static int SIZE = 40;
final static int OFFSET = SIZE / 2;

// RGB colors
int r_, g_, b_;

// bounds for color computation
float xMax_, xMin_, yMax_, yMin_;

// shape switch
boolean shapeIsCircle_ = false;

Map<Integer,ArrayList<PVector>> handPathMap_ = new HashMap<Integer,ArrayList<PVector>>();
int handVecListSize_ = 20;


void setup()
{
  // window size
  size(640,480);

  //init context
  context = new SimpleOpenNI(this);
  if(context.isInit() == false)
  {
     println("Can't init SimpleOpenNI, maybe the camera is not connected!"); 
     exit();
     return;  
  }   

  // enable depthMap generation 
  context.enableDepth();
  context.enableRGB();
  
  // disable mirror
  context.setMirror(true);

  // enable hands + gesture generation  
  context.enableHand();
  context.startGesture(SimpleOpenNI.GESTURE_WAVE);
  context.startGesture(SimpleOpenNI.GESTURE_HAND_RAISE);
}

void draw()
{
  // update the cam
  context.update();
  
  // draw color image
  image(context.rgbImage(),0,0);
    
  // draw the tracked hands
  if(handPathMap_.size() > 0)  
  {    
    Iterator itr = handPathMap_.entrySet().iterator();     
    while(itr.hasNext())
    {
      Map.Entry mapEntry = (Map.Entry)itr.next();       
      ArrayList<PVector> vecList = (ArrayList<PVector>)mapEntry.getValue();
      PVector p;
      PVector p2d = new PVector();
    
      noStroke();
      fill(r_, g_, b_);             
      
      Iterator itrVec = vecList.iterator();
      beginShape();
        while(itrVec.hasNext()) 
        { 
          p = (PVector) itrVec.next(); 
          context.convertRealWorldToProjective(p,p2d);
          drawShape(p2d);
        }
      endShape();  
            
      context.convertRealWorldToProjective(vecList.get(0), p2d);
      drawShape(p2d);
    }        
  }
}

void drawShape(PVector vector)
{
  if (shapeIsCircle_)
    ellipse(vector.x, vector.y, SIZE/2, SIZE/2);
  else
    rect(vector.x - OFFSET, vector.y - OFFSET, SIZE, SIZE, 5);
}


// -----------------------------------------------------------------
// hand events

void onNewHand(SimpleOpenNI curContext,int handId,PVector pos)
{
  println("onNewHand - handId: " + handId + ", pos: " + pos);
 
  ArrayList<PVector> vecList = new ArrayList<PVector>();
  vecList.add(pos);  
  handPathMap_.put(handId,vecList);
}

void onTrackedHand(SimpleOpenNI curContext,int handId,PVector pos)
{
  //println("onTrackedHand - handId: " + handId + ", pos: " + pos );
  
  updateParams(pos);
  
  updateColors(pos);
  
  // update map
  ArrayList<PVector> vecList = handPathMap_.get(handId);
  if(vecList != null)
  {
    vecList.add(0,pos);
    if(vecList.size() >= handVecListSize_)
      // remove the last point 
      vecList.remove(vecList.size()-1); 
  }  
}

void updateParams(PVector curPos)
{
  if (curPos.x > xMax_) { xMax_ = curPos.x; }
  if (curPos.y > yMax_) { yMax_ = curPos.y; }
  if (curPos.x < xMin_) { xMin_ = curPos.x; }
  if (curPos.y < yMin_) { yMin_ = curPos.y; }  
}

void updateColors(PVector curPos)
{
  // red
  float normColorValue = curPos.x - xMin_;
  float maxDistance = xMax_ - xMin_;
  r_ =  (int) (255 * normColorValue / maxDistance);
  
  // green
  normColorValue = curPos.y - yMin_;
  maxDistance = yMax_ - yMin_;
  g_ =  (int) (255 * normColorValue / maxDistance);
  
  // blue
  b_ = (r_ + g_) / 2;
}

void onLostHand(SimpleOpenNI curContext,int handId)
{
  println("onLostHand - handId: " + handId);
  handPathMap_.remove(handId);
}

// -----------------------------------------------------------------
// gesture events

void onCompletedGesture(SimpleOpenNI curContext,int gestureType, PVector pos)
{
  println("onCompletedGesture - gestureType: " + gestureType + ", pos: " + pos);
  switch (gestureType) {
    // wave
    case 0:
      changeShape();
      break;
    // hand raise
    case 2:
      context.startTrackingHand(pos);      
      break;
    default:
      println("Unknown gesture");
  }  
  
}

void changeShape()
{
  println("Shape change");
  shapeIsCircle_ = !shapeIsCircle_;  
}

// -----------------------------------------------------------------
// Keyboard event
void keyPressed()
{

  switch(key)
  {
  case ' ':
    context.setMirror(!context.mirror());
    break;
  case '1':
    context.setMirror(true);
    break;
  case '2':
    context.setMirror(false);
    break;
  }
}
